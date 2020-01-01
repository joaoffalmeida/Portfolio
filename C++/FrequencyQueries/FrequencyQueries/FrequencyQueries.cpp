/*
You are given 'n' queries. Each query is of the form two integers described below:

(1,x) - Insert 'x' in a data structure
(2,y) - Delete one occurence of 'y' from the data structure
(3,z) - Check if any integer is present whose frequency is exactly 'z'. If yes, 
print 1 else 0.

The queries are given in the form of a 2D array where queries[i][0] is the operation,
and queries[i][1] is the data element. Example:

Operation   Array   Output
(1,1)       [1]
(2,2)       [1]
(3,2)                   0
(1,1)       [1,1]
(1,1)       [1,1,1]
(2,1)       [1,1]
(3,2)                   1

At the end, return an array with the output.
*/

#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

vector<int> freqQuery(vector<vector<int>> queries) {
    vector<int> output;

    unordered_map<int, int> queriesRecords;
    unordered_map<int, int> countRecords;

    for (int i = 0; i < queries.size(); i++)
    {
        int op = queries[i][0];
        int elem = queries[i][1];

        if (op == 1)
        {
            //Insert
            countRecords[queriesRecords[elem]]--;
            queriesRecords[elem]++;
            countRecords[queriesRecords[elem]]++;
        }
        else if (op == 2)
        {
            //Delete
            if (queriesRecords[elem] > 0)
            {
                countRecords[queriesRecords[elem]]--;
                queriesRecords[elem]--;
                countRecords[queriesRecords[elem]]++;
            }
        }
        else
        {
            //Check
            output.push_back((countRecords[elem] > 0) ? 1 : 0);
        }
    }

    return output;
}

int main()
{
    int numberOfQueries;
    printf("How many queries do you wish to insert? ");
    cin >> numberOfQueries;

    cout << endl;

    vector<vector<int>> queries;
    vector<int> subqueries;

    for (int i = 0; i < numberOfQueries; i++)
    {
        subqueries.clear();

        int operation;
        printf("Operation for query %d: ", i + 1);
        cin >> operation;

        int element;
        printf("Element to be operated on query %d: ", i + 1);
        cin >> element;

        cout << endl;

        subqueries.push_back(operation);
        subqueries.push_back(element);

        queries.push_back(subqueries);
    }

    vector<int> output = freqQuery(queries);

    printf("Output: ");
    for (int i = 0; i < output.size(); i++)
    {
        cout << output[i] << " ";
    }

    return 0;
}