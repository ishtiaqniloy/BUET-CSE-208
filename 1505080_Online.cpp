///1505080 Offline 7 Red Black Tree

#include <cstdio>

#define RED 0
#define BLACK 1
#define NULL_VALUE -9999999

using namespace std;


/*
int getSize(struct treeNode * node){        ///opt 7
    if (node == 0){
        return 0;
    }

    return getSize(node->left) + getSize(node->right) + 1;


}

int calcNodeDepth(struct treeNode * node){      ///opt 8
                                                //return depth of a node
    int c = 0, item;
    if(node == 0){
        return -1;
    }
    item = node->item;

    struct treeNode * temp;
    temp = root;

    while(true){

        if(temp == 0){
            return -1;
        }

        else if(item == temp->item){
            return c;
        }

        else if(item<temp->item){
            temp = temp->left;
        }

        else if(item>temp->item){
            temp = temp->right;
        }

        c++;

    }

 }


int calcDepth(int item){    ///opt 9
                            //return depth of an item in the tree
    int c = 0;

    struct treeNode * temp;
    temp = root;

    while(true){

        if(temp == 0){
            return -1;
        }

        else if(item == temp->item){
            return c;
        }

        else if(item<temp->item){
            temp = temp->left;
        }

        else if(item>temp->item){
            temp = temp->right;
        }

        c++;

    }

}

int rangeSearch(struct treeNode * node, int leftBound, int rightBound){     ///opt 12
                                                                            //returns number of items in the
    if(node == 0){
        return 0;
    }

    else if(node->item<leftBound){
        return rangeSearch(node->right, leftBound, rightBound);
    }


    else if(node->item>rightBound){
        return rangeSearch(node->left, leftBound, rightBound);
    }

    else{

        return 1 + rangeSearch(node->left, leftBound, rightBound) + rangeSearch(node->right, leftBound, rightBound);

    }


}

*/


class RedBlackTree{

    class RBTNode{
    public:
        int key;
        int color;
        RBTNode *parent;
        RBTNode *left;
        RBTNode *right;

        RBTNode(int k = NULL_VALUE, int c = BLACK, RBTNode *p = NULL, RBTNode *l = NULL, RBTNode *r = NULL){
            key = k;
            color = c;
            parent = p;
            left = l;
            right = r;
        }

        ~RBTNode(){
            parent = NULL;
            left = NULL;
            right = NULL;
        }

    };

    RBTNode *root;
    RBTNode *nil;

    /*
    bool leftRotate(RBTNode *x) {
        printf("leftRotate Called\n");
        if (x == NULL ||  x->right == NULL) {
            return false;
        }

        RBTNode *y = x->right;
        x->right =  y->left;

        if(y->left!=nil){
            y->left->parent = x;
        }

        y->parent = x->parent;
        if(x->parent==nil){     ///x was root
            root == y;
        }
        else if(x->parent->left==x){
            x->parent->left = y;
        }
        else{
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;

        return true;

    }

    bool rightRotate(RBTNode *x){
        printf("rightRotate Called\n");
        if (x == NULL ||  x->left == NULL) {
            return false;
        }

        RBTNode *y = x->left;
        x->left =  y->right;

        if(y->right!=nil){
            y->right->parent = x;
        }

        y->parent = x->parent;
        if(x->parent==nil){     ///x was root
            root == y;
        }
        else if(x->parent->right==x){
            x->parent->right = y;
        }
        else{
            x->parent->left = y;
        }

        y->right = x;
        x->parent = y;

        return true;

    }
*/

    bool leftRotate2(RBTNode *x) {
        //printf("leftRotate2 Called\n");
        if (x == NULL ||  x->right == NULL) {
            return false;
        }

        RBTNode *y = x->right;
        x->right =  y->left;

        if(y->left!=NULL) y->left->parent = x;
        y->parent = x->parent;
        if(x->parent==nil){
            root = y;
        }
        else if(x == x->parent->left){
            x->parent->left = y;
        }
        else{
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;

        //printf("leftRotate2 completed\n");

        return true;

    }

    bool rightRotate2(RBTNode *x){
        //printf("rightRotate2 Called\n");
        if (x == NULL ||  x->left == NULL) {
            return false;
        }

        RBTNode *y = x->left;
        x->left =  y->right;

        if(y->right!=NULL) y->right->parent = x;
        y->parent = x->parent;
        if(x->parent==nil){
            root = y;
        }
        else if(x == x->parent->right){
            x->parent->right = y;
        }
        else{
            x->parent->left = y;
        }

        y->right = x;
        x->parent = y;

        //printf("rightRotate2 completed\n");

        return true;

    }

    bool insertFixUp(RBTNode *z){
        if(z==NULL)
            return false;

        while(z->parent!=NULL && z->parent->color == RED){
            if(z->parent->parent !=NULL && z->parent == z->parent->parent->left){
                RBTNode *y = z->parent->parent->right;
                if(y->color==RED){
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else{
                    if(z==z->parent->right){
                        z = z->parent;
                        leftRotate2(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    rightRotate2(z->parent->parent);

                }

            }
            else if(z->parent->parent !=NULL ){
                RBTNode *y = z->parent->parent->left;
                if(y->color==RED){
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                }
                else{
                    if(z==z->parent->left){
                        z = z->parent;
                        rightRotate2(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    leftRotate2(z->parent->parent);

                }
            }

        }

        root->color = BLACK;

        return true;


    }

    void printInOrder(RBTNode* node, int height){

        if(node==nil || node==NULL) return ;

        //print left sub-tree
        printInOrder(node->left, height-1);

        //print key
        for(int i=0;i<height;i++)printf("       ");

        char ch = 0;
        if(node->color==RED)    ch = 'R';
        else    ch = 'B';

        printf("(%03d,%c)\n",node->key, ch);


        //print right sub-tree
        printInOrder(node->right, height-1);
    }

    void printInOrderSorted(RBTNode* node){

        if(node==nil || node==NULL) return ;

        //print left sub-tree
        printInOrderSorted(node->left);

        //print key
        printf("%d ",node->key);

        //print right sub-tree
        printInOrderSorted(node->right);
    }

    int calcNodeHeight(RBTNode * node){
        //return height of a node
        if(node==NULL) return -1;
        else if(node==nil) return 0;

        int l, r;
        l = calcNodeHeight(node->left);
        r = calcNodeHeight(node->right);

        if(l>r) return l+1;
        else return r+1;

    }

    RBTNode * searchNode(RBTNode *node , int key){
        if(node==nil || node==NULL)
            return nil;

        else if(node->key==key)
            return node; //found, return node

        else if(key < node->key)
            return searchNode(node->left, key); //search in the left sub-tree

        else
            return searchNode(node->right, key); //search in the right sub-tree

    }

    bool rbTransplant(RBTNode *u, RBTNode *v){
        if(u==NULL)
            return false;
        else if(u->parent==nil){
            root = v;
        }
        else if(u == u->parent->left){
            u->parent->left = v;
        }
        else{
            u->parent->right = v;
        }

        if(v!=NULL ){
            v->parent = u->parent;
        }

        return true;
    }

    RBTNode * getMinNode(RBTNode *node){
        if(node==nil || node==NULL){
            return nil;
        }

        while(node->left!=nil){
            node = node->left;
        }

        return node;

    }

    RBTNode * RBTSuccessor(RBTNode *x){
        if(x->right!=nil){
            return getMinNode(x->right);
        }

        RBTNode *y = x->parent;
        while (y!=nil && x == y->right){
            x = y;
            y = y->parent;
        }

        return y;

    }

    bool deleteFixUp(RBTNode *x){
        if(x==NULL){
            return false;
        }

        while (root!=x && x!=NULL && x->color==BLACK){
            if(x->parent!=NULL && x==x->parent->left){
                RBTNode *w = x->parent->right;
                if(w!=NULL && w->color==RED){
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate2(x->parent);
                    w = x->parent->right;
                }

                if(w!=NULL && w->left!=NULL && w->left->color==BLACK && w->right!=NULL && w->right->color==BLACK){
                    w->color = RED;
                    x = x->parent;
                }
                else if(w!=NULL){
                    if(w->right!=NULL && w->right->color==BLACK){
                        if(w->left!=NULL)   w->left->color = BLACK;
                        w->color = RED;
                        rightRotate2(w);
                        w = x->parent->right;
                    }
                    if(w!=NULL) w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if(w->right!=NULL)w->right->color = BLACK;
                    leftRotate2(x->parent);
                    x = root;
                }
            }
            else if(x->parent!=NULL){
                RBTNode *w = x->parent->left;
                if(w!=NULL && w->color==RED){
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate2(x->parent);
                    w = x->parent->left;
                }

                if(w!=NULL && w->right!=NULL && w->right->color==BLACK && w->left!=NULL && w->left->color==BLACK){
                    w->color = RED;
                    x = x->parent;
                }
                else if(w!=NULL){
                    if(w->left!=NULL && w->left->color==BLACK){
                        if(w->right!=NULL) w->right->color = BLACK;
                        w->color = RED;
                        leftRotate2(w);
                        w = x->parent->left;
                    }
                    if(w!=NULL) w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if(w->left!=NULL)   w->left->color = BLACK;
                    rightRotate2(x->parent);
                    x = root;
                }
            }

        }
        x->color = BLACK;

        return true;
    }

    int rangeSumRecursion(RBTNode *node, int leftBound, int rightBound){
        if(node == nil){
            return 0;
        }
        else if(node->key<=leftBound){
            return rangeSumRecursion(node->right, leftBound, rightBound);
        }
        else if(node->key>=rightBound){
            return rangeSumRecursion(node->left, leftBound, rightBound);
        }
        else{
            return node->key + rangeSumRecursion(node->left, leftBound, rightBound) + rangeSumRecursion(node->right, leftBound, rightBound);
        }


    }

    int redSum(RBTNode *node, int level){
        if(level==0 || node == nil){
            return 0;
        }
        if(level==1 && node->color==RED){
            return node->key;
        }

        else if(level>1){
            return redSum(node->left, level-1)+redSum(node->right, level-1);
        }
        else{
            return 0;
        }


    }

    int blackSum(RBTNode *node, int level){
        if(level==0 || node == nil){
            return 0;
        }
        if(level==1 && node->color==BLACK){
            return node->key;
        }

        else if(level>1){
            return blackSum(node->left, level-1)+blackSum(node->right, level-1);
        }
        else{
            return 0;
        }


    }



public:
    RedBlackTree(){
        nil = new RBTNode(NULL_VALUE, BLACK, NULL, NULL, NULL);
        root = nil;


    }

    bool insertKey(int key){
        RBTNode *z = new RBTNode(key, RED, nil, nil, nil);
        RBTNode *y = nil;
        RBTNode *x = root;

        while (x!=nil){
            y = x;
            if(z->key < x->key){
                x = x->left;
            }
            else{
                x = x->right;
            }
        }

        z->parent = y;
        if(y==nil){
            root = z;
        }
        else if(z->key < y->key){
            y->left = z;
        }
        else{
            y->right = z;
        }

        return insertFixUp(z);
    }

/*
    bool deleteKey(int key){
        RBTNode *z = searchNode(root, key);
        if(z==nil || z==NULL){
            printf("Key not present.\n");
            return false;
        }

        //printf("Found node with key = %d\n", z->key);

        RBTNode *y = z;
        RBTNode *x = NULL;

        int yOriginalColor = y->color;

        if(z->left==nil){
            x = z->right;
            rbTransplant(z,z->right);
        }
        else if(z->right==nil){
            x = z->left;
            rbTransplant(z, z->left);
        }
        else{
            y = getMinNode(z->right);
            yOriginalColor = y->color;
            x = y->right;
            if(y->parent==z){
                x->parent == y;
            }
            else{
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            rbTransplant(z,y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;

        }

        if(yOriginalColor==BLACK){
            printf("Calling deleteFixUp from 1\n");
            deleteFixUp(x);
        }

        return true;
    }
*/

    bool deleteKey2(int key){
        RBTNode *z = searchNode(root, key);
        if(z==nil || z==NULL){
            printf("Key not present.\n");
            return false;
        }

        //printf("Found node with key = %d\n", z->key);

        RBTNode *y = NULL;
        RBTNode *x = NULL;

        if(z->left==nil || z->right==nil){
            y = z;
        }
        else{
            y = RBTSuccessor(z);
        }

        if(y->left!=nil){
             x = y->left;
        }
        else{
            x = y->right;
        }

        x->parent = y->parent;

        if(y->parent==nil || y->parent==NULL) {
            root = x;
        }
        else if(y->parent!=NULL && y == y->parent->left){
            y->parent->left = x;
        }
        else if(y->parent!=NULL){
            y->parent->right = x;
        }


        if(y!=z){
            z->key = y->key;
            ///copy  other data
        }

        if(y->color==BLACK){
            deleteFixUp(x);
        }

        return true;

    }

    bool lookUp(int key){
        RBTNode *node = searchNode(root, key);

        if(node!=nil) {
            return true;
        }
        else{
            return false;
        }

    }

    void printRBT(){
        printInOrder(root, calcNodeHeight(root));
    }

    void printSorted(){
        printInOrderSorted(root);
        printf("\n");
    }

    int rangeSum(int a, int b){
        return rangeSumRecursion(root, a, b);
    }

    int commonAncestor(int key1, int key2){
        RBTNode *x = searchNode(root, key1);
        RBTNode *y = searchNode(root, key2);

        if(x==nil || y==nil){
            return NULL_VALUE;
        }
        else if(searchNode(x, key2)!=nil){
            return key1;
        }
        else if(searchNode(y, key1)!=nil){
            return key2;
        }

        RBTNode *temp = root;

        while(temp!=nil){
            if(temp->key==key1 || temp->key == key2){
                return NULL_VALUE;
            }
            else if(temp->key > key1 && temp->key > key2){
                temp= temp->left;
            }
            else if(temp->key < key1 && temp->key < key2){
                temp= temp->right;
            }
            else{
                return temp->key;
            }

        }

        return NULL_VALUE;

    }

    void redBlackSum(int level){
        int rs = redSum(root, level);
        int bs = blackSum(root, level);

        printf("Level = %d, Red Sum = %d, Black Sum = %d\n", level, rs, bs);

    }


};



int main(){
    //printf("Hello World\n");

    RedBlackTree redBlackTree;

    printf("1. Insert Key.      2. Delete Key.          3. Look up Key. \n");
    printf("4. Print Tree.      5. Print Sorted.        6. Sum in Level.\n");
    printf("7. Common Ancestor. 8. Range Sum.           9. Exit.\n");

    while(true){
        int ch;
        scanf("%d",&ch);

        if(ch==1){      ///insert
            int key;
            scanf("%d", &key);
            redBlackTree.insertKey(key);
        }
        else if(ch==2){     ///delete
            int key;
            scanf("%d", &key);
            redBlackTree.deleteKey2(key);
        }
        else if(ch==3){     ///look up
            int key;
            scanf("%d", &key);

            bool found = redBlackTree.lookUp(key);
            if(found)
                printf("%d is found in the RBT.\n", key);
            else
                printf("%d is not found in the RBT.\n", key);
        }
        else if(ch==4){     ///print Tree
            printf("Printing Tree...\n");
            redBlackTree.printRBT();
        }
        else if(ch==5){     ///print in sorted order
            printf("Printing in sorted order: ");
            redBlackTree.printSorted();
        }
        else if(ch==6){     ///Sum in Level
            int level;
            scanf("%d", &level);
            redBlackTree.redBlackSum(level);
        }
        else if(ch==7){     ///Common Ancestor
            int a, b, sum;
            scanf("%d %d", &a, &b);
            int c = redBlackTree.commonAncestor(a,b);

            if(c == NULL_VALUE){
                printf("No common ancestor present.\n");
            }
            else{
                printf("Common Ancestor = %d\n", c);
            }

        }
        else if(ch==8){     ///Range Sum
            int a, b, sum;
            scanf("%d %d", &a, &b);
            int x = a<b? a: b;
            int y = a>b? a: b;
            sum = redBlackTree.rangeSum(x,y);
            printf("Sum of keys within %d-%d range = %d\n", x, y, sum);
        }
        else if(ch==9){     ///exit
            printf("Exiting...\n");
            break;
        }
        else{
            printf("Invalid Input\n");
        }




    }




}

