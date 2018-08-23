#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<complex.h>
#include<math.h>

//Declaration
void evaluation(char *str);
void coefficient_input();
int number_of_digits(int a);
void side_separation(char*s);
char * rem_space(char *s);
void input_conversion_left(char *s);
void input_conversion_right(char *s);
double complex poly(int , double complex);
double complex * polyroot(int );
void factorize(char *str);
float two_variablesolve(float a1,float b1,float a2,float b2,char var1,char var2);
void solve_2_equations();
void solve_3_equations();
void findSolution(double coeff[3][4]);
double determinantOfMatrix(double mat[3][3]);

char * complex_to_string(double complex number);
void compute_factors(GtkWidget *widget, GtkWidget *text);
void print_to_label(GtkWidget *label, char *string, int clear_before_printing);
void reset_all();
void parse_input(char *equation);


// The label in which the factors in Factorize screen are shown
GtkWidget *factors_output_label;

// The label in which the solution are shown(in both 2 equation and 3 equation screens) are shown
GtkWidget *solution_output_label;

// A GtkEntry which will act as an input for equation
GtkWidget *equation_textbox1;

// A GtkEntry which will act as an input for equation
GtkWidget *equation_textbox2;

// A GtkEntry which will act as an input for equation
GtkWidget *equation_textbox3;

//Global variable
int degree=1;
char s_left[100]={0},s_right[100]={0};
float coefficient_arr[26][100]={0},temp=0;
float coefficient_input_arr[100]={0};
float coefficient_arr1[26][100]={0};
float coefficient_arr2[26][100]={0};
float coefficient_arr3[26][100]={0};
double con=0,con1=0,con2=0,con3=0;

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

void factorize(char *str)
{
    evaluation(str);
    double complex * factors = polyroot(degree);
    
    //A temporary placeholder for strings that are printed to GTK window.
    char string_to_print[50];
    //Print out the evaluated equation
    sprintf(string_to_print, "The given equation is : \n\n\0");
    print_to_label(factors_output_label,string_to_print,0);

    for(int i=0;i<26;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(coefficient_arr[i][j]!=0)
            {
                g_print("%+.2f%c^%d ",coefficient_arr[i][j],i+'a',j);
                
                sprintf(string_to_print, "%+.2f%c^%d \0",coefficient_arr[i][j],i+'a',j);
                print_to_label(factors_output_label,string_to_print,0);
            }
        }
    }
    g_print("%+.2f = 0",con);
    sprintf(string_to_print, "%+.2f = 0",con);
    print_to_label(factors_output_label,string_to_print,0);
    
    print_to_label(factors_output_label,"\n\nThe roots are : ", 0);
    for(int i=0;i<degree;i++)
    {
        g_print(complex_to_string(factors[i]));

        sprintf(string_to_print, "\n%s", complex_to_string(factors[i]));
        print_to_label(factors_output_label, string_to_print, 0);

    }
}

// Set up the UI for a screen
void show_factorize_screen(GtkWidget *widget, GtkApplication *app)
{
    // The window that contains all the widgets.
    GtkWidget *window;

    // A button with the label "Factorize" that calculates fators when clicked
    GtkWidget *factorize_button;

    // The grid in which all the widgets are placed
    GtkWidget *grid;

    // A GtkEntry which will act as an input for equation
    GtkWidget *equation_textbox;

    // A label with the text "Enter an equation to factorize"
    GtkWidget *enter_eqn_label;

    // A label to show the factors after calculating.
    GtkWidget *factors_label;

    // Initialize and configure UI
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Factoize - EQNS");

    // When a window is set to modal it prevents interaction witb other windows.
    gtk_window_set_modal(GTK_WINDOW (window), TRUE);
    gtk_window_set_default_size (GTK_WINDOW (window), 1000, 500);

    equation_textbox = gtk_entry_new();
    gtk_widget_set_size_request(GTK_WIDGET(equation_textbox), 500, 20);
    gtk_entry_set_placeholder_text(GTK_ENTRY(equation_textbox), "Enter an equation !");
    factorize_button = gtk_button_new_with_label ("Factorize");
    
    g_signal_connect (factorize_button, "clicked", G_CALLBACK (compute_factors), equation_textbox);
    gtk_widget_set_size_request(GTK_WIDGET(factorize_button), 10, 30);

    enter_eqn_label = gtk_label_new("Enter an equation to factorize : ");

    factors_label = gtk_label_new("\n\n  Factors:\n ");

    grid = gtk_grid_new();
    
    gtk_widget_set_hexpand (factorize_button, TRUE);
    gtk_widget_set_halign (factorize_button, GTK_ALIGN_CENTER);

    gtk_widget_set_hexpand (equation_textbox, TRUE);
    gtk_widget_set_halign (equation_textbox, GTK_ALIGN_CENTER);

    gtk_widget_set_hexpand (factors_label, FALSE);
    gtk_widget_set_halign (factors_label, GTK_ALIGN_START);


    gtk_grid_attach(GTK_GRID(grid), enter_eqn_label, 0, 0, 10, 1);

    gtk_grid_attach_next_to(GTK_GRID(grid), equation_textbox, enter_eqn_label, GTK_POS_RIGHT, 5, 1);

    gtk_grid_attach_next_to(GTK_GRID(grid), factorize_button, equation_textbox, GTK_POS_RIGHT, 5, 1);

    gtk_grid_attach_next_to(GTK_GRID(grid), factors_label, enter_eqn_label, GTK_POS_BOTTOM, 15, 20);

    gtk_grid_attach_next_to(GTK_GRID(grid), factors_output_label, factors_label, GTK_POS_BOTTOM, 15, 20);

    gtk_container_add (GTK_CONTAINER (window), grid);
    gtk_widget_show_all (window);
}


void show_solve2equations_screen(GtkWidget *widget, GtkApplication *app)
{
    // The window that contains all the widgets.
    GtkWidget *window;

    // A button with the label "Solve" that calculates fators when clicked
    GtkWidget *solve_button;

    // The grid in which all the widgets are placed
    GtkWidget *grid;

    // A label with the text "Enter two equations in the textboxes"
    GtkWidget *enter_eqn_label;

    // A label to show the text "Solution".
    GtkWidget *solution_label;

    // Initialize and configure UI
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Solve two linear equations - EQNS");

    // When a window is set to modal it prevents interaction witb other windows.
    gtk_window_set_modal(GTK_WINDOW (window), TRUE);
    gtk_window_set_default_size (GTK_WINDOW (window), 1000, 500);

    equation_textbox1 = gtk_entry_new();
    gtk_widget_set_size_request(GTK_WIDGET(equation_textbox1), 500, 20);
    gtk_entry_set_placeholder_text(GTK_ENTRY(equation_textbox1), "Enter the first equation !");

    equation_textbox2 = gtk_entry_new();
    gtk_widget_set_size_request(GTK_WIDGET(equation_textbox2), 500, 20);
    gtk_entry_set_placeholder_text(GTK_ENTRY(equation_textbox2), "Enter the second equation !");

    solve_button = gtk_button_new_with_label ("Solve");
    
    g_signal_connect (solve_button, "clicked", G_CALLBACK (solve_2_equations), NULL);
    gtk_widget_set_size_request(GTK_WIDGET(solve_button), 10, 30);

    enter_eqn_label = gtk_label_new(" Enter two equations in the textboxes : ");

    solution_label = gtk_label_new("\n\n  Solution:\n ");


    grid = gtk_grid_new();
    
    gtk_widget_set_hexpand(solve_button, TRUE);
    gtk_widget_set_halign(solve_button, GTK_ALIGN_CENTER);

    gtk_widget_set_hexpand(equation_textbox1, TRUE);
    gtk_widget_set_halign(equation_textbox1, GTK_ALIGN_CENTER);

    gtk_widget_set_hexpand(equation_textbox2, TRUE);
    gtk_widget_set_halign(equation_textbox2, GTK_ALIGN_CENTER);


    gtk_widget_set_hexpand (solution_label, FALSE);
    gtk_widget_set_halign (solution_label, GTK_ALIGN_START);


    gtk_grid_attach(GTK_GRID(grid), enter_eqn_label, 0, 0, 10, 1);

    gtk_grid_attach_next_to(GTK_GRID(grid), equation_textbox1, enter_eqn_label, GTK_POS_RIGHT, 5, 1);

    gtk_grid_attach_next_to(GTK_GRID(grid), solve_button, equation_textbox1, GTK_POS_RIGHT, 5, 1);
    gtk_grid_attach_next_to(GTK_GRID(grid), equation_textbox2, equation_textbox1, GTK_POS_BOTTOM, 5, 1);


    gtk_grid_attach_next_to(GTK_GRID(grid), solution_label, enter_eqn_label, GTK_POS_BOTTOM, 15, 20);

    gtk_grid_attach_next_to(GTK_GRID(grid), solution_output_label, solution_label, GTK_POS_BOTTOM, 15, 20);

    gtk_container_add (GTK_CONTAINER (window), grid);
    gtk_widget_show_all (window);
}

void show_solve3equations_screen(GtkWidget *widget, GtkApplication *app)
{
    // The window that contains all the widgets.
    GtkWidget *window;

    // A button with the label "Solve" that calculates and solves the equations when clicked
    GtkWidget *solve_button;

    // The grid in which all the widgets are placed
    GtkWidget *grid;

    // A label with the text "Enter two equations in the textboxes"
    GtkWidget *enter_eqn_label;

    // A label to show the text "Solution".
    GtkWidget *solution_label;

    // Initialize and configure UI
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Solve three linear equations - EQNS");

    // When a window is set to modal it prevents interaction witb other windows.
    gtk_window_set_modal(GTK_WINDOW (window), TRUE);
    gtk_window_set_default_size (GTK_WINDOW (window), 1000, 500);

    equation_textbox1 = gtk_entry_new();
    gtk_widget_set_size_request(GTK_WIDGET(equation_textbox1), 500, 20);
    gtk_entry_set_placeholder_text(GTK_ENTRY(equation_textbox1), "Enter the first equation !");

    equation_textbox2 = gtk_entry_new();
    gtk_widget_set_size_request(GTK_WIDGET(equation_textbox2), 500, 20);
    gtk_entry_set_placeholder_text(GTK_ENTRY(equation_textbox2), "Enter the second equation !");

    equation_textbox3 = gtk_entry_new();
    gtk_widget_set_size_request(GTK_WIDGET(equation_textbox3), 500, 20);
    gtk_entry_set_placeholder_text(GTK_ENTRY(equation_textbox3), "Enter the third equation !");

    solve_button = gtk_button_new_with_label ("Solve");
    
    g_signal_connect (solve_button, "clicked", G_CALLBACK (solve_3_equations), NULL);
    gtk_widget_set_size_request(GTK_WIDGET(solve_button), 10, 30);

    enter_eqn_label = gtk_label_new(" Enter three equations in the textboxes : ");

    solution_label = gtk_label_new("\n\n\n\n  Solution:\n ");


    grid = gtk_grid_new();
    
    gtk_widget_set_hexpand(solve_button, TRUE);
    gtk_widget_set_halign(solve_button, GTK_ALIGN_CENTER);

    gtk_widget_set_hexpand(equation_textbox1, TRUE);
    gtk_widget_set_halign(equation_textbox1, GTK_ALIGN_CENTER);

    gtk_widget_set_hexpand(equation_textbox2, TRUE);
    gtk_widget_set_halign(equation_textbox2, GTK_ALIGN_CENTER);

    gtk_widget_set_hexpand(equation_textbox3, TRUE);
    gtk_widget_set_halign(equation_textbox3, GTK_ALIGN_CENTER);

    gtk_widget_set_hexpand (solution_label, FALSE);
    gtk_widget_set_halign (solution_label, GTK_ALIGN_START);


    gtk_grid_attach(GTK_GRID(grid), enter_eqn_label, 0, 0, 10, 1);

    gtk_grid_attach_next_to(GTK_GRID(grid), equation_textbox1, enter_eqn_label, GTK_POS_RIGHT, 5, 1);

    gtk_grid_attach_next_to(GTK_GRID(grid), equation_textbox2, equation_textbox1, GTK_POS_BOTTOM, 5, 1);
    gtk_grid_attach_next_to(GTK_GRID(grid), solve_button, equation_textbox2, GTK_POS_RIGHT, 5, 1);
    gtk_grid_attach_next_to(GTK_GRID(grid), equation_textbox3, equation_textbox2, GTK_POS_BOTTOM, 5, 1);

    gtk_grid_attach_next_to(GTK_GRID(grid), solution_label, enter_eqn_label, GTK_POS_BOTTOM, 15, 20);

    gtk_grid_attach_next_to(GTK_GRID(grid), solution_output_label, solution_label, GTK_POS_BOTTOM, 15, 20);

    gtk_container_add (GTK_CONTAINER (window), grid);
    gtk_widget_show_all (window);
}

void activate (GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *factorize_button;
    GtkWidget *solve2eqn_button;
    GtkWidget *solve3eqn_button;
    GtkWidget *grid;

    GtkWidget *info_label;

    // Initialize this global variable here with empty text
    factors_output_label = gtk_label_new(NULL);
    solution_output_label = gtk_label_new(NULL);

    window = gtk_application_window_new (app);
    gtk_window_set_title (GTK_WINDOW (window), "Window");
    gtk_window_set_default_size (GTK_WINDOW (window), 500, 500);

    grid = gtk_grid_new();
    gtk_container_add (GTK_CONTAINER (window), grid);

    info_label = gtk_label_new("\n\nEQNS - Manipulating Math Equations\n\nChoose an option to continue\n");

    factorize_button = gtk_button_new_with_label ("Factorize an equation(finding roots)");
    gtk_widget_set_size_request (GTK_WIDGET(factorize_button), 100, 25);
    g_signal_connect (factorize_button, "clicked", G_CALLBACK (show_factorize_screen), app);

    gtk_widget_set_hexpand(factorize_button, TRUE);
    gtk_widget_set_halign(factorize_button, GTK_ALIGN_CENTER);

    solve2eqn_button = gtk_button_new_with_label("Solve 2 equations");
    gtk_widget_set_size_request (GTK_WIDGET(solve2eqn_button), 100, 25);
    g_signal_connect (solve2eqn_button, "clicked", G_CALLBACK (show_solve2equations_screen), app);

    gtk_widget_set_hexpand(solve2eqn_button, TRUE);
    gtk_widget_set_halign(solve2eqn_button, GTK_ALIGN_CENTER);

    solve3eqn_button = gtk_button_new_with_label("Solve 3 equations");
    gtk_widget_set_size_request (GTK_WIDGET(solve3eqn_button), 100, 25);
    g_signal_connect (solve3eqn_button, "clicked", G_CALLBACK (show_solve3equations_screen), app);

    gtk_widget_set_hexpand(solve3eqn_button, TRUE);
    gtk_widget_set_halign(solve3eqn_button, GTK_ALIGN_CENTER);

    gtk_grid_attach(GTK_GRID(grid), info_label, 0, 0, 10, 1);
    gtk_grid_attach_next_to(GTK_GRID(grid), factorize_button, info_label, GTK_POS_BOTTOM, 10, 10);
    gtk_grid_attach_next_to(GTK_GRID(grid), solve2eqn_button, factorize_button, GTK_POS_BOTTOM, 10, 10);
    gtk_grid_attach_next_to(GTK_GRID(grid), solve3eqn_button, solve2eqn_button, GTK_POS_BOTTOM, 10, 10);

    gtk_widget_show_all (window);
}


int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;

    // Initializing this here as it can be initialized only once.
    app = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;

}

void solve_2_equations()
{
    float a1,b1,a2,b2;
    int var1=0,var2=0;

    char equation1[100];
    char equation2[100];

    // A temporary place for holding the string to be shown on the GTK window. 
    char string_to_print[150];

    strcpy(equation1, gtk_entry_get_text(GTK_ENTRY(equation_textbox1)));
    strcpy(equation2, gtk_entry_get_text(GTK_ENTRY(equation_textbox2)));

    // Reset all the variables to their initial value;
    reset_all();
    parse_input(equation1);
    con1=con;
    con=0;
    for(int i=0;i<26;i++)
    {
        coefficient_arr1[i][1]=coefficient_arr[i][1];
        coefficient_arr[i][1]=0;
    }

    //Output the given equation 1, Print the co-efficients seperately and then the constant seperately.
    g_print("\nGiven equation 1:  ");
    // Here we clear the exixting text in label
    print_to_label(solution_output_label,"\nGiven equation 1:  ",1);
    for(int i=0;i<26;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(coefficient_arr1[i][j]!=0)
            {
                sprintf(string_to_print, "%+.2f%c^%d \0",coefficient_arr1[i][j],i+'a',j);
                g_print(string_to_print);
                print_to_label(solution_output_label,string_to_print,0);

            }
        }
    }
    // Print the constant and append a zero to the end.
    sprintf(string_to_print, "%+.2f = 0\n", con1);
    g_print(string_to_print);
    print_to_label(solution_output_label,string_to_print,0);

    // Parse the second equation.
    parse_input(equation2);
    con2=con;
    for(int i=0;i<26;i++)
    {
        coefficient_arr2[i][1]=coefficient_arr[i][1];
    }

    //Output the given equation 1, Print the co-efficients seperately and then the constant seperately.
    g_print("\nGiven equation 2:  ");
    print_to_label(solution_output_label,"\nGiven equation 2:  ",0);
    for(int i=0;i<26;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(coefficient_arr2[i][j]!=0)
            {
                sprintf(string_to_print, "%+.2f%c^%d \0",coefficient_arr2[i][j],i+'a',j);
                g_print(string_to_print);
                print_to_label(solution_output_label,string_to_print,0);
            }
        }
    }

    // Print the constant and append a zero to the end.
    sprintf(string_to_print, "%+.2f = 0\n", con2);
    g_print(string_to_print);
    print_to_label(solution_output_label,string_to_print,0);

    for(int i=0,j=0;i<26;i++)
    {
        if(j==0)
        {
            if(coefficient_arr1[i][1]!=0||coefficient_arr2[i][1]!=0)
            {
                a1=coefficient_arr1[i][1];
                a2=coefficient_arr2[i][1];j=1;var1=i;
                continue ;
            }
        }
        if(j==1)
        {
             if(coefficient_arr1[i][1]!=0||coefficient_arr2[i][1]!=0)
            {
                b1=coefficient_arr1[i][1];
                b2=coefficient_arr2[i][1];var2=i;
            }
        }
    }
    // This is just for logging the process to the terminal.
    g_print("\nCo-efficients of one variable: %f %f",a1,a2);
    g_print("\nCo-efficients of another variable: %f %f",b1,b2);
    g_print("Constants: %f %f",con1,con2);
    two_variablesolve(a1,b1,a2,b2,var1,var2);
    
}

float two_variablesolve(float a1,float b1,float a2,float b2,char var1,char var2)
{
    float x=0,y=0;
    char string_to_print[500];
    if((a1*b2 - a2*b1))
    {
        x = (b1*con2 - b2*con1) / (a1*b2 - a2*b1);
        y = (con1*a2 - con2*a1) / (a1*b2 - a2*b1);
    }
    else
    {
        if((a1*b2 - a2*b1)==0)
        {
            if((b1*con2 - b2*con1)==0&&(con1*a2 - con2*a1)==0)
            {
                g_print("Infinitely many solutions\n");
                print_to_label(solution_output_label,"This system of equations has infinitely many solutions \n",0);
            }
            else
            {
                g_print("No Solution\n");
                print_to_label(solution_output_label,"This system of equations has no solution \n",0);
            }
        }
    }
    g_print("\n%c=%.2f\t%c=%.2f\n",var1+'a',x,var2+'a',y);
    sprintf(string_to_print, "\nOn solving, we get \n%c = %.2f\t %c = %.2f\n", var1+'a', x, var2+'a', y);
    print_to_label(solution_output_label, string_to_print, 0);
    return 0;
}


// This functions finds the determinant of Matrix 
double determinantOfMatrix(double mat[3][3]) 
{ 
    double ans; 
    ans = mat[0][0] * (mat[1][1] * mat[2][2] - mat[2][1] * mat[1][2]) 
          - mat[0][1] * (mat[1][0] * mat[2][2] - mat[1][2] * mat[2][0]) 
          + mat[0][2] * (mat[1][0] * mat[2][1] - mat[1][1] * mat[2][0]); 
    return ans; 
} 
  
// This function finds the solution of system of 
// linear equations using cramer's rule 
void findSolution(double coeff[3][4]) 
{
    char string_to_print[150];
    // Matrix d using coeff as given in cramer's rule 
    double d[3][3] = { 
        { coeff[0][0], coeff[0][1], coeff[0][2] }, 
        { coeff[1][0], coeff[1][1], coeff[1][2] }, 
        { coeff[2][0], coeff[2][1], coeff[2][2] }, 
    }; 
    // Matrix d1 using coeff as given in cramer's rule 
    double d1[3][3] = { 
        { coeff[0][3], coeff[0][1], coeff[0][2] }, 
        { coeff[1][3], coeff[1][1], coeff[1][2] }, 
        { coeff[2][3], coeff[2][1], coeff[2][2] }, 
    }; 
    // Matrix d2 using coeff as given in cramer's rule 
    double d2[3][3] = { 
        { coeff[0][0], coeff[0][3], coeff[0][2] }, 
        { coeff[1][0], coeff[1][3], coeff[1][2] }, 
        { coeff[2][0], coeff[2][3], coeff[2][2] }, 
    }; 
    // Matrix d3 using coeff as given in cramer's rule 
    double d3[3][3] = { 
        { coeff[0][0], coeff[0][1], coeff[0][3] }, 
        { coeff[1][0], coeff[1][1], coeff[1][3] }, 
        { coeff[2][0], coeff[2][1], coeff[2][3] }, 
    }; 
  
    // Calculating Determinant of Matrices d, d1, d2, d3 
    double D = determinantOfMatrix(d); 
    double D1 = determinantOfMatrix(d1); 
    double D2 = determinantOfMatrix(d2); 
    double D3 = determinantOfMatrix(d3); 
  
    // Case 1 
    if (D != 0) { 
        // Coeff have a unique solution. Apply Cramer's Rule 
        double x = D1 / D; 
        double y = D2 / D; 
        double z = D3 / D; // calculating z using cramer's rule
        
        sprintf(string_to_print, "\nOn solving, we get \nx = %.2lf\t y = %.2lf\t z = %.2lf\n ",x, y, z);
        print_to_label(solution_output_label, string_to_print, 0);
        g_print("Value of x is : %lf\n", x); 
        g_print("Value of y is : %lf\n", y); 
        g_print("Value of z is : %lf\n", z); 
    }
    // Case 2 
    else { 
        if (D1 == 0 && D2 == 0 && D3 == 0)
        {
            g_print("Infinite solutions\n"); 
            print_to_label(solution_output_label, "\n\nThis system has infinitely many solutions", 0);
        }
        else if (D1 != 0 || D2 != 0 || D3 != 0)
        {
            g_print("No solutions\n");
            print_to_label(solution_output_label, "\n\nThis system has no solution", 0);
        }
    } 
} 

void solve_3_equations()
{ 
    float a1,b1,a2,b2,a3,b3,c1,c2,c3;
    int var1=0,var2=0,var3=0;

    char equation1[100];
    char equation2[100];
    char equation3[100];
    // A temporary place for holding the string to be shown on the GTK window. 
    char string_to_print[150];

    strcpy(equation1, gtk_entry_get_text(GTK_ENTRY(equation_textbox1)));
    strcpy(equation2, gtk_entry_get_text(GTK_ENTRY(equation_textbox2)));
    strcpy(equation3, gtk_entry_get_text(GTK_ENTRY(equation_textbox3)));

    // Reset all the variables to their initial value;
    reset_all();
    parse_input(equation1);

    con1=con;
    con=0;
    for(int i=0;i<26;i++)
    {
        coefficient_arr1[i][1]=coefficient_arr[i][1];
        coefficient_arr[i][1]=0;
    }
    
    //Output the given equation 1, Print the co-efficients seperately and then the constant seperately.
    g_print("\nGiven equation 1:  ");
    // Here we clear the exixting text in label
    print_to_label(solution_output_label,"\nGiven equation 1:  ",1);
    
    for(int i=0;i<26;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(coefficient_arr1[i][j]!=0)
            {
                sprintf(string_to_print, "%+.2f%c^%d \0",coefficient_arr1[i][j],i+'a',j);
                g_print(string_to_print);
                print_to_label(solution_output_label,string_to_print,0);

            }
        }
    }

    // Print the constant and append a zero to the end.
    sprintf(string_to_print, "%+.2f = 0\n", con1);
    g_print(string_to_print);
    print_to_label(solution_output_label,string_to_print,0);

    parse_input(equation2);
    con2=con;
    con=0;
    for(int i=0;i<26;i++)
    {
        coefficient_arr2[i][1]=coefficient_arr[i][1];
        coefficient_arr[i][1]=0;
    }

    //Output the given equation 1, Print the co-efficients seperately and then the constant seperately.
    g_print("\nGiven equation 2:  ");
    print_to_label(solution_output_label,"\nGiven equation 2:  ",0);

    for(int i=0;i<26;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(coefficient_arr2[i][j]!=0)
            {
                // g_print("\n%f %c ^ %d ",coefficient_arr2[i][j],i+'a',j);
                sprintf(string_to_print, "%+.2f%c^%d \0",coefficient_arr2[i][j],i+'a',j);
                g_print(string_to_print);
                print_to_label(solution_output_label,string_to_print,0);

            }
        }
    }

    // Print the constant and append a zero to the end.
    sprintf(string_to_print, "%+.2f = 0\n", con2);
    g_print(string_to_print);
    print_to_label(solution_output_label,string_to_print,0);


    parse_input(equation3);
    con3=con;
    con=0;
    for(int i=0;i<26;i++)
    {
        coefficient_arr3[i][1]=coefficient_arr[i][1];
        coefficient_arr[i][1]=0;
    }

    //Output the given equation 1, Print the co-efficients seperately and then the constant seperately.
    g_print("\nGiven equation 3:  ");
    print_to_label(solution_output_label,"\nGiven equation 3:  ",0);

    for(int i=0;i<26;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(coefficient_arr3[i][j]!=0)
            {
                sprintf(string_to_print, "%+.2f%c^%d \0",coefficient_arr3[i][j],i+'a',j);
                g_print(string_to_print);
                print_to_label(solution_output_label,string_to_print,0);
            }
        }
    }

    // Print the constant and append a zero to the end.
    sprintf(string_to_print, "%+.2f = 0\n", con3);
    g_print(string_to_print);
    print_to_label(solution_output_label,string_to_print,0);

    for(int i=0,j=0;i<26;i++)
    {
        if(j==0)
        {
            if(coefficient_arr1[i][1]!=0||coefficient_arr2[i][1]!=0||coefficient_arr3[i][1]!=0)
            {
                a1=coefficient_arr1[i][1];
                a2=coefficient_arr2[i][1];
                a3=coefficient_arr3[i][1];
                j=1;var1=i;
                continue ;
            }
        }
        if(j==1)
        {
             if(coefficient_arr1[i][1]!=0||coefficient_arr2[i][1]!=0||coefficient_arr3[i][1]!=0)
            {
                b1=coefficient_arr1[i][1];
                b2=coefficient_arr2[i][1];
                b3=coefficient_arr3[i][1];
                var2=i;j=2;
                continue ;
            }
        }
        if(j==2)
        {
             if(coefficient_arr1[i][1]!=0||coefficient_arr2[i][1]!=0||coefficient_arr3[i][1]!=0)
            {
                c1=coefficient_arr1[i][1];
                c2=coefficient_arr2[i][1];
                c3=coefficient_arr3[i][1];
                var3=i;j=2;
                continue ;
            }
        }
    }
    g_print("\nCo-efficients: \n%f %f %f",a1,a2,a3);
    g_print("\n %f %f %f",b1,b2,b3);
    g_print("\n %f %f %f",c1,c2,c3);
    g_print("\n%f %f %f\n",con1,con2,con3);
    double coeff[3][4] = { 
        { a1,b1,c1,-1*con1}, 
        { a2,b2,c2,-1*con2}, 
        { a3,b3,c3,-1*con3}, 
    };

    findSolution(coeff); 
} 

void compute_factors(GtkWidget *widget, GtkWidget *text)
{
    const gchar *equation;
    equation = gtk_entry_get_text(GTK_ENTRY(text));
    g_print ("\n-----\n");
    g_print(equation);
    print_to_label(factors_output_label, "", 1);

    char s[50];
    strcpy(s, equation);
    g_print("\n\nGiven input: %s\n\n", s);

    factorize(s);
    reset_all();
}

void print_to_label(GtkWidget *label, char *string, int clear_before_printing)
{
    if(clear_before_printing) 
    {
        gtk_label_set_text(GTK_LABEL(label), string);
    }
    else
    {
        char existing_output[500];
        g_print(string);
        strcpy(existing_output, gtk_label_get_text(GTK_LABEL(label)));
        gtk_label_set_text(GTK_LABEL(label), strcat(existing_output, string));
    }
}

void reset_all()
{
    /*Clearing all the global variables*/
    degree=1;
    temp=0;
    con=0;con1=0;con2=0;con3=0;
    for(int i = 0; i < 100; i++)
    {
        s_left[i] = s_right[i] = coefficient_input_arr[i] = 0;
    }

    for(int i = 0; i < 26; i++)
    {
        for(int j = 0; j < 100; j++)
        {
            coefficient_arr[i][j]=0;
            coefficient_arr1[i][j]=0;
            coefficient_arr2[i][j]=0;
            coefficient_arr3[i][j]=0;
        }
    }
}

/*
Function to get the printable representation of a complex number.
*/
char *complex_to_string(double complex number)
{
    //static as we are returning this to the calling function
    static char string[15];
    double real = creal(number);
    double imaginary = cimag(number);

    if(fabs(imaginary) < (double) 0.001)
    {
        sprintf(string, "%.2lf", real);
    }
    else if(fabs(real) < (double) 0.001)
    {
        sprintf(string, "%.2lfi", imaginary);
    }
    else
    {
        sprintf(string, "%.2lf%+.2lfi", real, imaginary);
    }

    return string;
}