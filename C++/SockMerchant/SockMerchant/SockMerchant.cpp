/*
John works at a clothing store. He has a large pile of socks that he must pair 
by color for sale. Given an array of integers representing the color of each sock, 
determine how many pairs of socks with matching colors there are.

For example, there are n = 7 socks with colors ar = ["orange", "blue", "orange", "blue",
"orange", "purple", "blue"]. There is one pair of color "orange" and one of color 
"blue". There are three odd socks left, one of each color. The number of pairs is 2.
*/

#include <iostream>
#include <vector>
#include <set>

int sockMerchant(std::vector<std::string> colors)
{
	std::set<std::string> sockPairs;

	int numberOfPairs = 0;

	for (int i = 0; i < colors.size(); i++)
	{
		std::string currentSock = colors[i];
		if (sockPairs.find(currentSock) != sockPairs.end())
		{
			numberOfPairs++;
			sockPairs.erase(currentSock);
		}
		else
		{
			sockPairs.insert(currentSock);
		}
	}

	return numberOfPairs;
}

int main()
{
	int numberOfSocks;
	std::cout << "How many socks are in the pile? ";
	std::cin >> numberOfSocks;

	std::vector<std::string> sockColors;

	for (int i = 0; i < numberOfSocks; i++)
	{
		std::string sockColor;
		std::cout << "What's the color of the sock number " << i + 1 << "? ";
		std::cin >> sockColor;

		sockColors.push_back(sockColor);
	}

	int totalNumberOfPairs = sockMerchant(sockColors);

	if (totalNumberOfPairs < 1)
	{
		std::cout << "There are no pairs in the pile." << std::endl;
	}
	else if (totalNumberOfPairs == 1)
	{
		std::cout << "There is 1 pair of socks in the pile." << std::endl;
	}
	else
	{
		std::cout << "There are " << totalNumberOfPairs << " pairs of socks in the pile." << std::endl;
	}

	return 0;
}