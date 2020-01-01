/*
Harold is a kidnapper who wrote a ransom note, but now he is worried it will be 
traced back to him through his handwriting. He found a magazine and wants to know 
if he can cut out whole words from it and use them to create an untraceable replica 
of his ransom note. The words in his note are case-sensitive and he must use only 
whole words available in the magazine. He cannot use substrings or concatenation to 
create the words he needs.

Given the words in the magazine and the words in the ransom note, print "Yes" if he can 
replicate his ransom note exactly using whole words from the magazine; otherwise, 
print "No".

For example, the note is "Attack at dawn". The magazine contains only "attack at dawn". 
The magazine has all the right words, but there's a case mismatch. The answer is "No".
*/

#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

void checkMagazine(vector<string> magazineWords, vector<string> noteWords)
{
	map<string, int> bankWords;

	//populating the map
	for (string magazineWord : magazineWords) 
	{
		++bankWords[magazineWord];
	}

	//checking for correspondences
	for (string noteWord : noteWords) 
	{
		if (--bankWords[noteWord] < 0)
		{ 
			cout << "There is no match." << endl; 
			return;
		}
	}

	cout << "There is a match!" << endl;
}

void splitStringToVec(string& stringToSplit, vector<string>& vecToReceiveSplits)
{
	int counter = 0;
	int tracker = 0;

	stringToSplit += " ";

	for (int i = 0; i < stringToSplit.length(); i++)
	{
		string x = "";
		if (stringToSplit[i] == ' ')
		{
			for (int j = tracker; j < i; j++)
			{
				x = x + stringToSplit[j];
				tracker = i + 1;
			}

			vecToReceiveSplits.push_back(x);
		}
	}
}

int main()
{
	string magazineText;
	cout << "Magazine sentence: ";
	getline(cin,magazineText);


	string noteText;
	cout << "Note sentence: ";
	getline(cin, noteText);

	vector<string> magazineWords;
	vector<string> noteWords;

	splitStringToVec(magazineText, magazineWords);
	splitStringToVec(noteText, noteWords);

	cout << endl;

    checkMagazine(magazineWords, noteWords);

	return 0;
}