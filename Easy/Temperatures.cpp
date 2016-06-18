#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int n; // the number of temperatures to analyse
    cin >> n; cin.ignore();
    string temps; // the n temperatures expressed as integers ranging from -273 to 5526
    getline(cin, temps);
    int minTemp = 6000;

    stringstream stream(temps);
    int test;
    if (stream.rdbuf()->in_avail() == 0)
    {
        minTemp = 0;
    } 
    while(stream >> test){
        if (abs(test) < abs(minTemp))
        {
            minTemp = test;
        }
        else if (test == minTemp && test < 0)
        {
            continue;
        }
        else if(abs(test) == abs(minTemp))
        {
            minTemp = abs(test);
        }
    }
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << minTemp << endl;
}
