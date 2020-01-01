/*
Given two strings, determine if they share a common substring. 
A substring may be as small as one character.

For example, the words "a", "and", "art" share the common substring 'a'. 
The words "be" and "cat" do not share a substring.
*/

#include <string>
#include <iostream>
#include <set>

using namespace std;

string twoStrings(string stringOne, string stringTwo)
{
	set<char> charBank;

	for (char c : stringOne)
	{
		charBank.insert(c);
	}

	for (char k : stringTwo)
	{
		set<char>::iterator it = charBank.find(k);
		if (it != charBank.end())
		{
			return "Both words have letters in common.";
		}
	}

	return "There are no common letters among the two strings.";
}

int main()
{
	int numberOfTestCases;
	printf("How many test cases do you wish to perform? ");
	cin >> numberOfTestCases;

	cout << endl;

	for (int i = 0; i < numberOfTestCases; i++)
	{
		string wordOne, wordTwo;
		printf("Word 1 to compare on test case %d: ", i + 1);
		cin >> wordOne;

		printf("Word 2 to compare on test case %d: ", i + 1);
		cin >> wordTwo;

		cout << endl;
		string checkPair = twoStrings(wordOne, wordTwo);
		
		cout << checkPair << endl;
		printf("--------------------------------------\n");
	}

	return 0;
}