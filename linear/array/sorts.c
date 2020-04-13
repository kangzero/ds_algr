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
 * V1.3     add sorting runtime         12/07/2019
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
#include <sys/time.h>
#include <unistd.h>

#include "../log.h"
#include "sorts.h"

//#define _DEBUG
#define TAG     "ARRAY"

// macro for ascending or descending sort
#define SORT_DES 0
#define SORT_ASC 1

#define NELEMS(array) (sizeof(array) / sizeof(array[0])) \

typedef struct {
    char* name;
    void (*sf)(int*, int);
} sorts_f;

sorts_f sorts[] = {
    {"Bubble Sort\0", &bubble_sort},
    {"Select Sort\0", &selection_sort},
    {"Insert Sort\0", &insertion_sort},
    {"Quick Sort\0", &quick_sort},
    {"Heap Sort\0", &heap_sort},
    {"Shell Sort\0", &shell_sort},
    {"Merge SortUBC\0", &merge_sort_ubc},
    {"Merge SortBUC\0", &merge_sort_buc},
    {"Count Sort\0", &count_sort},
    {"Bucket Sort\0", &bucket_sort},
    {"Radix Sort\0", &radix_sort}
};

void quick_sort_helper(int* nums, int left, int right);
void merge_sort_ubc_helper(int* num, int start, int end);
void merge_group(int* nums, int n, int slen);
void merge(int* nums, int start, int mid, int end);
void swap(int *x, int *y);
void log_array(int *nums, int n);
void heapmax_down(int* nums, int start, int end);
void heapmin_down(int* nums, int start, int end);
void group_sort(int* nums, int n, int i, int gap);

int test_arr[] = {2, 3, 1, 0, 4, 9, 5, 7, 6};

#ifdef _MODULAR_TEST
int main(int argc, char** argv)
#elif defined _FULL_SYS
int array_sorting_test(void)
#endif
{
#ifdef _MODULAR_TEST
    logger_init();
#endif
    struct timeval start;
    struct timeval end;
    unsigned long runtime = 0;

    int len = NELEMS(test_arr);
    int *nums = (int*)malloc(len * sizeof(int));

    Log.i(TAG, "==== Array Sorting Test Start ====\n");

    Log.i(TAG, "the orignial array is:");
    log_array(test_arr, len);

    for (int i = 0; i < NELEMS(sorts); i++) {
        // restore the test array after sorting
        memmove(nums, test_arr, len * sizeof(int));
        // sorting test
        gettimeofday(&start, NULL);
        sorts[i].sf(nums, len);
        gettimeofday(&end, NULL);
        runtime = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;
        // output test result
        Log.i(TAG, "%s runtime: %lu ms:", sorts[i].name, runtime);
        log_array(nums, len);
    }

    Log.i(TAG, "==== Array Sorting Test End ====\n");

    return 1;
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
void count_sort(int* nums, int n)
{
    if (!nums || !n) return;

    int max = 0;
    int k = 0;
    for (int i = 0; i < n; i++)
        max = (max > nums[i]) ? max : nums[i];
    int* count = calloc((max+1), sizeof(int));
    for (int i = 0; i < n; i++)
        count[nums[i]]++;
#if SORT_ASC
    for (int i = 0; i < max + 1; i++)
#elif SORT_DES
    for (int i = max; i >= 0; i--)
#endif
        for (int j = 0; j < count[i]; j++)
            nums[k++] = i;

    free(count);
    count = NULL;
}

//merge sort buttom up computation
void merge_sort_buc(int* nums, int n)
{
    if (!nums || !n) return;

    for (int i = 1; i < n; i *= 2)
        merge_group(nums, n, i);
}

//merge groups
void merge_group(int* nums, int n, int slen)
{
    int i = 0;
    for (i = 0; i + 2 * slen - 1 < n; i += 2 * slen)
        merge(nums, i, i + slen - 1, i + 2 * slen - 1);

    if (i + slen - 1 < n - 1)
        merge(nums, i, i + slen - 1, n - 1);
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
    Log.d(TAG, "merge_sort_ubc enter!");
    Log.d(TAG, "start = %d, end = %d", start, end);
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
    if (tmp == NULL) {
        Log.d(TAG, "Merge: tmp malloc failed!");
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

    free(tmp), tmp = NULL;
}

//shell sort
void shell_sort(int* nums, int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = 0; i < gap; i++) {
            group_sort(nums, n, i, gap);
        }
    }
}

//group sort for every step
void group_sort(int* nums, int n, int start, int gap)
{
    for (int i = start + gap; i < n; i += gap) {
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
void heap_sort(int* nums, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
#if SORT_ASC
        heapmax_down(nums, i, n - 1);
#elif SORT_DES
        heapmin_down(nums, i, n - 1);
#endif
    for (int i = n - 1; i >= 0; i--) {
        swap(&nums[0], &nums[i]);
#if SORT_ASC
        heapmax_down(nums, 0, i - 1);
#elif SORT_DES
        heapmin_down(nums, 0, i - 1);
#endif
    }
}

// build up max heap
void heapmax_down(int* nums, int start, int end)
{
    int p = start; //parent node
    int cur = nums[p];

    for (int l = 2 * p + 1; l <= end; p = l, l = 2 * l + 1) {
        if (l < end && nums[l] < nums[l+1])
            l++; //max of 2 l child & r child
        if (cur >= nums[l]) {
            break;
        } else {
            nums[p] = nums[l];
            nums[l] = cur;
        }
    }
}

// build up min heap
void heapmin_down(int* nums, int start, int end)
{
    int p = start;
    int cur = nums[p];

    for (int l = 2 * p+ 1; l <= end; p = l, l = 2 * l + 1) {
        if (l < end && nums[l] > nums[l+1])
            l++;
        if (cur <= nums[l]) {
            break;
        } else {
            nums[p] = nums[l];
            nums[l] = cur;
        }
    }
}

// quick sort
void quick_sort(int* nums, int n)
{
    quick_sort_helper(nums, 0, n - 1);
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

// insertion sort
void insertion_sort (int* nums, int n)
{
    int key;
    for (int i = 1; i < n; i++) {
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

// selection sort
void selection_sort(int* nums, int n)
{
    for (int i = 0; i < n - 1; i++) {
        int m = i; //index of max or min element
        for (int j = i + 1; j < n; j++) {
#if SORT_ASC
            if (nums[j] < nums[m])
#elif SORT_DES
            if (nums[j] > nums[m])
#endif
                m = j;
        }
        if (m != i)
            swap(&nums[m], &nums[i]);
    }
}

// bubble sort
void bubble_sort(int* nums, int n)
{
    for (int i = n - 1; i >= 0; i--) {
        char flag = 0;
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
        if (!flag) break;
    }
}

// swap two element
void swap(int *x, int *y)
{
#if 0
    int tmp = *x;
    *x = *y;
    *y = tmp;
#else // swap 2 elemts w/o another temp variable
    *x = *x + *y;
    *y = *x - *y;
    *x = *x - *y;
#endif
}

// print elements in the array
void log_array(int* nums, int n)
{
    Log.c(TAG, "The elements in the array are: ");
    for (int i = 0; i < n; i++)
        printf("%d ", nums[i]);
    printf("\n");
}

