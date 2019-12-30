/*
PROBLEM:
You are in charge of the cake for your niece's birthday and have decided 
the cake will have one candle for each year of her total age. When she blows 
out the candles, she’ll only be able to blow out the tallest ones. Your task 
is to find out how many candles she can successfully blow out.
*/

#include <iostream>
#include <vector>

int birthdayCakeCandle(std::vector<int> candlesArray) {
	
	int tallestCandle = 0;

	for (int i = 0; i < candlesArray.size(); i++) {
		int candleBeingAnalyzed = candlesArray[i];
		if (candleBeingAnalyzed >= tallestCandle) {
			tallestCandle = candleBeingAnalyzed;
		}
	}

	int numberOfCandlesToBlow = std::count(candlesArray.begin(), candlesArray.end(), tallestCandle);

	return numberOfCandlesToBlow;
}

int main() {

	int noOfCandlesToBlow;
	int nieceAge;
	std::cout << "What's your niece's age? ";
	std::cin >> nieceAge;
	std::cout << std::endl;

	std::vector<int> candlesHeightArray;

	for (int i = 0; i < nieceAge; i++) {
		int candleHeight;
		std::cout << "Type in the height of the candles: ";
		std::cin >> candleHeight;
		candlesHeightArray.push_back(candleHeight);
	}
	std::cout << std::endl;

	noOfCandlesToBlow = birthdayCakeCandle(candlesHeightArray);

	std::cout << "There are " << noOfCandlesToBlow << " candles to blow." << std::endl;

	return 0;
}