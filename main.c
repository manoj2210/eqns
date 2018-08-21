#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<complex.h>
#include<math.h>

//Global variable
int degree=1;
char s_left[100]={0},s_right[100]={0};

float coefficient_arr[26][100]={0},temp=0;
double con=0,con1=0,con2=0,con3=0;
float coefficient_input_arr[100]={0};

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

//Function for calculating the number of digits
int number_of_digits(int a)
{
    int count = 0;
    while(a != 0)
    {
        a /= 10;
        ++count;
    }
    return count;
}

//Function for converting the user defined input as arrays for calculations
void input_conversion_left(char *s)
{
    int coefficient=0;
    for(int i=0;s[i];i=i+2)
        {
            if(s[i-1]=='-'&&i>0)
                coefficient=-1*atoi(s+i);
            else
                coefficient=atoi(s+i);
            i=i-1+number_of_digits(coefficient);
            if(s[i+1]>='a'&&s[i+1]<='z')
			{
                if(s[i+2]=='^')
                    {
                            coefficient_arr[s[i+1]-'a'][s[i+3]-'0']+=coefficient;i+=3;
					}
            }
            else
            {
                con+=coefficient;
            }
        }
}

//This right side is subtracted with left side
void input_conversion_right(char *s)
{
    int coefficient=0;
    for(int i=0;s[i];i=i+2)
        {
            if(s[i-1]=='-'&&i>0)
                coefficient=-1*atoi(s+i);
            else
                coefficient=atoi(s+i);
            i=i-1+number_of_digits(coefficient);
            if(s[i+1]>='a'&&s[i+1]<='z')
			{
                if(s[i+2]=='^')
                    {
                            coefficient_arr[s[i+1]-'a'][s[i+3]-'0']+=-1*coefficient;i+=3;
					}
            }
             else
            {
                con+=-1*coefficient;
            }
        }
}

//Function for identifing The degree and the powers present
void degree_function()
{
    for(int i=0;i<26;i++)
    {
        for(int j=0;j<100;j++)
        {
            if(coefficient_arr[i][j]!=0)
            {
                if(j>degree)
                degree=j;
            }
        }
    }
 }

 /*
    Here in this function, we parse a a given string of equation to the format 
    we need it to be 
*/
void parse_input(char *equation)
{
    char *s;
    int coefficient=0;
    s=rem_space(equation);
    side_separation(s);
    input_conversion_left(s_left);
    input_conversion_right(s_right);

}

//function for finding the coefficients of the inputs
void coefficient_input()
{
    int j,var_iable=0;
    for(int i=0;i<26;i++)
    {
        for(int j=0;j<=degree;j++)
        {
            if(coefficient_arr[i][j]!=0)
            {
                var_iable=i;
            }
        }
    }
    int m=0,k;
    k=coefficient_arr[var_iable][degree];
    for(int i=degree-1;i!=0;i--,m++)
    {

        coefficient_input_arr[m]=coefficient_arr[var_iable][i];
        coefficient_input_arr[m]/=k;
    }
    coefficient_input_arr[degree-1]=con;
    coefficient_input_arr[degree-1]/=k;
}

//Function for evaluation of factors
// "poly" evaluates at x a polynomial of the form:
// f(x) = cpow(x, n) + a1*cpow(x, n - 1) + a2*cpow(x, n - 2) + . . . + a(n - 2)*x*x + a(n - 1)*x + a(n)
// where the vector A = {a1, a2, a3, . . . , a(n - 2), a(n - 1), a(n)}
double complex poly(int degree, double complex x)
{
    double complex y = cpow(x, degree);
    for (int i = 0; i < degree; i++)
        y += coefficient_input_arr[i]*cpow(x, (degree - i - 1) );
    return y;
}


// polyroot uses the Durand-Kerner method to find all roots (real and complex) of a polynomial of the form:
// f(x) = cpow(x, n) + a1*cpow(x, n - 1) + a2*cpow(x, n - 2) + . . . + a(n - 2)*x*x + a(n - 1)*x + a(n)
// where the vector A = {a1, a2, a3, . . . , a(n - 2), a(n - 1), a(n)}
double complex * polyroot(int degree)
{
    int iterations = 1000;
    double complex z = 0.4+ 0.9*I;
    int size = sizeof(z);
    double complex * R;
    R = (double complex *) malloc(size*degree);
    for (int i = 0; i < degree; i++)
        R[i] = cpow(z, i);
    for (int i = 0; i < iterations; i++)
    {
        for (int j = 0; j < degree; j ++)
        {
            double complex B = poly(degree, R[j]);
            for (int k = 0; k < degree; k++)
            {
                if (k != j)
                B /= R[j] - R[k];
            }
            R[j] -= B;
        }
    }
    return R;
}

//function for evaluation
void evaluation(char *str)
{
    int coefficient=0;
    char *s;
    s=rem_space(str);
    side_separation(s);
    input_conversion_left(s_left);
    input_conversion_right(s_right);

    degree_function();
    coefficient_input();
}