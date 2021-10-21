#include <stdlib.h>
#include <stdio.h>

int bubble_sort(int *nums, size_t num_size, int *sort_nums)
{
    int i, j;
    int tmp;

    for (i = num_size - 1; i > 0; i--) {
        for (j = 0; j < i; j++) {
            if (nums[j] > nums[j + 1]) {
                tmp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = tmp;
            }
        }
    }
}

int quick_sort(int *array, int low, int high)
{
    if (low >= high) {
        return 0;
    }
    int pivot = array[low];
    int start = low;
    int end = high;

    while (low < high) {
        while (low < high && array[high] >= pivot) {
            high--;
        }
        array[low] = array[high];
        while (low < high && array[low] <= pivot) {
            low++;
        }
        array[high] = array[low];
    }
    array[low] = pivot;
    quick_sort(array, start, low-1);
    quick_sort(array, low + 1, end);
    return 0;
}

int main()
{
    int array[10] = {5, 9, 5, 8, 7, 2, 4, 0, 3, 1};

    quick_sort(array, 0, 9);
    for (int i = 0; i < 10; i++)
    {
        printf("%d\t", array[i]);
    }
}
