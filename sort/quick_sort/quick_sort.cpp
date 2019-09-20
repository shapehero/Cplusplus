#include <iostream>

void quick_sort(int arr[], int left, int right)
{
	if (left >= right)
		return;
	int i = left;
	int j = right;
	int key = arr[left];
	while (i < j)
	{
		while (i < j && key <= arr[j])
			j--;
		arr[i] = arr[j];

		while (i < j && key >= arr[i])
			i++;
		arr[j] = arr[i];
	}
	arr[i] = key;
	quick_sort(arr, left, i - 1);
	quick_sort(arr, i + 1, right);
}

int main(int argc, char *argv[])
{
	int arr[] = {17,32,3,7,65,23,82,97,45,54};
	int len = sizeof(arr)/sizeof(int);
	for (int i = 0; i < len; i++)
		std::cout << arr[i] << " ";
	std::cout << std::endl;

	quick_sort(arr, 0, len - 1);

	for (int i = 0; i < len; i++)
		std::cout << arr[i] << " ";
	std::cout << std::endl;
	return 0;
}
