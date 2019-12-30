/*
Starting with a 1-indexed array of zeros and a list of operations, for each operation 
add a value to each of the array element between two given indices, inclusive. 
Once all operations have been performed, return the maximum value in your array.

For example, the length of your array of zeros n = 10. Your list of queries is as 
follows:

	a b k
	1 5 3
	4 8 7
	6 9 1

Add the values of k between the indices a and b inclusive:

index->	 1 2 3  4  5 6 7 8 9 10
	    [0,0,0, 0, 0,0,0,0,0, 0]
	    [3,3,3, 3, 3,0,0,0,0, 0]
	    [3,3,3,10,10,7,7,7,0, 0]
	    [3,3,3,10,10,8,8,8,1, 0]

The largest value is 10 after all operations are performed.
*/

#include <iostream>
#include <vector>

long int arrayManipulation(int numberElementsInArray, std::vector<std::vector<int>> queries)
{
	long int maxValue = 0, diffSum = 0;

	std::vector<int> vectorOfElements(numberElementsInArray + 1);

	for (int i = 0; i < queries.size(); i++)
	{
		long int a = queries[i][0];
		long int b = queries[i][1];
		long int k = queries[i][2];

		vectorOfElements[a] += k;
		if ((b + 1) <= numberElementsInArray)
		{
			vectorOfElements[b + 1] -= k;
		}
	}

	for (int i = 1; i <= numberElementsInArray; i++)
	{
		diffSum += vectorOfElements[i];

		if (diffSum > maxValue)
		{
			maxValue = diffSum;
		}
	}

	return maxValue;
}

int main()
{
	int sizeOfArray;
	std::cout << "What's the size of the array? ";
	std::cin >> sizeOfArray;

	int numberOfOperations;
	std::cout << "How many operations are there? ";
	std::cin >> numberOfOperations;

	std::vector<std::vector<int>> queries;
	std::vector<int> intermediateQuerie;

	std::vector<int> test(sizeOfArray);

	for (int i = 0; i < numberOfOperations; i++)
	{
		intermediateQuerie.clear();
		int a, b, k;
		std::cout << "For operation number " << i + 1 << " type in the values for a, b and k respectively." << std::endl;
		std::cin >> a >> b >> k;
		intermediateQuerie.push_back(a);
		intermediateQuerie.push_back(b);
		intermediateQuerie.push_back(k);
		queries.push_back(intermediateQuerie);
	}


	int maxValue = arrayManipulation(sizeOfArray, queries);

	std::cout << std::endl << std::endl;

	std::cout << "The maximum value is: " << maxValue << std::endl;
	
	return 0;
}