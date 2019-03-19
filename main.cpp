#include <iostream>
#include <stdio.h>

using namespace std;

double S;
int n;

double function(double S, int n);

int main()
{
   S = 125348;
   n = 5;
   printf("%f", function(S, n));
}
double function(double S, int n)
{
    int i = 1;
    double a, b;
    a = 60000;
    for(;i<=n;i++)
    {
        b = (a + S/a)/2;
        a = (b + S/b)/2;
    }
    return a;
}
