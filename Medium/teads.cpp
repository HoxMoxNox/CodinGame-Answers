#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <list>

using namespace std;

// This class represents a directed graph using adjacency list representation
class Graph
{
    int V;    // No. of vertices
    list<int> *adj;    // Pointer to an array containing adjacency lists
public:
    Graph(int V);  // Constructor
    void addEdge(int v, int w); // function to add an edge to graph
    int BFS(int s);  // prints BFS traversal from a given source s
    int BFS_D(int s,int d); //returns distance from s to d
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
 
int Graph::BFS(int s)
{
    
    int farthestNode;
    
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;
 
    // Create a queue for BFS
    list<int> queue;
 
    // Mark the current node as visited and enqueue it
    visited[s] = true;
    queue.push_back(s);
 
    // 'i' will be used to get all adjacent vertices of a vertex
    list<int>::iterator i;
 
    while(!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        s = queue.front();
        //cout << s << " ";
        queue.pop_front();
        
        if(queue.empty())
        {
            farthestNode = s;
        }
 
        // Get all adjacent vertices of the dequeued vertex s
        // If a adjacent has not been visited, then mark it visited
        // and enqueue it
        for(i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if(!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
    
    return farthestNode;
    
}

int Graph::BFS_D(int s,int d)
{
    //cerr << "S: " << s << " D: " << d << endl;
    int dist = 0;
    
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;
 
    // Create a queue for BFS
    list<int> queue;
    
    //distance queue
    list<int> queueD;
 
    // Mark the current node as visited and enqueue it
    visited[s] = true;
    queue.push_back(s);
    
    //mark initial distance
    queueD.push_back(dist);
 
    // 'i' will be used to get all adjacent vertices of a vertex
    list<int>::iterator i;
 
    while(!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        s = queue.front();
        //cout << s << " ";
        queue.pop_front();
        
        dist = queueD.front();
        //cerr << "current dist: " << dist << endl;
        queueD.pop_front();
        
        if(s == d)
        {
            return dist;
        }
 
        // Get all adjacent vertices of the dequeued vertex s
        // If a adjacent has not been visited, then mark it visited
        // and enqueue it
        for(i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if(!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
                queueD.push_back(dist+1);
            }
        }
    }
    
    return -1; // never found node, shouldn't reach this
    
}

//Modified the GeeksForGeeks breadth first search for this problem


/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    int n; // the number of adjacency relations
    cin >> n; cin.ignore();
    
    Graph g(n*2); 
    
    int diameter,radius,startingNode,u,v;

    for (int i = 0; i < n; i++) {
        int xi; // the ID of a person which is adjacent to yi
        int yi; // the ID of a person which is adjacent to xi
        cin >> xi >> yi; cin.ignore();
        //cerr << xi << " " << yi << endl;
        g.addEdge(xi,yi);
        g.addEdge(yi,xi);
        startingNode = xi;
    }
    
    u = g.BFS(startingNode);
    v = g.BFS(u); //length between these two is the diameter
    //cerr << "u: " << u << " v: " << v << endl;
    
    diameter = g.BFS_D(u,v);
    //cerr << "Diameter: " << diameter << endl;
    radius = (int)(ceil(diameter/2.0));
    //cerr << "Radius: " << radius << endl;
    cout << radius << endl;
    
    
}



