#include<stdio.h>
#include<stdlib.h>
#include <fstream>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

#define MAX_HEAP_SIZE 100000
#define MAXREAL 999999.0

class HeapItem{
public:
	int data; //actual data that is stored
	float key; //key value of the data, heap is constructed based on key
};

//MinHeap class, minimum item stored at the root of heap tree
class MinHeap{
public:
	HeapItem * A; //stores heap items, e.g., nodes
	int heapLength;
	int * map;

	MinHeap(){ //constructor
		A = new HeapItem[MAX_HEAP_SIZE];
		map = new int[MAX_HEAP_SIZE];
		/*for(int i=0; i<MAX_HEAP_SIZE; i++){
            map[i] = 0;     ///sometimes some values are not automatically set to 0, thus gives wrong output
		}*/
		heapLength=0;
	}

	~MinHeap(){ //destructor
		if(map) delete [] map;
		if(A) delete [] A;
		map = 0; //set to NULL after deletion
		A = 0; //set to NULL after deletion
	}

    //Fills the heap with an array of integers
    //key values do not maintain heap property
    //May be used in some algorithms such as dijkstra's shortest path
	void initialize(int v[], int n){
		heapLength = n;
		for(int i=0; i<n; i++){ //nodes are stored from index 1 instead of 0 in the heap
			A[i+1].data = v[i];
			A[i+1].key = MAXREAL;
			map[v[i]] = i+1; //map tracks which vertex is stored at which heap node
		}
	}

	//this function inserts a new (data,key) pair in the heap
    //call to buHeapify is required
    void insertItem(int data, float key){     ///opt 1
        if(data<0 || data>MAXREAL){
            printf("Invalid input data\n");
            return;
        }
        else if (map[data]!=0){
            printf("Item already at index %d. Recurrence of Data not Supported...\n" , map[data]);
            return;
        }

        if(heapLength==0){
            for(int i=0; i<MAX_HEAP_SIZE; i++){
                map[i] = 0;     ///sometimes some values are not initially automatically set to 0, thus gives wrong output
            }
        }

        heapLength++;
        A[heapLength].data = data;
        A[heapLength].key = key;

        map[data] = heapLength;
        buHeapify(heapLength);

    }

    //this function removes (and returns) the node which contains the minimum key value
	HeapItem removeMin(){           ///opt 2
        HeapItem temp;
        if(heapLength==0){
            printf("Empty Heap\n");
            temp.data = -1;
            temp.key = MAXREAL+1;
            return temp;
        }

        temp = A[1];
        A[1] = A[heapLength];
        heapLength--;
        map[A[1].data] = 1;
        heapify(1);
        map[temp.data] = 0;
        return temp;
	}

    //The function updates the key value of an existing data stored in the heap
	//Note that updates can result in an increase or decrease of key value
	//Call to heapify or buheapify is required
	void updateKey(int data, float key){    ///opt 3
		//Write your codes here
		int index = map[data];
		if(index==0){
            printf("Item Not Found\n");
            return;
		}
		float oldKey = A[index].key;
		A[index].key = key;

		if(key >  oldKey){
            heapify(index);
		}
		else if(key < oldKey){
            buHeapify(index);
		}
	}

    //This function returns the key value of a data stored in heap
	float getKey(int data){
		int i = map[data];
		if( i == 0){
            printf("Invalid data\n");
            return MAXREAL+1;
		}
		return A[i].key;
	}

	bool exist(int data){
        int index = map[data];
		if(index==0){
            return false;
		}
		return true;
	}

    //This function heapifies the heap
    //When a key value of ith node is increased (because of update), then calling this function will restore heap property
	void heapify(int i){
		int l,r,smallest;
		while(1)
		{
			l=2*i;      //left child index
			r=2*i+1;    //right child index
			smallest=i;
			if(l>heapLength && r>heapLength)
				break; //nothing to do, we are at bottom
			else if(r>heapLength)
				smallest = l;
			else if(l>heapLength)
				smallest = r;
			else if( A[l].key < A[r].key )
				smallest = l;
			else
				smallest = r;

			if(A[i].key <= A[smallest].key)
				break;	//we are done heapifying
            else{
                //swap nodes with smallest child, adjust map array accordingly
				HeapItem t;
				t=A[i];
				A[i]=A[smallest];
				map[A[i].data]=i;
				A[smallest]=t;
				map[A[smallest].data]=smallest;
				i=smallest;
			}
		}
	}

    //This function heapifies the heap form bottom to up
    //When a key value of ith node is decreased (because of update), then calling this function will restore heap property
    //In addition, when a new item is inserted at the end of the heap, then calling this function restores heap property
	void buHeapify(int i){
        int par;
        while(i!=1){
            par = i/2;
            if( A[par].key > A[i].key){
                HeapItem temp = A[par];
                A[par] = A [i];
                A[i] = temp;
                map[A[par].data] = par;
                map[A[i].data] = i;
                i = par;
            }
            else{
                break;
            }
        }
	}

    void printHeap(){
        printf("Heap length: %d\n", heapLength);
        for(int i=1;i<=heapLength;i++)
        {
            printf("(%d,%.2f) ", A[i].data, A[i].key);
        }
        printf("\n");
    }

	bool Empty(){
		if(heapLength==0)return true;
		else return false;
	}
};

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
    void primMST();

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
    if(u<0 || v<0 || u>=nVertices || v>=nVertices || isEdge(u,v) || u==v) {
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

void Graph::primMST(){
    MinHeap heap;

    int *arr = new int[nVertices];
    int *par = new int[nVertices];
    int totalWeight=0;

    for(int i=0; i<nVertices; i++){
        arr[i]=i;
        par[i] = -1;
    }
    heap.initialize(arr,nVertices);
    //heap.printHeap();

    heap.updateKey(0,0);
    //heap.printHeap();

    while(!heap.Empty()){
        HeapItem htm = heap.removeMin();
        //heap.printHeap();
        //printf("%d\n", htm.data);
        int u = htm.data;
        totalWeight+=htm.key;
        int len = adjList[u].getLength();
        for(int i=0; i<len; i++){
            int v = adjList[u].getItem(i).node;
            int w = adjList[u].getItem(i).weight;

            if(heap.exist(v) && w < heap.getKey(v)){
                par[v] = u;
                heap.updateKey(v,w);
                //heap.printHeap();
            }


        }
        //heap.printHeap();
    }

    for(int i=0; i<nVertices; i++){
        if(par[i]!=-1)
            printf("%d %d\n", i+1, par[i]+1);
    }
    printf("%d\n", totalWeight);


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
    Graph g;

    //printf("Enter number of vertices\n");
    fscanf(fp, "%d", &n);
    g.setnVertices(n);

    //printf("Enter number of edges\n");
    fscanf(fp, "%d", &m);

    int u,v,w;
    for(int i=0; i<m; i++){
        fscanf(fp, "%d %d %d", &u, &v, &w);
        g.addEdge(u-1,v-1,w);
    }

    g.printGraph();
    printf("\n\n****Running Prim's Algorithm to find Minimum Spanning Tree****\n\n");
    g.primMST();

    return 0;

}


