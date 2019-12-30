/*
Emma is playing a new mobile game that starts with consecutively numbered clouds. 
Some of the clouds are thunderheads and others are cumulus. She can jump on any 
cumulus cloud having a number that is equal to the number of the current cloud 
plus 1 or 2. She must avoid the thunderheads. Determine the minimum number of 
jumps it will take Emma to jump from her starting position to the last cloud. 
It is always possible to win the game.

For each game, Emma will get an array of clouds numbered  if they are safe or  if 
they must be avoided. For example, c = [0, 1, 0, 0, 0, 1,0] indexed from 0 ... 6. 
The number on each cloud is its index in the list so she must avoid the clouds at 
indexes 1 and 5. She could follow the following two paths: 0 -> 2 -> 4 -> 6 or 
0 -> 2 -> 3 -> 4 -> 6. The first path takes 3 jumps while the second takes 4.
*/

#include <iostream>
#include <vector>

int jumpingOnClouds(std::vector<int> &clouds)
{
	std::vector<int> jumpableClouds;
	std::vector<int>::iterator itr;
	
	int numberOfJumps = 0;

	int currentCloud = 0;

	for (int i = 1; i < clouds.size(); i++)
	{
		if (clouds[i] == 0)
		{
			jumpableClouds.push_back(i);
		}
	}

	while (currentCloud != clouds.size() - 1)
	{
		itr = std::find(jumpableClouds.begin(), jumpableClouds.end(), currentCloud + 2);
		if (itr != jumpableClouds.end())
		{
			currentCloud += 2;
		}
		else
		{
			currentCloud++;
		}

		numberOfJumps++;
	}

	return numberOfJumps;
}

int main() 
{
	int minimumNumberOfJumps = 0;
	int numberOfClouds;
	std::cout << "How many clouds are there? ";
	std::cin >> numberOfClouds;

	std::vector<int> clouds;

	for (int i = 0; i < numberOfClouds; i++)
	{
		int cloudValue;
		std::cout << "Define the clouds value (0 = good; 1 = bad): ";
		std::cin >> cloudValue;
		clouds.push_back(cloudValue);
		std::cout << std::endl;
	}

	minimumNumberOfJumps = jumpingOnClouds(clouds);

	std::cout << "There will be at least " << minimumNumberOfJumps << " jumps to win the game." << std::endl;

	return 0;
}