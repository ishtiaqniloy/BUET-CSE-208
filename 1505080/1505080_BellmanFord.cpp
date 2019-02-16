#include<stdio.h>
#include<stdlib.h>
#include <fstream>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

class Edge{     ///weighted graph edge
public:
    int node;
    int weight;

    Edge(int n=0, int w=0){
        node= n;
        weight = w;
    }
};

///****************Dynamic ArrayList class based************************
class ArrayList
{
	Edge * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int nd) ;
    void insertItem(Edge item) ;
	void removeItem(int nd) ;
	void removeItemAt(int position);
	Edge getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new Edge[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(Edge newitem)
{
	Edge * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = new Edge[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
}

int ArrayList::searchItem(int nd)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i].node == nd ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(int nd)
{
	int position;
	position = searchItem(nd) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}


Edge ArrayList::getItem(int position)
{
	if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("(%d,%d) ", list[i].node, list[i].weight);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

///******************ArrayList class ends here*************************

///******************Graph class starts here**************************
class Graph{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
	//you must use pointers and dynamic allocation
	int * color;    //define other variables required for bfs such as color, parent, and dist
	int * parent;
	int * dist;

	int time;
	int * discoveryTime;
	int * finishTime;
    //void dfsVisit(int u);


public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v, int w);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    void printGraph();
    int edgeWeight(int u, int v);
    bool bellmanFord(int source);

};

Graph::Graph(bool dir){
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	directed = dir ; //set direction of the graph

	color = 0;
	parent = 0;
	dist = 0;

	time = -1;
	discoveryTime = 0;
	finishTime = 0;

	//define other variables to be initialized
}

void Graph::setnVertices(int n){
	this->nVertices = n ;
	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices] ;
}

void Graph::addEdge(int u, int v, int w){      ///opt 1
    if(u<0 || v<0 || u>=nVertices || v>=nVertices || u==v) {
        printf("Invalid Operation...\n");
        return;
    }
    this->nEdges++ ;
    Edge e;
    e.node = v;
    e.weight = w;
	adjList[u].insertItem(e) ;
	e.node = u;
	if(!directed) adjList[v].insertItem(e) ;
}

void Graph::removeEdge(int u, int v){       ///opt 2
    //write this function
    if(u<0 || v<0 || u>=nVertices || v>=nVertices || !isEdge(u,v)) {
        printf("Invalid Operation...\n");
        return;
    }

    this->nEdges--;
	adjList[u].removeItem(v) ;
	if(!directed) adjList[v].removeItem(u);

}

bool Graph::isEdge(int u, int v){       ///opt 3
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || v<0 || u>=nVertices || v>=nVertices)  return false;
    else if( adjList[u].searchItem(v) == NULL_VALUE)    return false;
    else    return true;

}

int Graph::edgeWeight(int u, int v){
    if(u<0 || v<0 || u>=nVertices || v>=nVertices || !isEdge(u,v)) {
        return -1;
    }

    int p = adjList[u].searchItem(v);
    Edge e = adjList[u].getItem(p);

    return e.weight;
}


int Graph::getDegree(int u){        ///opt 4
    //returns the degree of vertex u
    if(u<0 || u>=nVertices)  return NULL_VALUE;
    return adjList[u].getLength();
}

void Graph::printGraph(){       ///opt 9
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i+1);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" (%d,%d)", adjList[i].getItem(j).node+1, adjList[i].getItem(j).weight);
        }
        printf("\n");
    }
}

Graph::~Graph(){
    //write your destructor here
    printf("Destroying...\n");

    if(adjList!=0){
         delete  []adjList;
        adjList= 0;
    }

    if(color!=0){
        delete []color;
        color = 0;
        delete []parent;
        parent = 0;
    }
    if(dist!=0){
        delete []dist;
        dist = 0;
    }

    if(discoveryTime!=0){
        delete []discoveryTime;
        discoveryTime = 0;
        delete []finishTime;
        finishTime = 0;
    }

}

bool Graph::bellmanFord(int source){
    if(source<0 || source>=nVertices){
        printf("INVALID SOURCE\n");
        return false;
    }

    int parent[nVertices];
    int distance[nVertices];
    for(int i=0; i< nVertices; i++){
        parent[i]=-1;
        distance[i]=INFINITY;
    }
    distance[source] = 0;
    Edge e;
    int  len;
    bool negCycle = false;

    for(int i=0; i<nVertices-1; i++){
        for(int u=0; u<nVertices; u++){
            len = adjList[u].getLength();
            for(int k=0; k<len; k++){
                e = adjList[u].getItem(k);
                if(distance[e.node]>distance[u]+e.weight){
                    distance[e.node]=distance[u]+e.weight;
                    parent[e.node]=u;
                }
            }
        }
    }

    printf("\n***Bellman-Ford Algorithm Output***\n");
    printf("Source = %d\n", source+1);
    printf("V\t\t V.d \t\t V.pi\n");
    for(int i=0; i<nVertices; i++){
        printf("%d\t\t %d \t\t", i+1, distance[i]);
        if(parent[i]==-1)   printf("NIL\n");
        else    printf("%d\n", parent[i]+1);
    }

    for(int u=0; u<nVertices; u++){
        len = adjList[u].getLength();
        for(int k=0; k<len; k++){
            e = adjList[u].getItem(k);
            if(distance[e.node]>distance[u]+e.weight){
                negCycle=true;
                break;
            }
        }
    }

    printf("Negative cycle: ");
    if(negCycle)    printf("YES\n");
    else    printf("NO\n");

    return negCycle;

}

//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    FILE *fp;
    fp= fopen("input.txt", "r");
    if(fp==NULL){
        printf("ERROR OPENING FILE\n");
        exit(0);
    }

    int n,m;
    Graph g(true);

    fscanf(fp, "%d", &n);
    g.setnVertices(n);
    fscanf(fp, "%d", &m);

    int u,v,w;
    for(int i=0; i<m; i++){
        fscanf(fp, "%d %d %d", &u, &v, &w);
        g.addEdge(u-1,v-1,w);
    }

    g.printGraph();

    printf("Please enter the source: ");
    int source;
    scanf("%d", &source);

    g.bellmanFord(source-1);

    return 0;

}


