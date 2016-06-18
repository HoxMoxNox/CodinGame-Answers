#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int maxHeight = 0;
    int mountain = 0;

    // game loop
    while (1) {
        for (int i = 0; i < 8; i++) {
            int mountainH; // represents the height of one mountain, from 9 to 0.
            cin >> mountainH; cin.ignore();
            if (mountainH > maxHeight)
            {
                maxHeight = mountainH;
                mountain = i;
            }
            
        }

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        cout << mountain << endl; // The number of the mountain to fire on.
        maxHeight = 0;
    }
}
