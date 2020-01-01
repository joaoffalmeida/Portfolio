/*
You are given an array and you need to find number of tripets of indices (i, j, k) 
such that the elements at those indices are in geometric progression for 
a given common ratio 'r' and i < j < k.

For example, arr = [1, 4, 16, 64]. If r = 4, we have [1, 4, 16] and [4, 16, 64] 
at indices (0, 1, 2) and (1, 2, 3).
*/

#include <vector>
#include <iostream>
#include <map>

using namespace std;

long int countTriplets(vector<long int> arr, int ratio)
{
    long int numberOfTriplets = 0;

    map<int, long int> tripletsBankLeft;
    map<int, long int> tripletsBankRight;

    for (int i = 0; i < arr.size(); i++)
    {
        ++tripletsBankRight[arr[i]];
    }

    for (int i = 0; i < arr.size(); i++)
    {
        int a = (arr[i] / ratio);
        int currentChecking = arr[i];
        long int c = (arr[i] * ratio);

        long int counterLeft = 0;
        long int counterRight = 0;

        --tripletsBankRight[currentChecking];

        map<int, long int>::iterator itLeft = tripletsBankLeft.find(a);
        map<int, long int>::iterator itRight = tripletsBankRight.find(c);

        if (itLeft != tripletsBankLeft.end() && currentChecking % ratio == 0)
        {
            counterLeft = itLeft->second;
        }

        if (itRight != tripletsBankRight.end())
        {
            counterRight = itRight->second;
        }

        numberOfTriplets += (counterLeft * counterRight);

        ++tripletsBankLeft[currentChecking];
    }

    return numberOfTriplets;
}

int main()
{
    int sizeOfArray;
    printf("What's the size of the array? ");
    cin >> sizeOfArray;

    int ratio;
    printf("What's the ratio? ");
    cin >> ratio;

    vector<long int> valuesArray;

    cout << endl;

    for (int i = 0; i < sizeOfArray; i++)
    {
        int val;
        printf("Insert value to array: ");
        cin >> val;
        valuesArray.push_back(val);
    }

    int numberOfTriplets = countTriplets(valuesArray, ratio);

    printf("\nThere are %d triplets.", numberOfTriplets);

	return 0;
}