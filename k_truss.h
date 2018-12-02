/***********************************************
Grzegorz Kakareko
Florida State University
College of Engineering
2525 Pottsdamer Street, Tallahassee, FL 32310
Email: gk15b@my.fsu.edu - Phone: +1-850-570-4683

This is the header for the k_truss class, the header contains
the function descriptions utilized in this project. 
************************************************/
#ifndef K_TRUSS
#define K_TRUSS

#include <fstream>
#include <iostream>
#include <ctime>
#include <string>
#include <cstring>
#include <map>
#include <algorithm>
#include <cstring>
#include <vector>
#include <list>
using namespace std;

class k_truss
{
    // struct Edge - Container to hold the vertexes of an 
    // Edge for an improved algorithm
    struct Edge 
    {
        int u,v;

        friend bool operator<(Edge e1, Edge e2) 
        {
            return e1.u<e2.u || (e1.u==e2.u && e1.v<e2.v);
        }
    };

    // struct Edge - Container to hold the vertexes of an Edge
    // for the basic
    struct Edge_basic 
    {
        int u,v,d;

        friend bool operator<(Edge_basic e1, Edge_basic e2) 
        {
            return e1.d<e2.d || (e1.d==e2.d && e1.d<e2.d);
        }
    };
    list<Edge_basic> list_Edge_basic; 

    ofstream file_out;              // path to the file to be saved
    string path;                    // holds the path for the file
    string path_name;               // only the name without the .txt

    int n, m;                       // vetexes reading from the file
    vector<int> mapto;              // container that is used for sorting
    vector<int> deg, bin;           // holds the degrees for the vertexes 
    vector<Edge> binEdge;           // container for sorting
    vector<vector<int>> A;          // container for couting triangles 
    vector<map<int,int>> Adj, pos;  // Adjusted matrix for initialization

    int cntClass[1000];             // holds the classes for the 

    /***********************************************
    void init_Adj()- Initialize Adj, adjustment matrix
    ************************************************/
    void init_Adj();

    /***********************************************
    bool compVertex(int i,  int j)- check, which 
    vetex is greter
    ************************************************/
    bool compVertex(int i,  int j);

    /***********************************************
    void updateSupport(int u, int v, int delta)- 
    Update Adj, matrix adding the degrees 
    ************************************************/
    void updateSupport(int u, int v, int delta);

    /***********************************************
    void printClass(int u, int v, int cls)-
    Prints the the u, v, cls; for the edge
    ************************************************/
    void printClass(int u, int v, int cls);

    /***********************************************
    void removeEdge(int u, int v)
    Removes the edge from the Adj matrix
    ************************************************/
    void removeEdge(int u, int v);

    /***********************************************
    void orderPair(int &u, int &v)-
    swap the vertexes in order
    ************************************************/
    void orderPair(int &u, int &v);

    /***********************************************
    void intersect(const vector<int> &a, const vector<int> &b, vector<int> &c)-
    Checks which edges intersect and save them in c
    ************************************************/
    void intersect(const vector<int> &a, const vector<int> &b, vector<int> &c);

    /***********************************************
    void reorder()-
    Sort the edges in the asceending order
    ************************************************/
    void reorder();

    /***********************************************
    void countTriangles()-
    counts triangles for the each edge following
    the improved algorithm
    ************************************************/
    void countTriangles();

    /***********************************************
    void binSort()-
    Binary sorts edges based on the triangle number
    ************************************************/
    void binSort();

    /***********************************************
    void trussDecomp()-
    The main function for the improved algorithm
    for the truss decomposition
    ************************************************/
    void trussDecomp();

    /***********************************************
    void updateEdge(int u, int v, int minsup)-
    Updates the number of triangles after deleting
    the edges 
    ************************************************/
    void updateEdge(int u, int v, int minsup);

    /***********************************************
    void binSort_top_down()-
    The modyfied Bin sort used for top down decomposition
    ************************************************/
    void binSort_top_down();

    /***********************************************
    void trussDecomp_top_down()-
    The main function for the truss top down decomposition
    ************************************************/
    void trussDecomp_top_down();

    /***********************************************
    void trussDecomp_basic()-
    The function for the truss decomposition basic
    algorithm, using the list_Edge_basic
    ************************************************/
    void trussDecomp_basic();

    /***********************************************
    void update_list_Edge_basic();
    Functions updates the number of triangles for
    each edge after the decomposition
    ************************************************/
    void update_list_Edge_basic();

    /***********************************************
    void print_list_Edge_basic()-
    utilities function only for debuging to print
    the current list of edges
    ************************************************/
    void print_list_Edge_basic();

    
public:
    /***********************************************
    k_truss(string fn);
    Constructor for the class that initialize the path
    ************************************************/
    k_truss(string fn);

    /***********************************************
    ~k_truss(); 
    Destructor, that does nothing, no dynamicly 
    alocated matrix
    ************************************************/
    ~k_truss(); 

    /***********************************************
    string basic_truss_decomp();  
    The main function for the basic algorithm for truss
    decomposition
    ************************************************/
    string basic_truss_decomp();  

    /***********************************************
    string improved_truss_decomp();
    The main function for the improved truss decomposition
    ************************************************/  
    string improved_truss_decomp();

    /***********************************************
    string top_down_decomp();
    The main function for the top down truss decomposition
    ************************************************/  
    string top_down_decomp();
    

};
#endif