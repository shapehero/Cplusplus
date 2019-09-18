#include <iostream>

int get_loop_array_index(int arr[], int len, int key)
{
    int left = 0;
    int right = len - 1;
    int mid;
    while (left <= right)
    {
        mid = (left + right) / 2;
        if( arr[mid] == key )
        {
            return mid;
        }
        if( arr[left] <= arr[mid])
        {
            if(arr[left] <= key && arr[mid] >= key)
            {
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }
        else
        {
            if(arr[mid] <= key && arr[right] >= key)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
    }
    return -1;
}
int binary_search(int arr[], int len, int key)
{
    int left = 0;
    int right = len - 1;
    int mid;
    while(left <= right)
    {
        mid = (left + right) >> 1;
        if(arr[mid] == key)
        {
            return mid;
        }
        if(arr[mid] > key)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
        
    }
    return -1;
}

int binary_search_recursion(int arr[], int start, int end, int key)
{
    if(start > end)
    {
        return -1;
    }
    
    int left = start;
    int right = end;
    int mid = (left + right) >> 1;
    if(arr[mid] == key)
    {
        return mid;
    }
    if(arr[mid] > key)
    {
        return binary_search_recursion(arr, start, mid - 1, key);
    }
    else
    {
        return binary_search_recursion(arr, mid + 1, end, key);
    }
    
}

int main(int argc, char *argv[])
{
    // int a[] = {4, 5, 6, 7, 8, 1, 2, 3};
    // printf("%d\n", get_loop_array_index(a, 8, 3));

    int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
    // printf("%d\n", binary_search(a, 8, 7));
    printf("%d\n", binary_search_recursion(a, 0, 7, 7));
    return 0;
}
