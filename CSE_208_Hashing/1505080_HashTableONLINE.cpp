///Hashing Online by 1505080

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>
#include <vector>

#define MAXTABLESIZE 100
#define NUMBEROFDATA 100

#define MAXKEYSIZE  20
#define KEYSIZE 5

#define largePrime 67280421310721

#define NULL_VALUE -999999

using namespace std;

char * stringGenerator(){
    char * str = new char[MAXKEYSIZE];
    int rn;

    for(int i=0; i<KEYSIZE; i++){
        str[i] = 'A' + rand()%26;
    }
    str[KEYSIZE] = 0;

    return str;
}

unsigned long long hashFunc1(char *str){
    unsigned long long hashVal = (strlen(str)* 63533) %largePrime ;

    int arr [MAXKEYSIZE+20]= {104729, 65827, 101749, 37447, 101203, 54049, 89809,  99347, 104087, 16927, 96749, 93053, 91541, 87589, 80021, 92959, 93911, 77417, 95801, 97103, 89443, 79423, 75403, 101939, 103099, 61933};

    for (int i = 0; i < KEYSIZE; i++) {
        hashVal =  ( (hashVal*arr[MAXKEYSIZE-1-i] )  % largePrime + ( (str[i]) * arr[i]) % largePrime )   % largePrime;
    }

    return hashVal % largePrime ;
}

unsigned long long hashFunc2(char *str){
    unsigned long long hashVal = strlen(str) %largePrime;

    const int k = 65599;

    for (int i = 0; i < KEYSIZE; i++) {
        hashVal = ( (str[i]-'A')%largePrime + (hashVal << 6)%largePrime + (hashVal << 16)%largePrime - hashVal%largePrime ) %largePrime;
        //hashVal = ( (str[i])%largePrime + (hashVal*k)%largePrime ) %largePrime;
    }
    //printf("%llu ", hashVal);
    return hashVal;
}

unsigned long long hashFunc3(char *str){
    unsigned long long hashVal = 5381;

    for (int i = 0; i < KEYSIZE; i++) {
        hashVal = ( (((hashVal << 5 ) + hashVal) %largePrime ) ^ (unsigned long long) str[i] ) %largePrime ;
    }

    return hashVal;
}


float findCollisionRate(unsigned long long (*hFunction) (char *str)){
    char * str;

    bool arr[MAXTABLESIZE];
    for (int j = 0; j < MAXTABLESIZE; j++) {
        arr[j] = false;
    }

    int counter = 0, idx;
    unsigned long long hashVal;

    for (int i = 0; i < MAXTABLESIZE; i++) {
        str =  stringGenerator();
        hashVal = hFunction(str);
        idx = hashVal % MAXTABLESIZE;
        //cout << i << ": " << str << " " << hashVal << " " << idx << endl;
        if(arr[idx])    counter++;
        else arr[idx] = true;

    }

    float rate = 100.0*counter/MAXTABLESIZE;

    return rate;
}

/*
class HashTableLP{
    class HashDataLP{
    public:
        char* key;
        int value;

        HashDataLP(char * str, int data){
            key = new char[MAXKEYSIZE];
            strcpy(key, str);
            value = data;
            //delete []str;
        }

        ~HashDataLP(){
            //printf("Destroying Linear Probing Data...\n");
            delete[] key;
            key = NULL;
        }

    };

    HashDataLP * arr[MAXTABLESIZE];
    unsigned long long (*hFunction) (char *str);
    bool deletionCheck[MAXTABLESIZE];
    int collision;

public:
    HashTableLP(unsigned long long (*func) (char *str)){
        hFunction = func;

        for(int i=0; i<MAXTABLESIZE; i++){
            arr[i] = NULL;
            deletionCheck[i] = false;
        }
        collision = 0;

    }

    ~HashTableLP(){
        printf("Destroying Linear Probing Table...\n");
        for(int i=0; i<MAXTABLESIZE; i++){
            delete arr[i];
            arr[i] = NULL;
        }
        //delete []arr;
    }

    int searchData(char *str){
        int idxStarter = hFunction(str) % MAXTABLESIZE;
        int idx = idxStarter;

        while(arr[idx] != NULL || deletionCheck[idx] ){
            //cout << "Check : idx = " << idx << "arr[idx] = " << arr[idx] << endl;
            if(arr[idx]==NULL && deletionCheck[idx] == false){
                return NULL_VALUE;
            }

            if(arr[idx]!= NULL && strcmp(arr[idx]->key, str) == 0)
                return idx;
            idx = (idx+1) % MAXTABLESIZE;

            if(idx == idxStarter)
                break;

        }
        return NULL_VALUE;

    }

    bool deleteData(char *str){
        int idx = searchData(str);

        if(idx == NULL_VALUE)
            return false;

        deletionCheck[idx] = true;
        delete arr[idx];
        arr[idx] = NULL;
        //printf("%d", arr[idx]);
        return true;
    }

    bool insertData(char *str, int value){
        if(searchData(str)!=NULL_VALUE){
            return false;
        }
        int idxStarter = hFunction(str) % MAXTABLESIZE;
        int idx = idxStarter;

        if(arr[idx]!=NULL)
            collision++;

        while(arr[idx]!=NULL){
            idx = (idx+1) % MAXTABLESIZE ;
            if(idx == idxStarter)
                return false;
        }

        arr[idx] = new HashDataLP(str, value);

        return true;

    }

    int getValue(char *str){
        int idx = searchData(str);
        if(idx == NULL_VALUE)
            return idx;
        else
            return arr[idx]->value;

    }

    int getCollision(){
        return collision;
    }

    void printAllPair(){
        for(int i=0; i<MAXTABLESIZE; i++){
            if(arr[i]!=NULL){
                printf("%d : (%s , %d)\n", i , arr[i]->key, arr[i]->value);

            }

        }
    }

    void generateResultLP(char * searchTest[]){
        clock_t startTime, endTime;
        double timeDiff;
        int successfulSearch = 0, s;

        startTime = clock();
        for(int i=0; i<NUMBEROFDATA; i++){
            s = searchData(searchTest[i]);
            if(s!=NULL_VALUE)
                successfulSearch++;
        }
        endTime = clock();
        timeDiff = 1000 * ( endTime - startTime ) / (double)CLOCKS_PER_SEC;

        printf("Number of collisions: %d\n", collision );
        printf("Search time for %d searches: %lf milisec\n", NUMBEROFDATA, timeDiff);
        printf("Average time for search: %lf milisec\n", timeDiff/NUMBEROFDATA);
        printf("Number of Successful Searches: %d\n\n", successfulSearch);

    }


};

class HashTableSC{
    class HashDataSC{
    public:
        char* key;
        int value;
        HashDataSC *nextData;

        HashDataSC(char * str, int data, HashDataSC *next = NULL){
            key = new char[MAXKEYSIZE];
            strcpy(key, str);
            value = data;
            nextData = next;
            //delete []str;
        }

        ~HashDataSC(){
            //printf("Destroying Separate Chaining Data...\n");
            delete[] key;
            key = NULL;
            delete nextData;
            nextData = NULL;
        }
    };

    HashDataSC * arr[MAXTABLESIZE];
    unsigned long long (*hFunction) (char *str);
    int collision;
public:
    HashTableSC(unsigned long long (*func) (char *str)){
        hFunction = func;
        for(int i=0; i<MAXTABLESIZE; i++){
            arr[i] = NULL;
        }
        collision = 0;

    }

    ~HashTableSC(){
        printf("Destroying Separate Chaining Table...\n");
        for(int i=0; i<MAXTABLESIZE; i++){
            delete arr[i];
            arr[i] = NULL;
        }
        //delete []arr;
    }

    int searchData(char *str){
        int idx = hFunction(str) % MAXTABLESIZE;

        if(arr[idx] == NULL)
            return NULL_VALUE;

        HashDataSC *temp = arr[idx];

        while(temp!=NULL){
            if(strcmp(temp->key, str) == 0)
                return idx;
            temp = temp->nextData;

        }
        return NULL_VALUE;

    }

    bool deleteData(char *str){
        int idx = hFunction(str) % MAXTABLESIZE;

        if(arr[idx] == NULL){
            return false;
        }


        HashDataSC *temp = arr[idx];
        HashDataSC *par = NULL;

        if(strcmp(arr[idx]->key, str)==0 ){    ///data in head
            arr[idx] = arr[idx]->nextData;
            temp->nextData = NULL;
            delete temp;
            return true;
        }

        par = temp;
        temp = par->nextData;
        while(temp!=NULL){
            if(strcmp(temp->key, str) == 0){
                par->nextData = temp->nextData;
                temp->nextData = NULL;
                delete temp;
                return true;
            }
            par = temp;
            temp = par->nextData;

        }

        return false;
    }

    bool insertData(char *str, int value){
        if(searchData(str)!=NULL_VALUE){
            return false;
        }

        int idx = hFunction(str) % MAXTABLESIZE;
        HashDataSC *temp = new HashDataSC(str, value);

        if(arr[idx]==NULL){ ///head is null
            arr[idx] = temp;
            return true;
        }

        else{           ///head is not null, inserting at head
            collision++;
            temp->nextData = arr[idx];
            arr[idx] = temp;
            return true;

        }
    }

    int getValue(char *str){
        int idx = hFunction(str) % MAXTABLESIZE;

        if(arr[idx] == NULL)
            return NULL_VALUE;

        HashDataSC *temp = arr[idx];

        while(temp!=NULL){
            if(strcmp(temp->key, str) == 0)
                return temp->value;
            temp = temp->nextData;

        }
        return NULL_VALUE;

    }

    int getCollision(){
        return collision;
    }

    void printAllPair(){
        HashDataSC *temp = NULL;
        for(int i=0; i<MAXTABLESIZE; i++){
            if(arr[i]!=NULL){
                printf("%d : ", i);
                temp = arr[i];
                while(temp!=NULL){
                    printf("(%s , %d) ", temp->key, temp->value);
                    temp = temp->nextData;
                }
                printf("\n");

            }

        }
    }

    void generateResultSC(char * searchTest[]){
        clock_t startTime, endTime;
        double timeDiff;
        int successfulSearch = 0, s;

        startTime = clock();
        for(int i=0; i<NUMBEROFDATA; i++){
            s = searchData(searchTest[i]);
            if(s!=NULL_VALUE)
                successfulSearch++;
        }
        endTime = clock();
        timeDiff = 1000 * ( endTime - startTime ) / (double)CLOCKS_PER_SEC;

        printf("Number of collisions: %d\n", collision );
        printf("Search time for %d searches: %lf milisec\n", NUMBEROFDATA, timeDiff);
        printf("Average time for search: %lf milisec\n", timeDiff/NUMBEROFDATA);
        printf("Number of Successful Searches: %d\n\n", successfulSearch);

    }






};

*/

class HashTableVector{
    class HashDataVector{
    public:
        char key[MAXKEYSIZE];
        int value;

        HashDataVector(char * str, int data){
            strcpy(key, str);
            value = data;
        }
    };

    //HashDataLP * arr[MAXTABLESIZE];
    vector <HashDataVector> arr[MAXTABLESIZE];
    unsigned long long (*hFunction) (char *str);
    int collision;
public:
    HashTableVector(unsigned long long (*func) (char *str)){
        hFunction = func;
        collision = 0;
        for(int i=0; i<MAXTABLESIZE; i++){
            arr[i].reserve(10);
        }

    }

    ~HashTableVector(){
        printf("Destroying Hash Table with Vector...\n");
        /*for(int i=0; i<MAXTABLESIZE; i++){
            delete arr[i];
            arr[i] = NULL;
        }*/
        //delete []arr;
    }

    int searchData(char *str){
        cout << "in search " << str << endl;
        int idx = hFunction(str) % MAXTABLESIZE;
        int first = 0, last = arr[idx].size();
        int mid = (first+last)/2;

        if(last==0){
            //printf("size  = %d\n", last);
            return NULL_VALUE;
        }

        while(first<last){
                //cout << "In while" << endl;
            mid = (first+last)/2;
            if(strcmp(arr[idx].at(mid).key, str )==0){
                return mid;
            }

            else if(strcmp(arr[idx].at(mid).key, str )<0){
                first = mid;
            }
            else{
                last = mid;
            }

        }

        if(strcmp(arr[idx].at(mid).key, str )==0){
                return mid;
        }

        return NULL_VALUE;

    }

    bool deleteData(char *str){
        int pos = searchData(str);
        if(pos == NULL_VALUE)
            return false;

        int idx = hFunction(str) % MAXTABLESIZE;
        arr[idx].erase(arr[idx].begin() + pos);

        return true;
    }

    bool insertData(char *str, int value){
        cout << "in insert " << str << endl;
        if(searchData(str)!=NULL_VALUE){
            return false;
        }
        cout << "not found " << str << endl;

        HashDataVector temp(str, value);
        int idx = hFunction(str) % MAXTABLESIZE;
        int first = 0, last =  arr[idx].size();
        int mid = (first+last)/2;

        //arr[idx].push_back(temp);
       //return true;


        if(last != 0)
            collision++;

        while(first<last){
            mid = (first+last)/2;
            if( strcmp(arr[idx].at(mid).key, str ) < 0 && strcmp(arr[idx].at(mid+1).key, str ) > 0){
                arr[idx].insert( arr[idx].begin() + mid , temp);
                return true;

            }

            else if(strcmp(arr[idx].at(mid).key, str )<0){
                first = mid;
            }
            else{
                last = mid;
            }


        }

        arr[idx].insert( arr[idx].begin() + mid , temp);
        return true;

        //return false;

    }


    void printAllPair(){
        for(int i=0; i<MAXTABLESIZE; i++){
            int len = arr[i].size();
            if(len==0){
                continue;
            }
            printf("%d : ", i);
            for(int j=0; j<len; j++){
                printf("(%s , %d) ", arr[i][j].key, arr[i][j].value);
            }
            printf("\n");
        }
    }

};

int main() {
    srand(time(NULL));

    HashTableVector hv(hashFunc2);

    char * searchTest[NUMBEROFDATA];
    for(int i=0; i<NUMBEROFDATA; i++){
        searchTest[i]=NULL;
    }

    printf("\nGenerating and inserting initial data...\n");

    int val = 1, discard = 0;
    bool check = false;

    char *str;
    while(val <= NUMBEROFDATA){    ///data insertion
        str = stringGenerator();

        check = hv.insertData(str, val);

        if(check){
            val++;
            cout << "inserted " << str << endl;
        }
        else{
            discard ++;
            cout << "discarded " << str << endl;
        }


        delete []str;

    }

    //printf("%d\n",strcmp("HELLO", "WORLD"));

    hv.printAllPair();

    printf("\nGenerating test search strings...\n");
    for(int i=0; i<NUMBEROFDATA; i++){
        searchTest[i] = stringGenerator();
    }




    return 0;
}
