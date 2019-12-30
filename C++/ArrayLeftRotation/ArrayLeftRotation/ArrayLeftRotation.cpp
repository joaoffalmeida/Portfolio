/*
A left rotation operation on an array shifts each of the array's elements 1 unit to the 
left. For example, if 2 left rotations are performed on array [1, 2, 3, 4, 5], 
then the array would become [3, 4, 5, 1, 2].

Given an array 'a' of 'n' integers and a number, 'd', perform 'd' left rotations 
on the array. Return the updated array to be printed as a single line of 
space-separated integers.
*/

#include <iostream>
#include <vector>

std::vector<int> leftRotateArray(std::vector<int> arrayToRotate, int numberOfRotations)
{
	//PROBLEM SOLVED BY PUTTING THE ELEMENT TO ROTATE IN THE END AND DELETING FROM THE BEGINNING
	for (int i = 0; i < numberOfRotations; i++)
	{
		arrayToRotate.push_back(arrayToRotate[0]);
		arrayToRotate.erase(arrayToRotate.begin());
	}

	/* PROBLEM SOLVED BY COPYING THE ELEMENTS THAT WILL ROTATE TO ANOTHER VECTOR

	std::vector<int> rotatedArray;

	for (int i = 0; i < arrayToRotate.size(); i++)
	{
		if (i - numberOfRotations < 0)
		{
			rotatedArray.push_back(arrayToRotate[i]);
		}
	}

	arrayToRotate.erase(arrayToRotate.begin(), arrayToRotate.begin() + numberOfRotations);
	
	for (int i = 0; i < rotatedArray.size(); i++)
	{
		arrayToRotate.push_back(rotatedArray[i]);
	}*/

	return arrayToRotate;
}

void printArray(std::vector<int> arrayToPrint)
{
	std::cout << "[";
	for (int j = 0; j < arrayToPrint.size(); j++)
	{
		if (j == (arrayToPrint.size() - 1))
		{
			std::cout << arrayToPrint[j];
		}
		else
		{
			std::cout << arrayToPrint[j] << ", ";
		}
	}
	std::cout << "]" << std::endl;
}

int main()
{
	std::vector<int> arrayToRotate;

	std::cout << "Number of rotations to perform must be less than number of elements in the array." << std::endl << std::endl;

	int numberOfElements;
	std::cout << "How many elements in the array? ";
	std::cin >> numberOfElements;

	int numberOfRotations;
	std::cout << "How many rotations do you wish to perform? ";
	std::cin >> numberOfRotations;

	std::cout << std::endl;

	for (int i = 0; i < numberOfElements; i++)
	{
		int valueToInsert;
		std::cout << "Number to Insert: ";
		std::cin >> valueToInsert;
		arrayToRotate.push_back(valueToInsert);
	}

	std::vector<int> rotatedArray = leftRotateArray(arrayToRotate, numberOfRotations);

	std::cout << std::endl;

	printArray(rotatedArray);

	return 0;
}