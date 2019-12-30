/*
You are given an unordered array consisting of consecutive integers [1, 2, 3, ..., n] 
without any duplicates nor specific order.You are allowed to swap any two elements.
You need to find the minimum number of swaps required to sort the array in ascending 
order.

CONSTRAINTS:
-> the number of elements must be >= 1
-> the elements in the array must be <= than the size of the array
*/

#include <iostream>
#include <vector>
#include <chrono>

void swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

void printArray(std::vector<int> arrToPrint)
{
	for (int i = 0; i < arrToPrint.size(); i++)
	{
		std::cout << arrToPrint[i] << "  ";
	}
}

int minimumSwaps(std::vector<int> &arr)
{
	int numberOfSwaps = 0;

	bool isSwapping = true;

	while (isSwapping)
	{
		isSwapping = false;
		for (int i = 0; i < arr.size(); i++)
		{
			if (arr[i] - 1 != i)
			{
				isSwapping = true;
				std::cout << "Swapped " << arr[i] << " with " << arr[arr[i] - 1] << std::endl;
				swap(arr[i], arr[arr[i] - 1]);
				printArray(arr);
				std::cout << std::endl;
				numberOfSwaps++;
			}
		}
	}

	return numberOfSwaps;
}

int main()
{
	int numberOfElements;
	std::cout << "How many elements does the array have? ";
	std::cin >> numberOfElements;
	std::cout << std::endl;

	std::vector<int> elements;

	for (int i = 0; i < numberOfElements; i++)
	{
		int value;
		std::cout << "Type in the values to be added to the array: ";
		std::cin >> value;
		elements.push_back(value);
	}

	std::cout << std::endl;

	std::cout << "Original array: ";
	printArray(elements);
	std::cout << std::endl << std::endl;

	//Get execution time
	auto start = std::chrono::steady_clock::now();
	int minimumNumberOfSwaps = minimumSwaps(elements);
	auto end = std::chrono::steady_clock::now();
	auto diff = end - start;

	std::cout << std::endl;
	std::cout << "Execution time: " << std::chrono::duration <double, std::milli>(diff).count() << " ms" << std::endl;

	std::cout << std::endl;
	std::cout << "Sorted array: ";
	printArray(elements);
	std::cout << std::endl;

	std::cout << std::endl;

	std::cout << "The minimum number of swaps is: " << minimumNumberOfSwaps << std::endl;

	return 0;
}