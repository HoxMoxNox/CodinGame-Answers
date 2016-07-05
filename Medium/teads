#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include<list>

using namespace std;

class Graph
{
	int V; // No. of vertices
	list<int> *adj; // Pointer to an array containing adjacency lists
	void DFSUtil(int v, bool visited[],int &level,int &maxLevel); // A function used by DFS
public:
	Graph(int V); // Constructor
	void addEdge(int v, int w); // function to add an edge to graph
	void DFS(int v, int &level,int &maxLevel); // DFS traversal of the vertices reachable from v
};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w); // Add w to v’s list.
}

void Graph::DFSUtil(int v, bool visited[], int &level,int &maxLevel)
{
    
	// Mark the current node as visited and print it
	visited[v] = true;
	
	if(maxLevel < level)
	{
	    maxLevel = level;
	}
	
	// Recur for all the vertices adjacent to this vertex
	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
		if (!visited[*i])
			DFSUtil(*i, visited, ++level,maxLevel);
			--level;
}

// DFS traversal of the vertices reachable from v. It uses recursive DFSUtil()
void Graph::DFS(int v, int &level,int &maxLevel)
{
	// Mark all the vertices as not visited
	bool *visited = new bool[V];
	for (int i = 0; i < V; i++)
		visited[i] = false;
	
	// Call the recursive helper function to print DFS traversal
	DFSUtil(v, visited, level, maxLevel);
}


//Modified the GeeksForGeeks depth first search for this problem


/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int n; // the number of adjacency relations
    cin >> n; cin.ignore();
    
    Graph g(n*2); 
	
	int minMaxLevel = 100000000;
	
	//try brute force? seems to fail at test 8
	map<int,int>edges;
	map<int,int>::iterator it;
	
	int maxConnections = 0;
    
    for (int i = 0; i < n; i++) {
        int xi; // the ID of a person which is adjacent to yi
        int yi; // the ID of a person which is adjacent to xi
        cin >> xi >> yi; cin.ignore();
        //cerr << xi << " " << yi << endl;
        g.addEdge(xi,yi);
        g.addEdge(yi,xi);
        edges[xi]++;
        
        int currentConnections = edges[xi];
        
        if(currentConnections > maxConnections)
        {
            maxConnections = currentConnections;
        }
    }
    
    
    cerr << "Largest # of connections: " << maxConnections << endl;
    //cout << 9 << endl;
    
    for(it = edges.begin(); it != edges.end(); ++it)
    {
        if(it->second >= maxConnections - 2)
        {
            int level = 0;
    	    int maxLevel = 0;
    	    g.DFS(it->first,level,maxLevel);
    	    if(maxLevel < minMaxLevel)
    	    {
    	        minMaxLevel = maxLevel;
    	    }    	    
    	   // if(maxLevel >= 9)
    	    //{
    	      //  break;
    	        //cerr << "Time to propogate from " << it->first << " is " << maxLevel << endl;
    	        //cerr << it->first << " has " << it->second << " connections" << endl;
    	        //cerr << endl;
    	   // }

        }
	    
    }
    
    // The minimal amount of steps required to completely propagate the advertisement
    cerr << "edges: " << n << endl;
    cerr << "Min level is " << minMaxLevel << endl;
    cout << minMaxLevel << endl;
}
