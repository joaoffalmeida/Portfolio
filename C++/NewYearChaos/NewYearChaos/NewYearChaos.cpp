/*
It's New Year's Day and everyone's in line for the Wonderland rollercoaster ride! 
There are a number of people queued up, and each person wears a sticker indicating 
their initial position in the queue. Initial positions increment by 1 from 1 at the 
front of the line to 'n' at the back.

Any person in the queue can bribe the person directly in front of them to swap positions. 
If two people swap positions, they still wear the same sticker denoting their original 
places in line. One person can bribe AT MOST two others. For example, if n = 8 and 
Person 5 bribes Person 4, the queue will look like this: 1, 2, 3, 5, 4, 6, 7, 8.

Fascinated by this chaotic queue, you decide you must know the minimum number of bribes 
that took place to get the queue into its current state!
*/

#include <iostream>
#include <vector>
#include <algorithm>

void minimumBribes(std::vector<int> queue)
{
	int numberOfBribes = 0;

	for (int i = 0; i < queue.size(); i++)
	{
		int personToCheck = queue[i];
		if (personToCheck - i - 1 > 2)
		{
			std::cout << "Rules of bribing have been broken!" << std::endl;
			return;
		}

		for (int j = std::max(0, (personToCheck - 2)); j <= i; j++)
		{
			if (queue[j] > personToCheck)
			{
				numberOfBribes++;
			}
		}
	}

	std::cout << "Minimum number of bribes: " << numberOfBribes << std::endl;
}

int main()
{
	int numberOfTestCases;
	std::cout << "How many test cases do you wish to perform? ";
	std::cin >> numberOfTestCases;

	std::cout << std::endl;

	std::vector<int> queue;

	for (int i = 1; i <= numberOfTestCases; i++)
	{
		queue.clear();

		int numberOfPeopleInTheQueue;
		std::cout << "How many people are in the queue for test case " << i << "? ";
		std::cin >> numberOfPeopleInTheQueue;

		std::cout << std::endl;

		for (int j = 1; j <= numberOfPeopleInTheQueue; j++)
		{
			int personx;
			std::cout << "Who's on position " << j << "? ";
			std::cin >> personx;

			queue.push_back(personx);
		}

		std::cout << std::endl;

		minimumBribes(queue);

		std::cout << std::endl;
		std::cout << "---------------------------------" << std::endl;
		std::cout << std::endl;
	}

	return 0;
}