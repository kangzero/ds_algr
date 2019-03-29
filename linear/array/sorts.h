/********************************************************************************
 *
 * Filename: sorts.h
 * Description: sorting algorithm implementation
 *
 * Version: v1.0
 * History:
 * V1.0     Created by Ning Kang     03/28/2019
 *
 * Copyright(c) 2019 by Ning Kang
 *
 * This software is placed into the public domain and may be used for any purpose.  
 * However, this notice must not be changed or removed and no warranty is either 
 * expressed or implied by its publication or distribution.
 *
 ********************************************************************************/
#ifndef SORTS_H
#define SORTS_H

void radix_sort(int* nums, int numsSize);
void bucket_sort(int* nums, int numsSize);
void count_sort(int* nums, int numsSize);
void merge_sort_buc(int* nums, int numsSize);
void merge_group(int* nums, int numsSize, int slen);
void merge_sort_ubc(int* nums, int start, int end);
void merge(int* nums, int start, int mid, int end);
void shell_sort(int* nums, int numsSize);
void group_sort(int* nums, int numsSize, int i, int gap);
void heap_sort(int* nums, int numsSize);
void heapmax_down(int* nums, int start, int end);
void heapmin_down(int* nums, int start, int end);
void quick_sort(int* nums, int left, int right);
void insertion_sort(int* nums, int numsSize);
void selection_sort(int* nums, int numsSize);
void bubble_sort(int* nums, int numsSize);
void swap(int *x, int *y);
void array_print(int *nums, int numsSize);

#endif

