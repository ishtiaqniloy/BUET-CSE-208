///MaxFlow Online by 1505080
///bipartite matching

#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>

#define GraphMaxSize 150

#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

using namespace std;

class FlowNetwork{
    class Residual{
    public:
        vector <int> adjList[GraphMaxSize];
        int nVertices;
        int nEdges;
        int source;
        int sink;
        int totalFlow;
        int capacity[GraphMaxSize][GraphMaxSize];

        int color[GraphMaxSize];
        int parent[GraphMaxSize];
        int dist[GraphMaxSize];

        Residual(int n, int m, int s, int t){
            nVertices = n;
            nEdges = m;
            source = s;
            sink = t;
            for(int i=0; i<GraphMaxSize; i++){
                for(int j=0; j<GraphMaxSize; j++){
                    capacity[i][j]= 0;
                }
            }

        }

        void addEdge(int u, int v, int c){
            adjList[u].push_back(v);
            capacity[u][v] = c;
        }

        void bfs(){
            for(int i=1; i<=nVertices; i++){     //initialize BFS variables
                color[i] = WHITE ;
                parent[i] = -1 ;
                dist[i] = INFINITY ;
            }
            queue <int> q;

            color[source] = GREY;
            dist[source] = 0 ;
            q.push(source) ;

            int u, v, len;
            while( !q.empty() ){
                u = q.front();
                q.pop();
                len = adjList[u].size();
                for(int i=0; i<len; i++){
                    v = adjList[u].at(i);
                    if(capacity[u][v]<=0){
                        continue;
                    }
                    else if(v==sink){
                        color[v] = GREY;
                        dist[v] = dist[u]+1;
                        parent[v] = u;
                        return;
                    }
                    else if(color[v] == WHITE){
                        color[v] = GREY;
                        dist[v] = dist[u]+1;
                        parent[v] = u;
                        q.push(v);
                    }
                }
                color[u]= BLACK;
            }

            /*printf("*****BFS OUTPUT*****\n");
            printf("        Parents     Distance\n");
            for(int i=1; i<=nVertices; i++){
            printf("%d :      %d            %d\n", i, parent[i], dist[i]);
            }*/

        }

        void printResidualNetwork(){
            printf("Number of Vertices = %d\nNumber of Edges = %d\nSource = %d, Sink = %d\n", nVertices, nEdges, source, sink);
            for(int i=1; i<=nVertices; i++){
                int len = adjList[i].size();
                printf("%d: ", i);
                for(int j = 0; j < len; j++){
                    int v = adjList[i].at(j);
                    printf("(%d , %d) ", v, capacity[i][v]);
                }
                printf("\n");
            }
        }

    };

    vector <int> adjList[GraphMaxSize];
    int nVertices;
    int nEdges;
    int source;
    int sink;
    int currentFlow;
    bool isEdge[GraphMaxSize][GraphMaxSize];
    int capacity[GraphMaxSize][GraphMaxSize];
    int flow[GraphMaxSize][GraphMaxSize];

public:
    FlowNetwork(int n, int m, int s, int t){
        nVertices = n;
        nEdges = m;
        source = s;
        sink = t;
        currentFlow = 0;

        for(int i=0; i<GraphMaxSize; i++){
            for(int j=0; j<GraphMaxSize; j++){
                isEdge[i][j] = false;
                capacity[i][j]= 0;
                flow[i][j] = 0;
            }
        }

    }

    void addEdge(int u, int v, int c, int f=0){
        if(isEdge[u][v])
            return;

        isEdge[u][v] = true;
        adjList[u].push_back(v);
        capacity[u][v] = c;
        flow[u][v] = f;
    }

    void printFlowNetwork(){
        printf("Number of Vertices = %d\nNumber of Edges = %d\nSource = %d, Sink = %d, Current Flow = %d\n", nVertices, nEdges, source, sink, currentFlow);
        for(int i=1; i<=nVertices; i++){
            int len = adjList[i].size();
            printf("%d: ", i);
            for(int j = 0; j < len; j++){
                int v = adjList[i].at(j);
                printf("(%d , %d/%d) ",  v, flow[i][v], capacity[i][v]);
            }
            printf("\n");
        }
    }



    int maxFlow(){
        currentFlow = 0;
        Residual temp(nVertices, nEdges, source, sink);

        for(int i=1; i<=nVertices; i++){
            int len = adjList[i].size();
            for(int j = 0; j < len; j++){
                int v = adjList[i].at(j);
                temp.addEdge(i, v, capacity[i][v]);
                if(!isEdge[v][i])
                    temp.addEdge(v, i, 0);
            }
        }
        ///temp.printResidualNetwork();

        temp.bfs();
        int minCap, tempNode, par;

        while(temp.dist[sink]!=INFINITY){
            minCap = INFINITY;
            tempNode = sink;
            par = temp.parent[tempNode];
            while(par!=-1){     ///finding how much flow can be added this iteration
                if(minCap > temp.capacity[par][tempNode]){
                    minCap = temp.capacity[par][tempNode];
                }
                tempNode = par;
                par = temp.parent[tempNode];
            }
            currentFlow+=minCap;

            tempNode = sink;
            par = temp.parent[tempNode];
            while(par!=-1){
                if(isEdge[par][tempNode] && flow[par][tempNode]+minCap <= capacity[par][tempNode])
                    flow[par][tempNode]+=minCap;
                else
                    flow[tempNode][par]-=minCap;

                temp.capacity[par][tempNode]-=minCap;
                temp.capacity[tempNode][par]+=minCap;

                tempNode = par;
                par = temp.parent[tempNode];

            }

            temp.bfs();

            //printFlowNetwork();
            //temp.printResidualNetwork();

        }

        printFlowNetwork();

        printf("\nMaximum Bipartite Matching Number of Edges = %d\n", currentFlow);

        printf("Edges: ");
        for(int i=1; i<=nVertices-2; i++){
            int len = adjList[i].size();
            for(int j=0; j<len; j++){
                int v = adjList[i].at(j);
                if(v!=sink && flow[i][v]>0)
                    printf("(%d,%d) ", i, v);
            }

        }

        printf("\n");


    }


};

int main(){
FILE *fp;
    fp= fopen("input_online3.txt", "r");
    if(fp==NULL){
            printf("ERROR OPENING FILE\n");
        exit(0);
    }

    int n, m, s, t;
    fscanf(fp, "%d", &n);
    fscanf(fp, "%d", &m);
    //fscanf(fp, "%d", &s);
    //fscanf(fp, "%d", &t);
    s = n+1;
    t = n+2;
    FlowNetwork g(n+2, n+m, s, t);
    int u,v,c=1;
    for(int i=0; i<m; i++){
        fscanf(fp, "%d %d", &u, &v, &c);
        g.addEdge(u,v,c);
        g.addEdge(s,u,c);
        g.addEdge(v,t,c);
    }

    //g.printFlowNetwork();
    cout<<endl;
    g.maxFlow();


    return 0;
}
