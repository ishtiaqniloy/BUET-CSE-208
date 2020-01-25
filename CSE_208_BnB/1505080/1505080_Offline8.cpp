#include <cstdio>
#include <cstring>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <cmath>

#define MAXSIZE 200
#define NULL_VALUE 999999

using namespace std;

class SetCover{
    class Node{
    public:
        int n;
        int remaining;
        int setsTaken;
        int bound;

        Node *left;
        Node *right;
        Node *parent;

        bool *covered;

        int level;

        Node(int num, int rem, int sets, int b, Node *l, Node* r, Node *p, bool *cv, int lv){
            n = num;
            remaining = rem;
            setsTaken = sets;
            bound = b;

            left = l;
            right = r;
            parent = p;

            covered = new bool[n+5];

            level = lv;

            if(cv!=NULL){
                for(int i=0; i<n+5; i++){
                    covered[i] = cv[i];
                }
            }
            else{
                for(int i=0; i<n+5; i++){
                    covered[i] = false;
                }
            }


        }

    };

    class Qcomparison{
        bool reverse;
    public:
        Qcomparison(const bool& minQ=true){     ///true if minPriorityQueue
            reverse=minQ;
        }
        bool operator() (const Node* lhs, const Node*rhs) const{
            if (reverse) return (lhs->bound>rhs->bound);
            else return (lhs->bound<rhs->bound);
        }
    };

    int n, m;
    vector <int> *arr;

    int calculateBound(Node *node){
        int maxi = 1;
        for(int i=node->level; i<m; i++){
            if(maxi<arr[i].size()){
                maxi = arr[i].size();
            }
        }

        int bound = node->setsTaken + ceil(1.0*node->remaining / maxi );

        return bound;


    }

    void printSets(Node *node){
        if(node==NULL || node->level==0){
            return;
        }
        printSets(node->parent);

        if(node->parent!=NULL && node == node->parent->right){
            int level = node->level;
            printf("Set %d: ", level);

            for(int i=0; i<arr[level-1].size(); i++){
                printf("%d ", arr[level-1].at(i));
            }
            printf("\n");
        }

        return;

    }

public:

    SetCover(){
        FILE *fp;
        fp= fopen("input.txt", "r");
        if(fp==NULL){
            printf("ERROR OPENING FILE\n");
            return ;
        }

        fscanf(fp, "%d %d", &n, &m);

        arr = new vector<int>[m];
//        for (int i = 0; i < m; ++i) {
//            arr[i].reserve(n);
//        }

        char *str = new char[MAXSIZE];
        fgets(str, MAXSIZE, fp);

        for(int i=0; i<m; i++){
            fgets(str, MAXSIZE, fp);
            int num;
            char s[10];
            while (sscanf(str, "%d", &num)!=EOF){
                //printf("read %d\n", num);
                if(num>n){
                    printf("Invalid Data");
                    exit(0);
                }
                arr[i].push_back(num);
                itoa(num, s, 10);
                str+= strlen(s)+1;
            }


        }

    }

    int minCover(){
        Node *root = new Node(n, n, 0, 0, NULL, NULL, NULL, NULL, 0);

        priority_queue <Node*, vector <Node*>, Qcomparison > queue;
        queue.push(root);

        while (!queue.empty()){
            Node *temp = queue.top();
            queue.pop();

            if(temp==NULL){
                break;
            }

            //printf("Found node : level = %d, bound = %d, remaining=%d, setsTaken=%d\n", temp->level, temp->bound, temp->remaining, temp->setsTaken);

            if(temp->remaining==0){
                printf("Following are the sets taken in cover...\n");
                printSets(temp);
                return temp->setsTaken;
            }
            else if(temp->level == m){
                continue;
            }

            Node *leftNode = new  Node(n, temp->remaining, temp->setsTaken, temp->bound, NULL, NULL, temp, temp->covered, temp->level+1);
            Node *rightNode = new  Node(n, temp->remaining, temp->setsTaken+1, temp->bound, NULL, NULL, temp, temp->covered, temp->level+1);

            int level = rightNode->level;
            for(int i=0; i<arr[level-1].size(); i++){
                //printf("here %d %d\n", i, arr[level-1].size());
                if(!rightNode->covered[arr[level-1].at(i)] ){
                    rightNode->remaining--;
                    rightNode->covered[arr[level-1].at(i)] = true;
                }
                //printf("out of here\n");


            }

            int br = calculateBound(rightNode);
            rightNode->bound = br;

            br = calculateBound(leftNode);
            leftNode->bound = br;

            queue.push(leftNode);
            queue.push(rightNode);

            temp->left = leftNode;
            temp->right = rightNode;

        }

        return NULL_VALUE;


    }

};


int main() {
    //printf("Hello World\n");

    SetCover *setCover = new SetCover();

    int result = setCover->minCover();

    if(result == NULL_VALUE){
        printf("Cover not possible\n");
    }
    else{
        printf("Minimum number of sets in the set cover = %d\n", result);
    }


    return 0;
}




