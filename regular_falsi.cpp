#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <vector>

#define MAX_ITER 1000

using namespace std;

double poly(vector<double> &coeff, double x) 
{
    double result = 0;
    int n = coeff.size();
    for (int i = 0; i < n; i++) 
    {
        result += coeff[i] * pow(x, n-1-i);
    }
    return result;
}

double poly_prime(vector<double> &coeff, double x) 
{
    double result = 0;
    int n = coeff.size();
    for (int i = 0; i < n-1; i++) 
    {
        result += coeff[i] * (n-1-i) * pow(x, n-2-i);
    }
    return result;
}

double regula_falsi(vector<double> &coeff, double a, double b, double tol) 
{
    double x = 0;
    int n = coeff.size();
    for (int i = 0; i < MAX_ITER; i++) 
    {
        x = (a * poly(coeff, b) - b * poly(coeff, a)) / (poly(coeff, b) - poly(coeff, a));
        if (fabs(poly(coeff, x)) < tol) 
        {
            return x;
        }
        if (poly(coeff, a) * poly(coeff, x) < 0) 
        {
            b = x;
        }
        else 
        {
            a = x;
        }
    }
    return x;
}

int main()
{
    int n = 0;
    cout << "Enter the degree of the polynomial: ";
    cin >> n;
    vector<double> coeff(n+1);
    for (int i = 0; i <= n; i++)
    {
        cout << "Enter the coefficient of x^" << n - i << ": ";
        cin >> coeff[i];
    }
    double a = 0, b = 0;   
    double x = 0;
    // cin >> x;
    // cout << "the polynomial value is: " << poly(coeff, x) << endl;
    
    cout << "Enter the lower bound: ";
    cin >> a;
    cout << "Enter the upper bound: ";
    cin >> b;
    double tolerance = 0;
    cout << "Enter the error tolerance: ";
    cin >> tolerance;
    int iter = 0;
    cout << "the root of the polynomial is: " << regula_falsi(coeff, a, b, tolerance) << endl;
    return 0;
}