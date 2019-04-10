/********************************************************************************
 *
 * Filename: sorts.c
 * Description: sorting algorithm implementation
 *
 * Version: v1.0
 * History:
 * V1.0     Created by Ning Kang        03/28/2019
 * V1.1     callback function           04/08/2019
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
//for general cases, an input parameter could be defined in sort fun
#define SORT_DES 0
#define SORT_ASC 1

//func pointer declaration
void (*p_func)(int*, int) = NULL;

//definition of lib func
void sorting(int* v, int len, void (*p_func)(int*, int))
{
    return (*p_func)(v, len);
}

int main(int argc, char** argv)
{
    int a[] = {2, 3, 1, 0, 4, -1, 5, 7, 6};
    int cp[] = {2, 3, 1, 0, 4, -1, 5, 7, 6};
    int* nums = a;
    int numsSize = 9;


    printf("Bubble Sort:\n");
    printf("Before Sort: ");
    array_print(nums, numsSize);
    sorting(nums, numsSize, &bubble_sort);
    //bubble_sort(nums, numsSize);
    printf("After Sort: ");
    array_print(nums, numsSize);
    printf("\n");

    printf("Selection Sort: \n");
    memcpy(a, cp, sizeof(int) * numsSize);
    printf("Before Sort: ");
    array_print(nums, numsSize);
    sorting(nums, numsSize, &selection_sort);
    //selection_sort(nums, numsSize);
    printf("After Sort: ");
    array_print(nums, numsSize);
    printf("\n");

    printf("Insertion Sort:\n");
    memcpy(a, cp, sizeof(int) * numsSize);
    printf("Before Sort: ");
    array_print(nums, numsSize);
    sorting(nums, numsSize, &insertion_sort);
    //insertion_sort(nums, numsSize);
    printf("After Sort: ");
    array_print(nums, numsSize);
    printf("\n");

    printf("Quick Sort:\n");
    memcpy(a, cp, sizeof(int) * numsSize);
    printf("Before Sort: ");
    array_print(nums, numsSize);
    quick_sort(nums, 0, numsSize-1);
    printf("After Sort: ");
    array_print(nums, numsSize);
    printf("\n");

    printf("Heap Sort:\n");
    memcpy(a, cp, sizeof(int) * numsSize);
    printf("Before Sort: ");
    array_print(nums, numsSize);
    sorting(nums, numsSize, &heap_sort);
    //heap_sort(nums, numsSize);
    printf("After Sort: ");
    array_print(nums, numsSize);
    printf("\n");

    printf("Shell Sort:\n");
    memcpy(a, cp, sizeof(int) * numsSize);
    printf("Before Sort: ");
    array_print(nums, numsSize);
    sorting(nums, numsSize, &shell_sort);
    //shell_sort(nums, numsSize);
    printf("After Sort: ");
    array_print(nums, numsSize);
    printf("\n");

    printf("Merge Sort - UBC:\n");
    memcpy(a, cp, sizeof(int) * numsSize);
    printf("Before Sort: ");
    array_print(nums, numsSize);
    merge_sort_ubc(nums, 0, numsSize-1);
    printf("After Sort: ");
    array_print(nums, numsSize);
    printf("\n");

    printf("Merge Sort - BUC:\n");
    memcpy(a, cp, sizeof(int) * numsSize);
    printf("Before Sort: ");
    array_print(nums, numsSize);
    sorting(nums, numsSize, &merge_sort_buc);
    //merge_sort_buc(nums, numsSize);
    printf("After Sort: ");
    array_print(nums, numsSize);
    printf("\n");

    //int c[] = {8, 1, 6, 5, 2, 0, 4, 7, 9, 3};
    int c[] = {8, 1, 6, 6, 2, 0, 8, 7, 9, 3};
    nums = c;
    numsSize = 9;
    printf("Count Sort:\n");
    printf("Before Sort: ");
    array_print(nums, numsSize);
    sorting(nums, numsSize, &count_sort);
    //count_sort(nums, numsSize);
    printf("After Sort: ");
    array_print(nums, numsSize);
    printf("\n");

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
void count_sort(int* nums, int numsSize)
{
    if ((nums == NULL) || (numsSize == 0)) return;

    int max = 0;
    int k = 0;

    for (int i = 0; i < numsSize; i++)
    {
        max = (max > nums[i]) ? max : nums[i];
    }

    int* count = calloc((max+1), sizeof(int));

    for (int i = 0; i < numsSize; i++)
    {
        count[nums[i]]++;
    }

#if SORT_ASC
    for (int i = 0; i < (max+1); i++)
#elif SORT_DES
    for (int i = max; i >= 0; i--)
#endif
    {
        for (int j = 0; j < count[i]; j++)
        {
            nums[k] = i;
            k++;
        }
    }

    free(count);
    count = NULL;
}

//merge sort buttom up computation
void merge_sort_buc(int* nums, int numsSize)
{
    if ((nums == NULL) || (numsSize <= 0)) return;

    for (int i = 1; i < numsSize; i *= 2)
    {
        merge_group(nums, numsSize, i);
    }
}

//merge groups
void merge_group(int* nums, int numsSize, int slen)
{
    int i = 0;
    for (i = 0; (i+2*slen-1) < numsSize; i += 2*slen)
    {
        merge(nums, i, i+slen-1, i+2*slen-1);
    }

    if ((i+slen-1) < (numsSize-1))
    {
        merge(nums, i, i+slen-1, numsSize-1);
    }
}

//merge sort up buttom computation
void merge_sort_ubc(int* nums, int start, int end)
{
    if ((nums == NULL) || (start >= end)) return;
#ifdef _DEBUG
    printf("[merge_sort_ubc enter!\n");
    printf("start = %d, end = %d\n", start, end);
#endif
    int mid = (start + end) / 2;
    merge_sort_ubc(nums, start, mid);
    merge_sort_ubc(nums, mid+1, end);

    merge(nums, start, mid, end);
}

//merge two sorted group
void merge(int* nums, int start, int mid, int end)
{
#ifdef _DEBUG
    printf("start = %d, mid = %d, end = %d\n", start, mid, end);
#endif
    int *tmp = malloc((end-start+1) * sizeof(int));
    if (tmp == NULL)
    {
        printf("[merge] - tmp malloc failed !!! \n");
        return;
    }
    int i = start;
    int j = mid + 1;
    int k = 0;

    while ((i <= mid) && (j <= end))
    {
#ifdef _DEBUG
        printf("nums[i] = %d, nums[j] = %d\n", nums[i], nums[j]);
#endif
#if SORT_ASC
        if (nums[i] <= nums[j])
#elif SORT_DES
        if (nums[i] >= nums[j])
#endif
        {
            tmp[k] = nums[i];
#ifdef _DEBUG
            printf("i: nums[%d] = %d, tmp[%d] = %d \n", i, nums[i], k, tmp[k]);
#endif
            k++;
            i++;
        } else {
            tmp[k] = nums[j];
#ifdef _DEBUG
            printf("j: nums[%d] = %d, tmp[%d] = %d \n", j, nums[j], k, tmp[k]);
#endif
            k++;
            j++;
        }
    }

    while (i <= mid)
    {
        tmp[k] = nums[i];
        k++;
        i++;
    }
    while (j <= end)
    {
        tmp[k] = nums[j];
        k++;
        j++;
    }

    for (i = 0; i < k; i++)
    {
        nums[start+i] = tmp[i];
#ifdef _DEBUG
        printf("nums[%d] = %d\n", start+i, nums[start+i]);
#endif
    }

    free(tmp);
    tmp = NULL;
}

//shell sort
void shell_sort(int* nums, int numsSize)
{
    for (int gap = numsSize/2; gap > 0; gap /= 2)
    {
        for (int i = 0; i < gap; i++)
        {
            group_sort(nums, numsSize, i, gap);
        }
    }
}

//group sort for every step
void group_sort(int* nums, int numsSize, int start, int gap)
{
    for (int i = (start+gap); i < numsSize; i += gap)
    {
#if SORT_ASC
        if (nums[i] < nums[i-gap])
#elif SORT_DES
        if (nums[i] > nums[i-gap])
#endif
        {
            int key  = nums[i];
            int j = i - gap;
#if SORT_ASC
            while ((j >= 0) && (nums[j] > key))
#elif SORT_DES
            while ((j >= 0) && (nums[j] < key))
#endif
            {
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
    {
        heapmax_down(nums, i, (numsSize-1));
#ifdef _DEBUG
        array_print(nums, numsSize);
#endif
    }

    for (int i = (numsSize-1); i >= 0; i--)
    {
        swap(&nums[0], &nums[i]);
        heapmax_down(nums, 0, (i-1));
    }
#elif SORT_DES
    for (int i = ((numsSize/2)-1); i >= 0; i--)
    {
        heapmin_down(nums, i, (numsSize-1));
#ifdef _DEBUG
        array_print(nums, numsSize);
#endif
    }
    for (int i = (numsSize-1); i >= 0; i--)
    {
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

    for (int l = (2*p + 1); l <= end; p = l, l = 2*l+1)
    {
#ifdef _DEBUG
        printf("l = %d, cur = %d\n", l, cur);
#endif
        if ((l < end) && (nums[l] < nums[l+1]))
        {
            l++; //max of 2 l child & r child
        }
        if (cur >= nums[l])
        {
            break;
        } else {
            nums[p] = nums[l];
            nums[l] = cur;
        }
#ifdef _DEBUG
        printf("nums[%d] = %d, nums[%d]= %d\n", p, nums[p], l, nums[l]);
        array_print(nums, 9);
#endif
    }
}

//build up min heap
void heapmin_down(int* nums, int start, int end)
{
    int p = start;
    int cur = nums[p];

    for (int l = (2*p+1); l <= end; p = l, l = 2*l+1)
    {
        if ((l < end) && (nums[l] > nums[l+1]))
        {
            l++;
        }
        if (cur <= nums[l])
        {
            break;
        } else {
            nums[p] = nums[l];
            nums[l] = cur;
        }
    }
}

//quick sort
void quick_sort(int* nums, int left, int right)
{
    if (left < right)
    {
        int l = left;
        int r = right;
        int pivot = nums[l];
        while (l < r)
        {
#if SORT_ASC
            while ((l < r) && (nums[r] > pivot))
#elif SORT_DES
            while ((l < r) && (nums[r] < pivot))
#endif
            {
                r--;
            }
            if (l < r)
            {
                nums[l] = nums[r];
                l++;
            }
#if SORT_ASC
            while ((l < r) && (nums[l] < pivot))
#elif SORT_DES
            while ((l < r) && (nums[l] > pivot))
#endif
            {
                l++;
            }
            if (l < r)
            {
                nums[r] = nums[l];
                r--;
            }
        }
        nums[l] = pivot;
#ifdef _DEBUG
        array_print(nums, 8);
        printf("l = %d, r = %d\n", l, r);
#endif
        quick_sort(nums, left, l-1);
        quick_sort(nums, l+1, right);
    }
}

//insertion sort
void insertion_sort (int* nums, int numsSize)
{
    int key;

    for (int i = 1; i < numsSize; i++)
    {
        key = nums[i];
        int j = i - 1;
#if SORT_ASC
        while ((j >= 0) && (nums[j] > key))
#elif SORT_DES
        while ((j >= 0) && (nums[j] < key))
#endif
        {
            nums[j+1] = nums[j];
            j--;
        }
        nums[j+1] = key;
    }
}

//selection sort
void selection_sort(int* nums, int numsSize)
{
    for (int i = 0; i < (numsSize-1); i++)
    {
        int max = i;
        for (int j = (i+1); j < numsSize; j++)
        {
#if SORT_ASC
            if (nums[j] < nums[max])
#elif SORT_DES
            if (nums[j] > nums[max])
#endif
            {
                max = j;
            }
        }
#ifdef _DEBUG
        printf("nums[%d] = %d, nums[%d] = %d\n", max, nums[max], i, nums[i]);
#endif
        swap(&nums[max], &nums[i]);
    }
}

//bubble sort
void bubble_sort(int* nums, int numsSize)
{
    for (int i = (numsSize-1); i > 0; i--)
    {
        int flag = 0;
        for (int j = 0; j < i; j++)
        {
#if SORT_ASC
            if (nums[j] > nums[j+1])
#elif SORT_DES
            if (nums[j] < nums[j+1])
#endif
            {
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
    //xor op raise error when x = y;
}

//print elements in array
void array_print(int* nums, int numsSize)
{
    for (int i = 0; i < numsSize; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");
}
