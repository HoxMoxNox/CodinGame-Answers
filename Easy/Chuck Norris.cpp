#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <bitset>
#include <typeinfo>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    string MESSAGE;
    getline(cin, MESSAGE);
    
    constexpr int ASCII_BIN_SIZE = 7;
    string answer = "";
    
    //Convert to binary string
    string bMessage = "";
    for (int i = 0; i < MESSAGE.size(); i++)
    {
        bMessage.append(bitset<ASCII_BIN_SIZE>((int)MESSAGE[i]).to_string());
    }
    
    //Encode
    int j = 0;
    while(j < bMessage.size())
    {
        if (bMessage[j] == '1')
        {
            answer.append("0 ");
            while(bMessage[j] == '1')
            {
                answer.append("0");
                j++;
            }
            
            if (j < bMessage.size())
            {
            answer.append(" ");                
            }
            
        }
        else if (bMessage[j] == '0')
        {
            answer.append("00 ");
            while(bMessage[j] == '0')
            {
                answer.append("0");
                j++;
            }
            
            if (j < bMessage.size())
            {
            answer.append(" ");                
            }
        }
    }

    cout << answer << endl;
}
