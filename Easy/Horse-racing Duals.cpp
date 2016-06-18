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
    int N;
    cin >> N; cin.ignore();
    vector<int> strengths(N);
    int minDifference = 10000000000;
    int difference;
    
    for (int i = 0; i < N; i++) {
        int Pi;
        cin >> Pi; cin.ignore();
        strengths[i] = Pi;
    }
    
    sort(strengths.begin(),strengths.end());
    
    for (int i = 0; i < N - 1; i++)
    {
        difference = abs(strengths[i] - strengths[i+1]);
        if(difference < minDifference)
        {
            minDifference = difference;
        }
    }
    
    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    cout << minDifference << endl;
}
