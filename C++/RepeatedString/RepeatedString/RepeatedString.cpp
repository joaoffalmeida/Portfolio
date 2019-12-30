/*
Lilah has a string, s, of lowercase English letters that she repeated 
infinitely many times.

Given an integer, n, find and print the number of letter x's in the 
first n letters of Lilah's infinite string.

For example, if the string s = 'abcac' and n = 10, and we want to find
the number of occurrences of the letter 'a', the substring we 
consider is 'abcacabcac', the first 10 characters of her infinite string. 
There are 4 occurrences of 'a' in the substring.
*/

#include <iostream>
#include <string>

long int repeatedString(std::string phrase, long long int charsToConsider, char charToFindOccurrences)
{
    long int timesToRepeatString = charsToConsider / phrase.length();
    int rest = charsToConsider % phrase.length();
    long int numberOfOccurrences = 0;

    for (int i = 0; i < phrase.length(); i++)
    {
        if (phrase[i] == charToFindOccurrences)
        {
            numberOfOccurrences++;
        }
    }

    numberOfOccurrences *= timesToRepeatString;

    for (int i = 0; i < rest; i++)
    {
        if (phrase[i] == charToFindOccurrences)
        {
            numberOfOccurrences++;
        }
    }

    return numberOfOccurrences;
}

int main()
{
    std::string phrase;
    std::cout << "Type in the string you wish to search: ";
    std::cin >> phrase;

    long int numberOfCharsToConsider;
    std::cout << "How many characters do you want to consider? ";
    std::cin >> numberOfCharsToConsider;

    char charToFind;
    std::cout << "What char do you want to find in the phrase? ";
    std::cin >> charToFind;

    long int result = repeatedString(phrase, numberOfCharsToConsider, charToFind);

    std::cout << "There are " << result << " occurrences of '" << charToFind << "' in the given string." << std::endl;

    return 0;
}