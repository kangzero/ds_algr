
#include "stdio.h"
#include "stdlib.h"

#define MAX_SIZE 100U

#define BUFFER_MALLOC
#define MYMALLOC_FREE_SBRK

#define align4(x)   (((((x)-1) >> 2) << 2) + 4)
#define align8(x)   (((((x)-1) >> 3) << 3) + 8)
#define align16(x)  (((((x)-1) >> 4) << 4) + 16)
#define align32(X)  (((((x)-1) >> 5) << 5) + 32)
#define align64(x)  (((((x)-1) >> 6) << 6) + 64)

typedef int elemType;

//static Linkedlist structure
typedef struct {
    elemType data;  //data
    int cur;        //cursor to next node, 0: no next node
} component, sLinkedList[MAX_SIZE];

//init the unused nodes
void init_cur(sLinkedList *L)
{
    for (int i = 0; i < MAX_SIZE-1; i++) {
        (*L)[i].cur = i + 1;
    }
    (*L)[MAX_SIZE-1].cur = 0;
}

//private malloc
static int sLinkedList_malloc(sLinkedList *L)
{
    int tmp = (*L)[0].cur;
    if (tmp == 0) {
        printf("Error: memory malloc failed!\n");
    } else {
        (*L)[0].cur = (*L)[tmp].cur;
    }
    printf("Allocate %d \n", tmp);
    return tmp;
}

static void sLinkedList_free(sLinkedList *L, int idx)
{
    (*L)[idx].cur = (*L)[0].cur;
    (*L)[0].cur = idx;
    printf("Free %d \n", idx);
}


#ifdef BUFFER_MALLOC_FREE
//A simple buffer alloc sample code
#define BUFFER_MAX_SIZE 100000U

static char Buf[BUFFER_MAX_SIZE];   //storage
static char *ptrMalloc = Buf;       //next free position

//malloc
static char* BufMalloc(int nBytes)
{
    if (Buf + BUFFER_MAX_SIZE - ptrMalloc >= nBytes) {
        ptrMalloc += nBytes;
        return ptrMalloc - nBytes;
    } else {
        return NULL;
    }
}

//free: need to free memory by order
void BufFree(char *ptrFree)
{
    if (ptrFree >= Buf && ptrFree < Buf + BUFFER_MAX_SIZE)
        ptrMalloc = ptrFree;
    else
        printf("Invalid memory address to free!\n");
}
#endif

#ifdef MYMALLOC_FREE_SBRK
//malloc and free implementation
char has_initialized = 0;
void *ptr_memory_start;
void *last_valid_address;

void myMallocInit(void)
{
    last_valid_address = sbrk(0);
    ptr_memory_start = last_valid_address;
    has_initialized = 1;
    return;
}

typedef struct mem_control_block {
    int isValid;
    int size;
} MCB;

void myFree(void *firstByte)
{
    MCB *mcb = firstByte - sizeof(MCB);
    mcb->isValid = 1;
    return;
}

void* myMalloc(int numBytes)
{
    void *curAddr;
    MCB *curAddrMcb;
    void *memAddr;

    if (!has_initialized)
        myMallocInit();

    numBytes = align4(numBytes + sizeof(MCB));
    memAddr = NULL;
    curAddr = ptr_memory_start;
    while (curAddr != last_valid_address) {
        curAddrMcb = (MCB*)curAddr;
        if (curAddrMcb->isValid) {
            if (curAddrMcb->size >= numBytes) {
                //found an valid memory block and return the current address
                curAddrMcb->isValid = 0;
                memAddr = curAddr;
                break;
            }
        }
        //move to next block to see if we could grab valid mem block
        curAddr = curAddr + curAddrMcb->size;
    }

    if (!memAddr) {
        if(sbrk(numBytes) == -1)
            return NULL;
        memAddr = last_valid_address;
        last_valid_address += numBytes;;
        curAddrMcb = memAddr;
        curAddrMcb->isValid = 0;
        curAddrMcb->size = numBytes;
    }

    memAddr = memAddr + sizeof(MCB);
    return memAddr;
}
#endif

#ifdef LL_MALLOC_FREE
typedef struct s_block *t_block

struct s_block {
    size_t size;
    t_block next;
    int free;
    char data[1];
}

#define BLOCK_SIZE 12

void* base = NULL;

t_block find_block(t_block *last, size_t size)
{
    t_block b = base;
    while (b && !b->free && b->size >= size) {
        *last = b;
        b = b->next;
    }
    return b;
}

t_block extend_heap(t_block last, size_t size)
{
    t_block b;
    b = sbrk(0);
    if (sbrk(sizeof(struct s_block) + size) == (void*)-1)
        return NULL;
    b->size = size;
    b->next = NULL;
    if (last)
        last->next = b;
    b->free = 0;
    return b;
}

t_block split_block(t_block b, size_t size)
{
    t_block new;
    new = b->data + size;
    new->size = b->size - size - BLOCK_SIZE;
    new->next = b->next;
    new->free = 1;
    b->size = size;
    b->next = new;
}

#define align4(x)   (((((x)-1) >> 2) << 2) + 4)
#define align8(x)   (((((x)-1) >> 3) << 3) + 8)
#define align16(x)  (((((x)-1) >> 4) << 4) + 16)
#define align32(X)  (((((x)-1) >> 5) << 5) + 32)
#define align64(x)  (((((x)-1) >> 6) << 6) + 64)

void *malloc(size_t size)
{
    t_block b, last;
    size_t s;
    s = align4(size);
    if (base) {
        last = base;
        b = find_block(&last, s);
        if (b) {
            if (b->size - s >= BLOCK_SIZE + 8)
                split_block(b, s);
            b->free = 0;
        } else {
            b = extend_heap(last, s);
            if (!b)
                return NULL;
        }
    } else {
        b = extend_heap(NULL, s);
        if (!b)
            return NULL;
        base = b;
    }
    return b->data;
}

#endif

int main()
{
    sLinkedList sl;
    init_cur(&sl);
    for (int j = 0; j < MAX_SIZE; j++)
        printf("the cur of %d is %d \n", j, sl[j].cur);
    for (int i = 0; i < MAX_SIZE; i++) {
        int j = sLinkedList_malloc(&sl);
        if (j != 0)
            sl[j].data = 0x55;
        else
            printf("the static linkedlist is full");
    }
    sLinkedList_free(&sl, 20);
    sLinkedList_malloc(&sl);

    return 0;
}
