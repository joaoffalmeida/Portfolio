/*
Given some X by X 2D array, We define an hourglass in the array to be a subset of 
values with indices falling in this pattern in the array's graphical representation:

a b c
  d
e f g

An hourglass sum is the sum of an hourglass' values. Calculate the hourglass sum 
for every hourglass in the array, then print the maximum hourglass sum.
*/

#include <iostream>
#include <vector>

void print2DArray(std::vector<std::vector<int>> arr)
{
    for (int i = 0; i < arr.size(); ++i)
    {
        for (int j = 0; j < arr.size(); ++j)
        {
            std::cout << arr[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

int hourglassSum(std::vector<std::vector<int>> arr)
{
    int maxHourglassSum = INT_MIN;

    for (int i = 0; i < arr.size() - 2; i++)
    {
        for (int j = 0; j < arr.size() - 2; j++)
        {
            int a = arr[i][j];
            int b = arr[i][j + 1];
            int c = arr[i][j + 2];
            int d = arr[i + 1][j + 1];
            int e = arr[i + 2][j];
            int f = arr[i + 2][j + 1];
            int g = arr[i + 2][j + 2];

            int sum = a + b + c + d + e + f + g;

            if (sum > maxHourglassSum)
            {
                maxHourglassSum = sum;
            }
        }
    }

    return maxHourglassSum;
}

int main()
{
    int rows;
    std::cout << "How many rows does your 2D array has? ";
    std::cin >> rows;

    int columns;
    std::cout << "How many columns does your 2D array has? ";
    std::cin >> columns;
    std::cout << std::endl;

    std::vector<std::vector<int>> arr(rows);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            int value;
            std::cout << "Value for 2D array at pos(" << i + 1 << ", " << j + 1 << "): ";
            std::cin >> value;
            arr[i].push_back(value);
        }
    }

    std::cout << std::endl;

    print2DArray(arr);

    std::cout << std::endl;

    int result = hourglassSum(arr);

    std::cout << "The maximum hourglass sum is: " << result << std::endl;

    return 0;
}