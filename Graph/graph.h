#ifndef GRAPH_H
#define GRAPH_H

//#include <stack>
#include <string>
//#include <vector>
//#include <queue>
#include <algorithm>
using std::string;
//using std::stack;
//using std::vector;
//using std::queue;

#include "myVector.cpp"


class graph
{
public:
    struct edge
    {
        bool mark;
        int vertex[2];
        int path[2];
        int cost;
        edge(int v1 = -1,int v2 = -1,int p1 = -1,int p2 = -1,int c = 0,bool m = false):mark(m),cost(c){
            vertex[0] = v1;
            vertex[1] = v2;
            path[0] = p1;
            path[1] =p2;
        }
    };
    struct vertex
    {
        string name;
        int to;
        bool mark;
        int level;
        int x;
        int y;
        vertex(string name = "", int to = -1,bool mark = false,int level = 0,int x = 0, int y = 0):name(name),to(to),mark(mark),level(level),x(x),y(y){}
    };
    graph();
    ~graph();

    void sortBylevel();
    static bool cmpBylevel(vertex,vertex);

    bool judgeOddPoint(int x,int y);
    void setOnePathin(int);

    void pushVertex(string);
    void pushVertex(vertex);
    void pushEdge(string,string,int);
    myVector<edge> getEdge();
    myVector<vertex> getVertex();
    myVector<vertex> olds;
    graph DFS(string);
    graph BFS(string);
    
    friend class mypainter;
private:
    myVector<edge> _edge;
    myVector<vertex> _vertex;
};

#endif // GRAPH_H
