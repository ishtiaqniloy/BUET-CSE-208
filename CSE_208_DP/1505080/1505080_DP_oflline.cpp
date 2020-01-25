#include <iostream>
#include <cstdio>
#include  <cstdlib>
#include <cstring>

#define diagonal   1
#define left  2
#define up  3

#include <stack>

using namespace std;

int sigma(int match, int misMatch, char a, char b){
    if(a==b)    return match;
    else return misMatch;
}

int maxfunc(int a, int b, int c){
    int x = a;
    x = b>x? b : x;
    x = c>x? c : x;
    return x;
}

void Needleman_Wunsch(int n, int m, int match, int misMatch, int gap, char *s, char *t){
    int a, b, c;
    //printf("%d %d %d %d %d\n", n, m, match, misMatch, gap);
    //printf("%s %s\n", s, t);

    int arr[n+1][m+1];  ///initialization
    int dir[n+1][m+1];
    arr[0][0]=0;
    for(int i=1; i<n+1; i++){
        arr[i][0] = arr[i-1][0]+gap;
        dir[i][0] = up;
    }

    for(int i=1; i<m+1; i++){
        arr[0][i]=arr[0][i-1]+gap;
        dir[0][i] = left;

    }

    for(int i=1; i<n+1; i++){
        for(int j=1; j<m+1; j++){
            a = arr[i-1][j-1] + sigma(match, misMatch, s[i-1],t[j-1]);
            b = arr[i-1][j] + gap;
            c = arr[i][j-1] + gap;

            if(a>=b && a>=c){
                arr[i][j] = a;
                dir[i][j] = diagonal;
            }
            else if(b>=a && b>=c){
                arr[i][j] = b;
                dir[i][j] = up;
            }
            else{
                arr[i][j] = c;
                dir[i][j] = left;
            }

        }
    }

    stack <char> s2;
    stack <char> t2;

    int i= n;
    int j = m;
    while(i>0 || j>0){
        if(dir[i][j]==diagonal){
            s2.push(s[i-1]);
            t2.push(t[j-1]);
            i--;
            j--;
        }
        else if (dir[i][j] == left){
            s2.push('-');
            t2.push(t[j-1]);
            j--;
        }
        else{
            s2.push(s[i-1]);
            t2.push('-');
            i--;
        }
    }

    /*for(int i=0; i<n+1; i++){
        for(int j=0; j<m+1; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }*/

    printf("\n***Needleman-Wunsch OUTPUT***\n");
    printf("Global Alignment Score = %d\n", arr[n][m]);
    while(!s2.empty()){
        printf("%c", s2.top());
        s2.pop();
    }
    printf("\n");

    while(!t2.empty()){
        printf("%c", t2.top());
        t2.pop();
    }
    printf("\n");

}


void Smith_Waterman(int n, int m, int match, int misMatch, int gap, char *s, char *t){
    int a, b, c;
    //printf("%d %d %d %d %d\n", n, m, match, misMatch, gap);
    //printf("%s %s\n", s, t);

    int arr[n+1][m+1];  ///initialization
    int dir[n+1][m+1];
    arr[0][0]=0;
    for(int i=1; i<n+1; i++){
        arr[i][0] = 0;
        dir[i][0] = 0;
    }

    for(int i=1; i<m+1; i++){
        arr[0][i] = 0;
        dir[0][i] = 0;

    }

    int maxVal=0, maxi=0, maxj=0;

    for(int i=1; i<n+1; i++){
        for(int j=1; j<m+1; j++){
            a = arr[i-1][j-1] + sigma(match, misMatch, s[i-1],t[j-1]);
            b = arr[i-1][j] + gap;
            c = arr[i][j-1] + gap;

            if(a>0 && a>=b && a>=c){
                arr[i][j] = a;
                dir[i][j] = diagonal;
            }
            else if(b>0 && b>=a && b>=c){
                arr[i][j] = b;
                dir[i][j] = up;
            }
            else if(c>0 && c>=a && c>=b){
                arr[i][j] = c;
                dir[i][j] = left;
            }
            else{
                arr[i][j] = 0;
                dir[i][j] = 0;
            }

            if(maxVal < arr[i][j]){
                maxVal = arr[i][j];
                maxi = i;
                maxj = j;
            }

        }
    }

    stack <char> s2;
    stack <char> t2;

    int i= maxi;
    int j = maxj;
    while(i>0 || j>0){
        if(dir[i][j]==diagonal){
            s2.push(s[i-1]);
            t2.push(t[j-1]);
            i--;
            j--;
        }
        else if (dir[i][j] == left){
            s2.push('-');
            t2.push(t[j-1]);
            j--;
        }
        else if (dir[i][j] == up){
            s2.push(s[i-1]);
            t2.push('-');
            i--;
        }
        else    break;

    }

    /*for(int i=0; i<n+1; i++){
        for(int j=0; j<m+1; j++)
            printf("%d ", arr[i][j]);
        printf("\n");
    }*/



    printf("\n***Smith-Waterman OUTPUT***\n");
    printf("Local Alignment Score = %d\n", maxVal);
    while(!s2.empty()){
        printf("%c", s2.top());
        s2.pop();
    }
    printf("\n");

    while(!t2.empty()){
        printf("%c", t2.top());
        t2.pop();
    }
    printf("\n");



}


int main(){
    int n, m, match, misMatch, gap;
    scanf("%d %d %d %d %d", &n, &m, &match, &misMatch, &gap);
    getchar();

    char *s = new char[n+1];
    char *t = new char[m+1];

    gets(s);
    gets(t);
    //printf("%s %s\n", s, t);

    Needleman_Wunsch(n,  m,  match,  misMatch,  gap,  s,  t);
    Smith_Waterman(n,  m,  match,  misMatch,  gap,  s,  t);

    printf("\n");

    delete []s;
    delete []t;
    return 0;

}
