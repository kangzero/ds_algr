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

#include <stdint.h>

void radix_sort(int* nums, int n);
void bucket_sort(int* nums, int n);
void count_sort(int* nums, int n);
void merge_sort_buc(int* nums, int n);
void merge_sort_ubc(int* nums, int n);
void shell_sort(int* nums, int n);
void heap_sort(int* nums, int n);
void quick_sort(int* nums, int n);
void insertion_sort(int* nums, int n);
void selection_sort(int* nums, int n);
void bubble_sort(int* nums, int n);
int array_sorting_test(void);

#endif

