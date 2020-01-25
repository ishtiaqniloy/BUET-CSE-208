#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <vector>

#define GraphMaxSize 25
#define INFINITY 999
#define NULL_VALUE -999

using namespace std;

class Graph{
    class Edge{
        public:
        int node;
        int weight;
    };
    vector <Edge> adjList[GraphMaxSize];
    int nVertices;
    int nEdges;
    bool isDir;
public:
    Graph(int n, int m, bool dir){
        nVertices = n;
        nEdges = m;
        isDir = dir;
    }

    void addEdge(int u, int v, int w){
        Edge e;
        e.node = v;
        e.weight = w;
        adjList[u].push_back(e);
        if(!isDir){
            Edge f;
            f.node = u;
            f.weight = w;
            adjList[v].push_back(f);
        }

    }

    void printGraph(){
        printf("Number of Vertices = %d\nNumber of Edges = %d\n", nVertices, nEdges);
        for(int i=1; i<=nVertices; i++){
            int len = adjList[i].size();
            printf("%d: ", i);
            for(int j = 0; j < len; j++){
                Edge e = adjList[i].at(j);
                printf("(%d,%d) ",  e.node, e.weight);
            }
            printf("\n");


        }
    }

    void Floyd_Warshall(){

        int weightMatrix[nVertices+1][nVertices+1];
        int parentMatrix[nVertices+1][nVertices+1];

        for(int i=1; i<=nVertices; i++){    ///O(n^2)
            for(int j=1; j<=nVertices; j++){
                weightMatrix[i][j] = INFINITY;
                parentMatrix[i][j] = NULL_VALUE;
            }
            weightMatrix[i][i] = 0;
        }

        for(int i=1; i<=nVertices; i++){        ///O(n^2)
            int len = adjList[i].size();
            for(int j = 0; j < len; j++){
                Edge e = adjList[i].at(j);
                if(weightMatrix[i][e.node] > e.weight){
                    weightMatrix[i][e.node] = e.weight;
                    parentMatrix[i][e.node] = i;
                }

            }
        }

        printf("\n***Floyd-Warshall Algorithm Output***\n\n");

        printf("Initial Graph:\n");
        for(int i=1; i<=nVertices; i++){
            for(int j=1; j<=nVertices; j++){
                if(weightMatrix[i][j]==INFINITY)    printf("INF\t");
                else printf("%d\t", weightMatrix[i][j]);
            }
            printf("\n");

        }

        for(int k = 1; k<=nVertices; k++){      ///O(n^3)
            for(int i = 1; i<=nVertices; i++){
                for(int j = 1; j<=nVertices; j++){
                    if(weightMatrix[i][j] > weightMatrix[i][k]+weightMatrix[k][j]){
                        weightMatrix[i][j] = weightMatrix[i][k]+weightMatrix[k][j];
                        parentMatrix[i][j] = parentMatrix[k][j] ;
                    }
                }
            }

            /*printf("\nAfter %dth iteration:\n", k);
            for(int i=1; i<=nVertices; i++){
                for(int j=1; j<=nVertices; j++){
                    printf("%d\t", weightMatrix[i][j]);
                }
                printf("\n");

            }*/

        }

        /*for(int i = 1; i<=nVertices; i++){
            if(weightMatrix[i][i] <0 ){
                printf("Negative Cycle Present\n");
                return;
            }
        }*/



        printf("\nAll pair shortest paths:\n");
        for(int i=1; i<=nVertices; i++){
            for(int j=1; j<=nVertices; j++){
                if(weightMatrix[i][j]==INFINITY)    printf("INF\t");
                else printf("%d\t", weightMatrix[i][j]);
            }
            printf("\n");

        }

        printf("\nPredecessor Matrix:\n");
        for(int i=1; i<=nVertices; i++){
            for(int j=1; j<=nVertices; j++){
                if(parentMatrix[i][j]==NULL_VALUE)    printf("INF\t");
                else printf("%d\t", parentMatrix[i][j]);
            }
            printf("\n");

        }


    }


};

int main(){

FILE *fp;
    fp= fopen("input.txt", "r");
    if(fp==NULL){
            printf("ERROR OPENING FILE\n");
        exit(0);
    }

    int n,m;
    fscanf(fp, "%d %d", &n, &m);
    Graph g(n, m, true);

    int u,v,w;
    for(int i=0; i<m; i++){
        fscanf(fp, "%d %d %d", &u, &v, &w);
        g.addEdge(u,v,w);
    }


    g.printGraph();

    g.Floyd_Warshall();



    return 0;
}





