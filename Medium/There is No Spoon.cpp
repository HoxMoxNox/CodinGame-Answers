#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Don't let the machines win. You are humanity's last hope...
 **/
int main()
{
    
    int width; // the number of cells on the X axis
    cin >> width; cin.ignore();
    int height; // the number of cells on the Y axis
    cin >> height; cin.ignore();
    
    vector< vector<char> > nodes(height, vector<char>(width));
    
    for (int i = 0; i < height; i++) {
        string line; // width characters, each either 0 or .
        getline(cin, line);
        
        //gather all the nodes into a 2d vector
        for (int j = 0; j < width; j++)
        {
            nodes[i][j] = line[j];
        }
        
    }
    
    //iterate through all nodes, any that are '.' are ignored
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            
            if (nodes[i][j] == '.')
            {
                continue;
            }
            
            cout << j << " " << i << " ";
            
            //check every node to the right of the current one, looking for a valid node
            for(int p = j + 1; p <= width;p++)
            {
                if(p >= width)
                {
                    cout << -1 << " " << -1 << " ";
                    break;
                }
                if(nodes[i][p] == '0')
                {
                    cout << p << " " << i << " ";
                    break;
                }
            }
            
             //check every node to the bottom of the current one, looking for a valid node
            for(int q = i + 1; q <= height;q++)
            {
                if(q >= height)
                {
                    cout << -1 << " " << -1;
                    break;
                }
                if(nodes[q][j] == '0')
                {
                    cout << j << " " << q;
                    break;
                }
            }
            cout << endl;
        }
    }
}
