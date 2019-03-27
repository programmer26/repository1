#include <iostream>
#include <stdio.h>

using namespace std;

double sqrt(double S);
int abs(double S);
double power(double S, int n);
double factorial(double S);

int n, i=1;
double S, a, b;

int main()
{
	printf("%f", (2+sqrt(factorial(power(abs(-32), 6)))));
	return 0;
}

double sqrt(double S)
{
	n = 15;
	a = 60;
	while(i<=n)
	{
	    b = (a + S/a)/2;
        a = (b + S/b)/2;
	    i++;
	}
	return a;
}
int abs(double S)
{
	if(S<0) return -S;
	else if(S>=0) return S;
}
double power(double S, int n)
{
	a = S;
	while(i<n)
	{
		a *= S;
		i++;
	}
	return a;
}
double factorial(double S)
{
	double factorial=1;
	while(i<=S)
	{
		factorial *= i;
		i++;
	}
	return factorial;
}