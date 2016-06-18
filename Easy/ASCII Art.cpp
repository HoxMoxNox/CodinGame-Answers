#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <locale>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int L;
    cin >> L; cin.ignore();
    int H;
    cin >> H; cin.ignore();
    string T;
    getline(cin, T);
    
    constexpr int ASCII_LENGTH = 26;
    constexpr int ASCII_SHIFT_TO_ZERO = 65;
    string myAnswer = "";
    
    transform(T.begin(),T.end(),T.begin(),::toupper);
    
    for (int i = 0; i < H; i++) {
        
        string ROW;
        getline(cin, ROW);
        
        for(int j = 0; j < T.size();j++)
        {
            if (isalpha(T[j]))
            {   
                myAnswer.append(ROW, L * ((int)T[j]-ASCII_SHIFT_TO_ZERO) , L);
            }
            else
            {
                myAnswer.append(ROW,ASCII_LENGTH*L,L);
            }         
        }
        myAnswer.append("\n");      
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;
    cout << myAnswer<< endl;
}

