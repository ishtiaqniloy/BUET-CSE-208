#include<stdio.h>
#include<stdlib.h>
#include <fstream>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int item) ;
    void insertItem(int item) ;
	void removeItem(int item) ;
	void removeItemAt(int item);
	int getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = new int[listMaxSize] ;
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

int ArrayList::searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}


int ArrayList::getItem(int position)
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
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
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
    void dfsVisit(int u);


public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph
	void dfs(); //will run dfs in the graph
	bool isConnected();
	bool isTree();
	void isConnTree();
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

void Graph::addEdge(int u, int v){      ///opt 1
    if(u<0 || v<0 || u>=nVertices || v>=nVertices || isEdge(u,v) || u==v) {
        printf("Invalid Operation...\n");
        return;
    }
    this->nEdges++ ;
	adjList[u].insertItem(v) ;
	if(!directed) adjList[v].insertItem(u) ;
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

int Graph::getDegree(int u){        ///opt 4
    //returns the degree of vertex u
    if(u<0 || u>=nVertices)  return NULL_VALUE;
    return adjList[u].getLength();
}

bool Graph::hasCommonAdjacent(int u, int v){        ///opt 5
    //returns true if vertices u and v have common adjacent vertices
    int m[nVertices];
    for(int i=0; i<nVertices; i++)  m[i] = 0;

    if(u<0 || v<0 || u>=nVertices || v>=nVertices)  return  false;

    int len = adjList[u].getLength();
    for(int i=0; i<len; i++){
        int ver = adjList[u].getItem(i);
        if(ver==v)  continue;
        m[ver] = 1;
    }

    len = adjList[v].getLength();
    for(int i=0; i<len; i++){
        int ver = adjList[v].getItem(i);
        if(ver==u)  continue;
        if(m[ver] == 1)   return true;
    }

    return false;

}

void Graph::bfs(int source){       ///opt 6
    //complete this function
    if(source<0 || source>=nVertices){
        printf("Invalid Source\n");
        return;
    }

    if(color==0){
        color = new int[nVertices];
        parent = new int[nVertices];
    }
    if(dist == 0){
        dist = new int[nVertices];
    }

    for(int i=0; i<nVertices; i++){     //initialize BFS variables
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;

    color[source] = GREY;
    dist[source] = 0 ;
    q.enqueue(source) ;

    int u, v, len;
    while( !q.empty() ){
        //complete this part
        u = q.dequeue();
        len = adjList[u].getLength();
        for(int i=0; i<len; i++){
            v = adjList[u].getItem(i);
            if(color[v] == WHITE){
                color[v] = GREY;
                dist[v] = dist[u]+1;
                //printf("Distance of %d = %d\n", v, dist[v]);
                parent[v] = u;
                q.enqueue(v);
            }
        }
        color[u]= BLACK;
    }

    /*printf("\n*****BFS OUTPUT*****\n");
    printf("        Parents     Distance\n");
    for(int i=0; i<nVertices; i++){
    printf("%d :      %d            %d\n", i, parent[i], dist[i]);
    }*/



}

void Graph::dfs(){          ///opt 8
    //write this function
    if(color==0){
        color = new int[nVertices];
        parent = new int[nVertices];
    }
    if(discoveryTime==0){
        discoveryTime = new int[nVertices];
        finishTime = new int[nVertices];
    }

    for(int i=0; i<nVertices; i++){     //initialize DFS variables
        color[i] = WHITE;
        parent[i] = -1;
        discoveryTime[i] = INFINITY;
        finishTime[i] = INFINITY;

    }
    time = 0;

    for(int i=0 ; i < nVertices; i++){
        if(color[i] == WHITE){
            dfsVisit(i);
        }
    }

    printf("\n*****DFS OUTPUT*****\n");
    printf("        Parents     Discovery Time  Finish Time\n");
    for(int i=0; i<nVertices; i++){
    printf("%d :     %d             %d              %d\n", i, parent[i], discoveryTime[i], finishTime[i]);
    }


}

void Graph::dfsVisit(int u){
    time++;
    discoveryTime[u] = time;
    color[u] = GREY;

    int v;
    int len = adjList[u].getLength();
    for(int i=0; i<len; i++){
        v = adjList[u].getItem(i);
        if(color[v]==WHITE){
            parent[v] = u;
            dfsVisit(v);
        }

    }

    time++;
    finishTime[u] = time;
    color[u] = BLACK;

}

int Graph::getDist(int u, int v){       ///opt 7
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || v<0 || u>=nVertices || v>=nVertices){
        return NULL_VALUE;
    }

    bfs(u);
    return dist[v] ;

}

void Graph::printGraph(){       ///opt 9
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

bool Graph::isConnected(){      ///opt 10
    bfs(0);
    for(int i=0; i<nVertices; i++){
        if(color[i]==WHITE)
            return false;
    }
    return true;
}

bool Graph::isTree(){       ///opt 11
    int source = 0;
    if(color==0){
        color = new int[nVertices];
        parent = new int[nVertices];
    }
    if(dist == 0){
        dist = new int[nVertices];
    }

    for(int i=0; i<nVertices; i++){     //initialize BFS variables
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;

    color[source] = GREY;
    dist[source] = 0 ;
    q.enqueue(source) ;

    int u, v, len;
    while( !q.empty() ){
        //complete this part
        u = q.dequeue();
        len = adjList[u].getLength();
        for(int i=0; i<len; i++){
            v = adjList[u].getItem(i);
            if(v!=parent[u] && color[v]!=WHITE)
                return false;

            else if(color[v] == WHITE){
                color[v] = GREY;
                dist[v] = dist[u]+1;
                //printf("Distance of %d = %d\n", v, dist[v]);
                parent[v] = u;
                q.enqueue(v);
            }
        }
        color[u]= BLACK;
    }

    for(int i=0; i<nVertices; i++){
        if(color[i]==WHITE)
            return false;
    }
    return true;


}

void Graph::isConnTree(){
    int source = 0;
    bool isC= true, isT=true;
    if(color==0){
        color = new int[nVertices];
        parent = new int[nVertices];
    }
    if(dist == 0){
        dist = new int[nVertices];
    }

    for(int i=0; i<nVertices; i++){     //initialize BFS variables
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;

    color[source] = GREY;
    dist[source] = 0 ;
    q.enqueue(source) ;

    int u, v, len;
    while( !q.empty() ){
        //complete this part
        u = q.dequeue();
        len = adjList[u].getLength();
        for(int i=0; i<len; i++){
            v = adjList[u].getItem(i);
            if(v!=parent[u] && color[v]!=WHITE)
                isT =  false;

            else if(color[v] == WHITE){
                color[v] = GREY;
                dist[v] = dist[u]+1;
                //printf("Distance of %d = %d\n", v, dist[v]);
                parent[v] = u;
                q.enqueue(v);
            }
        }
        color[u]= BLACK;
    }

    for(int i=0; i<nVertices; i++){
        if(color[i]==WHITE)
            isT = isC = false;
    }

    if(isC)
        printf("Connected, ");
    else
        printf("Not Connected, ");
    if(isT)
        printf("Tree\n");
    else
        printf("Not Tree\n");


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

//**********************Graph class ends here******************************

//******main function to test your code*************************
int main(void)
{
    printf("Enter number of vertices\n");
    printf("1. Add Edge.     2.Remove Edge.          3.Is Edge\n");
    printf("4.Get Degree.    5.Has Common Adjacent.  6.BFS.\n");
    printf("7.Get Distance.  8.DFS.                  9.Print Graph\n");
    printf("10.Is Connected. 11.Is Tree.             12.Connected and Tree Check\n");
    printf("13.Exit\n");

    FILE *fp;
    fp= fopen("input2.txt", "r");
    if(fp==NULL){
            printf("ERROR OPENING FILE\n");
        exit(0);
    }

    int n;
    Graph g;
    fscanf(fp, "%d", &n);
    g.setnVertices(n);

    while(1)
    {
        int ch;
        fscanf(fp, "%d",&ch);
        if(ch==1){
            int u, v;
            fscanf(fp, "%d%d", &u, &v);
            g.addEdge(u, v);

            //g.printGraph();

        }
        else if(ch==2){
            int u, v;
            fscanf(fp, "%d%d", &u, &v);
            g.removeEdge(u, v);

            //g.printGraph();

        }
        else if(ch==3){
            int u, v;
            fscanf(fp, "%d%d", &u, &v);
            bool flag= g.isEdge(u, v);
            printf("Edge between %d & %d : ", u, v);
            if(flag)    printf("True\n");
            else        printf("False\n");

        }
        else if(ch==4){
            int u;
            fscanf(fp, "%d", &u);
            int deg= g.getDegree(u);
            if(deg==NULL_VALUE)     printf("Invalid Vertex\n");
            else    printf("Degree of %d = %d\n", u, deg);
        }
        else if(ch==5){
            int u, v;
            fscanf(fp, "%d%d", &u, &v);
            bool flag= g.hasCommonAdjacent(u, v);
            printf("Common Adjacent Vertex between %d & %d : ", u, v);
            if(flag)    printf("True\n");
            else        printf("False\n");
        }
        else if(ch==6){
            int u;
            fscanf(fp, "%d", &u);
            printf("Running BFS from %d", u);
            g.bfs(u);

        }
        else if(ch==7){
            int u, v;
            fscanf(fp, "%d%d", &u, &v);
            int distance = g.getDist(u,v);

            if(distance==NULL_VALUE){
                printf("Invalid Input...\n");
                continue;
            }

            printf("Distances from %d to %d = %d\n" , u, v, distance);

        }
        else if(ch==8){
            g.dfs();
        }
        else if(ch==9){
            g.printGraph();
        }
        else if(ch==10){
            if(g.isConnected())
                printf("Connected Graph\n");
            else
                printf("Not Connected Graph\n");
        }

        else if(ch==11){
            if(g.isTree())
                printf("It's a Tree\n");
            else
                printf("It's not a Tree\n");
        }

        else if(ch==12){
            g.isConnTree();
        }

        else if(ch==13){
            break;
        }
        else{
            printf("Invalid Selection...\n");
        }

        //g.printGraph();
        printf("\n");

    }

}


