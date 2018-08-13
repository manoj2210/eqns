#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<complex.h>
#include<math.h>

//Function for removing all the blank spaces in the input
char * append(char *a,int number,int digit)
{
    char b[10];
    char c[100];
    int p=0,r=0,i=0;
    int t=0;
    int x,g,s,n,o;
    if(number==1){
        b[0]='^';
        b[1]='1';
        b[2]=0;
    }else{
        b[0]='1';
        b[1]=0;
    }
    p=digit;
    r = strlen(a);
    n = strlen(b);
    i=0;

    // Copying the input string into another array
    while(i <= r){
        c[i]=a[i];
        i++;
    }
    s = n+r;
    o = p+n;
    return a;
}
    