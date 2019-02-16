///Hashing Offline by 1505080

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>
#include <vector>

#define MAXTABLESIZE 10000
#define NUMBEROFDATA 10000

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

int main() {
    srand(time(NULL));

    HashTableLP hLP1(hashFunc1);
    HashTableLP hLP2(hashFunc2);
    HashTableLP hLP3(hashFunc3);

    HashTableSC hSC1(hashFunc1);
    HashTableSC hSC2(hashFunc2);
    HashTableSC hSC3(hashFunc3);


    char * searchTest[NUMBEROFDATA];
    for(int i=0; i<NUMBEROFDATA; i++){
        searchTest[i]=NULL;
    }

    ///collision rate checking
    printf("***Checking collision rate of the hash functions***\n");
    int colTest = 10;
    double r1=0, r2=0, r3=0;
    for(int i = 0; i < colTest; i++){
        r1 += findCollisionRate(hashFunc1);
        r2 += findCollisionRate(hashFunc2);
        r3 += findCollisionRate(hashFunc3);
    }
    r1/=colTest;
    r2/=colTest;
    r3/=colTest;
    printf("hashFunc1 Collision rate = %f\n", r1);
    printf("hashFunc2 Collision rate = %f\n", r2);
    printf("hashFunc3 Collision rate = %f\n", r3);


    /// testing Linear probing making maxsize = 6
    /*hSC1.insertData("NILOY", 1);
    hSC1.insertData("DIGIT", 2);
    hSC1.insertData("VISIT", 3);
    hSC1.insertData("BOOKS", 4);
    hSC1.insertData("INTRO", 5);
    hSC1.printAllPair();
    cout << "Collisions : " << hSC1.getCollision() <<  endl << endl;

    hSC1.deleteData("NILOY");
    hSC1.insertData("HAZRA", 6);
    hSC1.insertData("MATIN", 7);
    hSC1.printAllPair();
    cout << "Collisions : " << hSC1.getCollision() <<  endl << endl;

    hSC1.deleteData("INTRO");
    hSC1.insertData("NILOY", 8);
    hSC1.insertData("DUMMY", 9);
    hSC1.printAllPair();
    */


    printf("\nGenerating and inserting initial data...\n");
    int val1 = 1, val2=1, val3=1, val4=1, val5=1, val6=1;
    int discard1 = 1, discard2=1, discard3=1, discard4=1, discard5=1, discard6=1;
    bool check1 = false, check2 = false, check3 = false, check4 = false, check5 = false, check6 = false;
    char *str;
    while(val1 <= NUMBEROFDATA){    ///data insertion
        str = stringGenerator();
        check1 = hLP1.insertData(str, val1);
        if(check1) val1++;
        else discard1++;

        check2 = hLP2.insertData(str, val2);
        if(check2) val2++;
        else discard2++;

        check3 = hLP3.insertData(str, val3);
        if(check3) val3++;
        else discard3++;

        check4 = hSC1.insertData(str, val1);
        if(check4) val4++;
        else discard4++;

        check5 = hSC2.insertData(str, val1);
        if(check5) val5++;
        else discard5++;

        check6 = hSC3.insertData(str, val1);
        if(check6) val6++;
        else discard6++;

        delete []str;

    }

    printf("Checking discards: %d %d %d %d %d %d\n", discard1, discard2, discard3, discard4, discard5, discard6);
    printf("Checking values: %d %d %d %d %d %d\n", val1, val2, val3, val4, val5, val6);

    printf("\nGenerating test search strings...\n");
    for(int i=0; i<NUMBEROFDATA; i++){
        searchTest[i] = stringGenerator();
    }

    printf("\n***Results for Linear Probing***\n\n");

    printf("Linear Probing with Hash function 1:\n");
    hLP1.generateResultLP(searchTest);
    printf("Linear Probing with Hash function 2:\n");
    hLP2.generateResultLP(searchTest);
    printf("Linear Probing with Hash function 3:\n");
    hLP3.generateResultLP(searchTest);

    printf("\n***Results for Separate Chaining***\n\n");

    printf("Separate Chaining with Hash function 1:\n");
    hSC1.generateResultSC(searchTest);
    printf("Separate Chaining with Hash function 2:\n");
    hSC2.generateResultSC(searchTest);
    printf("Separate Chaining with Hash function 3:\n");
    hSC3.generateResultSC(searchTest);



    return 0;
}
