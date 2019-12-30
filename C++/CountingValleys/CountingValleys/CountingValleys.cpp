/*
Gary is an avid hiker. He tracks his hikes meticulously, paying close 
attention to small details like topography. During his last hike he took 
exactly  steps. For every step he took, he noted if it was an uphill, U, 
or a downhill, D step. Gary's hikes start and end at sea level and each step 
up or down represents a  unit change in altitude. We define the following terms:

A mountain is a sequence of consecutive steps above sea level, starting 
with a step up from sea level and ending with a step down to sea level.

A valley is a sequence of consecutive steps below sea level, starting with a 
step down from sea level and ending with a step up to sea level.

Given Gary's sequence of up and down steps during his last hike, 
find and print the number of valleys he walked through.

For example, if Gary's path is p = [DDUUUUDD], he first enters a valley 2 units 
deep. Then he climbs out an up onto a mountain  units high. Finally, he 
returns to sea level and ends his hike.
*/

#include <iostream>
#include <string>

using namespace std;

int numberOfValleysWalked(int steps, string path) {
    int noOfValleysWalked = 0;
    int height = 0;

    if (steps == path.size())
    {
        for (int i = 0; i < path.size(); i++) {
            if (path[i] == 'U') {
                height++;
            }
            else if (path[i] == 'D') {
                if (height == 0) {
                    noOfValleysWalked++;
                }
                height--;
            }
            else {
                cout << "Path can only contain 'D' or 'U'. Please check your path again.\n";
            }
        }
    } else {
        cout << "The number of steps and the path description do not match.\n";
    }

    return noOfValleysWalked;
}

int main()
{
    int numberOfSteps;
    cout << "How many steps have you done? ";
    cin >> numberOfSteps;
    string pathDescription;
    cout << "Type in your path: ";
    cin >> pathDescription;

    int valleysWalked = numberOfValleysWalked(numberOfSteps, pathDescription);

    cout << "You've walked " << valleysWalked << " valleys." << endl;
}