// A simple hash implementation

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_SIZE 1024UL

//#define _DEBUG
#define _RELEASE

typedef uint32_t Type;

typedef struct HashNode_ {
    Type key;
    uint32_t val;
    struct HashNode_ * next;
} HashNode;

HashNode* hashTable[MAX_SIZE];

uint32_t table_size;

void hash_init(void);
uint32_t hash_code (const Type key);
Type put (const Type key);
Type get (const Type key);
HashNode* search (const Type key);
void hash_destroy (void);

// init the hash table
void hash_init(void)
{
  table_size = 0;
  memset(hashTable, 0, sizeof(HashNode*) * MAX_SIZE);
}

uint32_t hash_code (const Type key)
{
  return (key % MAX_SIZE);
}

// return the key node's count number, return 0 if put failed
Type put (const Type key)
{
    if (table_size >= MAX_SIZE) {
        printf("%s failed because table if full!\n", __func__);
        return 0;
    }

    uint32_t idx = hash_code(key);
    HashNode* node = search(key);
    if (node != NULL) {
        // find the node in the table
        node->val += 1;
        return node->val;
    } else {
        // create a new node
        node = (HashNode*)calloc(1, sizeof(HashNode));
        if (!node) {
            printf("%s failed because calloc failed\n", __func__);
            return 0;
        }
        node->key = key;
        node->val = 1;
        node->next = hashTable[idx];
        hashTable[idx] = node;
        table_size++;
    }

    return 1;
}

// get a node with the key, if the node val is 1, remove the node
// return key node's count number, return 0 if node removed
Type get (const Type key)
{
    uint32_t idx = hash_code(key);
    uint32_t cnt = 0;

    if (hashTable[idx] == NULL) {
        printf("%s invalid key!\n", __func__);
        return 0;
    } else {
        HashNode* cur = hashTable[idx];
        HashNode* pre = NULL;
        HashNode* tmp = NULL;

        while (cur != NULL) {
            if (cur->key == key) {
                cur->val -= 1;
                cnt = cur->val;
                if (cur->val == 0) {
                    tmp = cur;
                    break;
                }
            }
            pre = cur;
            cur = cur->next;
        }

        if (tmp != NULL) {
            table_size--;
            if(pre != NULL)
              pre->next = tmp->next;
            else
              hashTable[idx] = NULL;
            free(tmp);
            tmp = NULL;
        }
    }

    return cnt;
}

// search the key in the table, return NULL if the key doesn't exist
HashNode* search (const Type key)
{
    uint32_t idx = hash_code(key);

    if (hashTable[idx] != NULL) {
        HashNode* cur = hashTable[idx];
        while (cur != NULL) {
            if(cur->key == key)
                return cur;
            cur = cur->next;
        }
    }

    return NULL;
}

// destroy the table, release memory
void hash_destroy (void)
{
    for (uint32_t i = 0; i < MAX_SIZE; ++i) {
        if (hashTable[i]) {
            HashNode* cur = hashTable[i];
            while (cur != NULL) {
                HashNode* rm = cur;
                cur = cur->next;
                if (rm) {
#ifdef _DEBUG
                    table_size--;
                    printf("DEBUG %s: table_size = %d\n", __func__, table_size);

#endif
                    free(rm);
                    rm = NULL;
                }
            }
        }
    }
#ifdef _RELEASE
    table_size = 0;
#endif
}

int main(int argc, char** argv)
{
    hash_init();

    const Type ip1 = 10316207;
    const Type ip2 = 20311008;
    const Type ip3 = 10315209;
    const Type ip4 = 11;

    uint32_t cnt = 0;

    printf("hash table put test ... ...\n");
    cnt = put(ip1);
    printf("%d's count = %d, table_size = %d\n", ip1, cnt, table_size);
    cnt = put(ip2);
    printf("%d's count = %d, table_size = %d\n", ip2, cnt, table_size);
    cnt = put(ip3);
    printf("%d's count = %d, table_size = %d\n", ip3, cnt, table_size);
    cnt = put(ip1);
    printf("%d's count = %d, table_size = %d\n", ip1, cnt, table_size);
    cnt = put(ip1);
    printf("%d's count = %d, table_size = %d\n", ip1, cnt, table_size);
    cnt = put(ip1);
    printf("%d's count = %d, table_size = %d\n", ip1, cnt, table_size);
    cnt = put(ip1);
    printf("%d's count = %d, table_size = %d\n", ip1, cnt, table_size);
    cnt = put(ip3);
    printf("%d's count = %d, table_size = %d\n", ip3, cnt, table_size);

    printf("hash table search test ... ...\n");
    HashNode* cur = search(ip1);
    printf("key = %d val = %d \n", cur->key, cur->val);
    cur = search(ip2);
    printf("key = %d val = %d \n", cur->key, cur->val);
    cur = search(ip3);
    printf("key = %d val = %d \n", cur->key, cur->val);

    printf("hash table get test ... ...\n");
    cnt = get(ip3);
    printf("%d's count = %d, table_size = %d\n", ip3, cnt, table_size);
    cnt = get(ip3);
    printf("%d's count = %d, table_size = %d\n", ip3, cnt, table_size);
    cnt = get(ip4);
    printf("%d's count = %d, table_size = %d\n", ip4, cnt, table_size);

    printf("hash table destroy test ... ...\n");
    hash_destroy();
    printf("hash table size = %d\n", table_size);

    return 0;
}
