#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<complex.h>
#include<math.h>

//Global variable
int degree=1;
char s_left[100]={0},s_right[100]={0};

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

    // Adding the sub-string
    for(i=p;i<s;i++){
        x = c[i];
        if(t<n)
        {
            a[i] = b[t];
            t=t+1;
        }
        a[o]=x;
        o=o+1;
    }
    return a;
}

//Function to remove spaces between the equation
char * rem_space(char *s)
{
    int i,j, len=strlen(s);
	for(i=0; i<len; i++)
	{
	    if(s[i]==' '&&s[i+1]!='=')
		{
			for(j=i; j<len; j++)
			{
				s[j]=s[j+1];
			}
		len--;
		}
	}
    for(i=0; s[i]; i++)
    {
        if(s[i]>='a'&&s[i]<='z')
        {
            if(i>0)
            {
                if(!(s[i-1]>='0'&&s[i-1]<='9'))
                {
                    s=append(s,2,i);
                }
            }
            else
            {
                s=append(s,2,i);
            }
        }
    }
     for(i=0; s[i]; i++)
    {
        if(s[i]>='a'&&s[i]<='z')
        {
            if(s[i+1]!='^')
            {
                s=append(s,1,i+1);
            }
        }
    }
    return (s);
}
    
//Function for separating the left side and right side with some changes
void side_separation(char*s)
{
    int i,j=0;
    for(i=0;s[i]!='=';i++)
    {
        s_left[i]=s[i];
    }
    s_left[i]=' ';//There should me a space bar before the end for certain uses
    s_left[i+1]=0;
    for(i=i+1;s[i];i++,j++)
    {
        s_right[j]=s[i];
    }
    s_right[i]=' ';//There should me a space bar before the end for certain uses
    s_right[i+1]=0;
}