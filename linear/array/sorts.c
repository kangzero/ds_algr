/********************************************************************************
 *
 * Filename: sorts.c
 * Description: sorting algorithm implementation
 *
 * Version: v1.0
 * History:
 * V1.0     Created by Ning Kang        03/28/2019
 * V1.1     callback function           04/08/2019
 * V1.2     simplify test function      12/06/2019
 *
 * Copyright(c) 2019 by Ning Kang
 *
 * This software is placed into the public domain and may be used for any purpose.
 * However, this notice must not be changed or removed and no warranty is either
 * expressed or implied by its publication or distribution.
 *
 ********************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorts.h"

//#define _DEBUG

//macro for ascending or descending sort
#define SORT_DES 0
#define SORT_ASC 1

#define NELEMS(array) (sizeof(array) / sizeof(array[0])) \

typedef struct _SORTS_OPCODE {
    char* name;
    void (*sort_opcode)(int*, int);
} SORTS_OPCODE;

SORTS_OPCODE sorts[] = {
    {"BubbleSort\0", &bubble_sort},
    {"SelectSort\0", &selection_sort},
    {"InsertSort\0", &insertion_sort},
    {"QuickSort\0", &quick_sort},
    {"HeapSort\0", &heap_sort},
    {"ShellSort\0", &shell_sort},
    {"MergeSortUBC\0", &merge_sort_ubc},
    {"MergeSortBUC\0", &merge_sort_buc},
    {"CountSort\0", &count_sort},
    {"BucketSort\0", &bucket_sort},
    {"RadixSort\0", &radix_sort}
};

void quick_sort_helper(int* nums, int left, int right);
void merge_sort_ubc_helper(int* num, int start, int end);
void merge_group(int* nums, int numsSize, int slen);
void merge(int* nums, int start, int mid, int end);
void swap(int *x, int *y);
void log_array(int *nums, int numsSize);
void heapmax_down(int* nums, int start, int end);
void heapmin_down(int* nums, int start, int end);
void group_sort(int* nums, int numsSize, int i, int gap);
void log_string(char *str);


int test_arr[] = {2, 3, 1, 0, 4, 9, 5, 7, 6};

void main(int argc, char** argv)
{
    int numsSize = NELEMS(test_arr);
    int *nums = (int*)malloc(numsSize * sizeof(int));
    log_array(test_arr, numsSize);
    for (int i = 0; i < NELEMS(sorts); i++) {
        //restore the test array after sorting
        memmove(nums, test_arr, numsSize * sizeof(int));
        log_string(sorts[i].name);
        //sorting test
        sorts[i].sort_opcode(nums, numsSize);
        log_array(nums, numsSize);
    }
    return;
}

void radix_sort(int* nums, int numsSize)
{
    //inplement later...
}

void bucket_sort(int* nums, int numsSize)
{
    //implement later...
}

//count sort: assume all the elements >= 0 in nums
//if you want to apply this algorithm to negative number
//you could split array into 2 part, transfer the negative
//number to positive number, and then merge together
//will implement this later
void count_sort(int* nums, int numsSize)
{
    if ((nums == NULL) || (numsSize == 0)) return;

    int max = 0;
    int k = 0;
    for (int i = 0; i < numsSize; i++)
        max = (max > nums[i]) ? max : nums[i];
    int* count = calloc((max+1), sizeof(int));
    for (int i = 0; i < numsSize; i++)
        count[nums[i]]++;
#if SORT_ASC
    for (int i = 0; i < (max+1); i++)
#elif SORT_DES
    for (int i = max; i >= 0; i--)
#endif
        for (int j = 0; j < count[i]; j++)
            nums[k++] = i;

    free(count);
    count = NULL;
}

//merge sort buttom up computation
void merge_sort_buc(int* nums, int numsSize)
{
    if ((nums == NULL) || (numsSize <= 0)) return;

    for (int i = 1; i < numsSize; i *= 2)
        merge_group(nums, numsSize, i);
}

//merge groups
void merge_group(int* nums, int numsSize, int slen)
{
    int i = 0;
    for (i = 0; (i+2*slen-1) < numsSize; i += 2*slen)
        merge(nums, i, i+slen-1, i+2*slen-1);

    if ((i+slen-1) < (numsSize-1))
        merge(nums, i, i+slen-1, numsSize-1);
}

//merge sort up buttom computation
void merge_sort_ubc(int* nums, int numsSize)
{
    merge_sort_ubc_helper(nums, 0, numsSize-1);
}

void merge_sort_ubc_helper(int* nums, int start, int end)
{
    if (nums == NULL || start >= end) return;
#ifdef _debug
    printf("[merge_sort_ubc enter!\n");
    printf("start = %d, end = %d\n", start, end);
#endif
    int mid = (start + end) / 2;
    merge_sort_ubc_helper(nums, start, mid);
    merge_sort_ubc_helper(nums, mid+1, end);
    merge(nums, start, mid, end);
}

//merge two sorted group
void merge(int* nums, int start, int mid, int end)
{
    int *tmp = malloc((end-start+1) * sizeof(int));
    if (tmp == NULL)
    {
        printf("[merge] - tmp malloc failed !!! \n");
        return;
    }
    int i = start;
    int j = mid + 1;
    int k = 0;

    while ((i <= mid) && (j <= end)) {
#if SORT_ASC
        if (nums[i] <= nums[j])
#elif SORT_DES
        if (nums[i] >= nums[j])
#endif
            tmp[k++] = nums[i++];
        else
            tmp[k++] = nums[j++];
    }

    while (i <= mid)
        tmp[k++] = nums[i++];
    while (j <= end)
        tmp[k++] = nums[j++];

    for (i = 0; i < k; i++)
        nums[start+i] = tmp[i];

    free(tmp);
    tmp = NULL;
}

//shell sort
void shell_sort(int* nums, int numsSize)
{
    for (int gap = numsSize/2; gap > 0; gap /= 2) {
        for (int i = 0; i < gap; i++) {
            group_sort(nums, numsSize, i, gap);
        }
    }
}

//group sort for every step
void group_sort(int* nums, int numsSize, int start, int gap)
{
    for (int i = (start+gap); i < numsSize; i += gap) {
#if SORT_ASC
        if (nums[i] < nums[i-gap]) {
#elif SORT_DES
        if (nums[i] > nums[i-gap]) {
#endif
            int key  = nums[i];
            int j = i - gap;
#if SORT_ASC
            while ((j >= 0) && (nums[j] > key)) {
#elif SORT_DES
            while ((j >= 0) && (nums[j] < key)) {
#endif
                nums[j+gap] = nums[j];
                j -= gap;
            }
            nums[j+gap] = key;
        }
    }
}

//heap sort
void heap_sort(int* nums, int numsSize)
{
#if SORT_ASC
    for (int i = ((numsSize/2)-1); i >= 0; i--)
        heapmax_down(nums, i, (numsSize-1));

    for (int i = (numsSize-1); i >= 0; i--) {
        swap(&nums[0], &nums[i]);
        heapmax_down(nums, 0, (i-1));
    }
#elif SORT_DES
    for (int i = ((numsSize/2)-1); i >= 0; i--)
        heapmin_down(nums, i, (numsSize-1));
    for (int i = (numsSize-1); i >= 0; i--){
        swap(&nums[0], &nums[i]);
        heapmin_down(nums, 0, (i-1));
    }
#endif
}

//build up max heap
void heapmax_down(int* nums, int start, int end)
{
    int p = start; //parent node
    int cur = nums[p];

    for (int l = (2*p + 1); l <= end; p = l, l = 2*l+1) {
        if ((l < end) && (nums[l] < nums[l+1]))
            l++; //max of 2 l child & r child
        if (cur >= nums[l]) {
            break;
        } else {
            nums[p] = nums[l];
            nums[l] = cur;
        }
    }
}

//build up min heap
void heapmin_down(int* nums, int start, int end)
{
    int p = start;
    int cur = nums[p];

    for (int l = (2*p+1); l <= end; p = l, l = 2*l+1) {
        if ((l < end) && (nums[l] > nums[l+1]))
            l++;
        if (cur <= nums[l]) {
            break;
        } else {
            nums[p] = nums[l];
            nums[l] = cur;
        }
    }
}

//quick sort
void quick_sort(int* nums, int numsSize)
{
    quick_sort_helper(nums, 0, numsSize-1);
}

void quick_sort_helper(int* nums, int left, int right)
{
    if (left < right) {
        int l = left;
        int r = right;
        int pivot = nums[l];
        while (l < r) {
#if SORT_ASC
            while ((l < r) && (nums[r] > pivot)) r--;
#elif SORT_DES
            while ((l < r) && (nums[r] < pivot)) r--;
#endif
            if (l < r)
                nums[l++] = nums[r];
#if SORT_ASC
            while ((l < r) && (nums[l] < pivot)) l++;
#elif SORT_DES
            while ((l < r) && (nums[l] > pivot)) l++;
#endif
            if (l < r)
                nums[r--] = nums[l];
        }
        nums[l] = pivot;
        quick_sort_helper(nums, left, l-1);
        quick_sort_helper(nums, l+1, right);
    }
}

//insertion sort
void insertion_sort (int* nums, int numsSize)
{
    int key;
    for (int i = 1; i < numsSize; i++) {
        key = nums[i];
        int j = i - 1;
#if SORT_ASC
        while ((j >= 0) && (nums[j] > key)) {
#elif SORT_DES
        while ((j >= 0) && (nums[j] < key)) {
#endif
            nums[j+1] = nums[j];
            j--;
        }
        nums[j+1] = key;
    }
}

//selection sort
void selection_sort(int* nums, int numsSize)
{
    for (int i = 0; i < (numsSize-1); i++) {
        int m = i; //index of max or min element
        for (int j = (i+1); j < numsSize; j++) {
#if SORT_ASC
            if (nums[j] < nums[m])
#elif SORT_DES
            if (nums[j] > nums[m])
#endif
                m = j;
        }
        swap(&nums[m], &nums[i]);
    }
}

//bubble sort
void bubble_sort(int* nums, int numsSize)
{
    for (int i = (numsSize-1); i > 0; i--) {
        int flag = 0;
        for (int j = 0; j < i; j++) {
#ifdef SORT_ASC
            if (nums[j] > nums[j+1]) {
#elif defined SORT_DES
            if (nums[j] < nums[j+1]) {
#endif
                swap(&nums[j], &nums[j+1]);
                flag = 1;
            }
        }
        if (flag == 0) break;
    }
}

//swap two element
void swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

//print elements in the array
void log_array(int* nums, int numsSize)
{
    for (int i = 0; i < numsSize; i++)
        printf("%d ", nums[i]);
    printf("\n");
}

void log_string(char *str)
{
    while(*str != '\0')
        printf("%c", *str++);
    printf("\n");
}
