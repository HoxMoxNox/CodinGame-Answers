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
    int N; // Number of elements which make up the association table.
    cin >> N; cin.ignore();
    int Q; // Number Q of file names to be analyzed.
    cin >> Q; cin.ignore();
    
    vector<string> mime(N);
    vector<string> extensions(N);
    vector<int> answers(Q);
        
    for (int i = 0; i < N; i++) {
        string EXT; // file extension
        string MT; // MIME type.
        cin >> EXT >> MT; cin.ignore();
        transform(EXT.begin(),EXT.end(),EXT.begin(),::tolower);
        mime[i] = MT;
        extensions[i] = EXT;
    }
    
    int currentFile = 0;
    
    cerr << endl;
    
    while(true)
    {
        //set it automatically to -1 in case the file has an unknown extension
        answers[currentFile] = -1;
        
        string FILE;
        
        if(!getline(cin,FILE))
        {
            break;
        }
        
        //Check that the string has a period
        if(FILE.find(".") == string::npos)
        {
            currentFile++;
            continue;
        }
        

        istringstream fileStream(FILE);
        string FILE_EXT;
        while(fileStream)
        {
            if(!getline(fileStream,FILE_EXT,'.'))
            {
                break;
            }         
        }
        
        //Now search for the file extension in the mime vector
        
        //First lowercase the extension to disregard case
        transform(FILE_EXT.begin(),FILE_EXT.end(),FILE_EXT.begin(),::tolower);
        
        for(int i = 0; i < extensions.size(); i++)
        {      
            //if strings are equal, output is 0         
            if(!extensions[i].compare(FILE_EXT))
            {
                answers[currentFile] = i;
                break;
            }
        }
        
        currentFile++; 
    }
    
    //Now print out answers
    // For each of the Q filenames, display on a line the corresponding MIME type. If there is no corresponding type, then display UNKNOWN.
    for (int i = 0; i < answers.size(); i++)
    {
        int mimeIndex = answers[i];
        if (mimeIndex < 0)
        {
            cout << "UNKNOWN" << endl;
        }
        else
        {
            cout << mime[mimeIndex] << endl;
        }
    }
    
    
    
    
    

}
