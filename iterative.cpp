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

double iterative_method(double x0, double tolerance, vector<double> &coeff, int iter) 
{
    double fx0 = poly(coeff, x0);
    double x1 = x0 - fx0 / poly_prime(coeff, x0);
    if (abs(x1 - x0) < tolerance || iter > MAX_ITER) 
    {
        cout << iter << endl;
        return x1;
    }
    return iterative_method(x1, tolerance, coeff, iter + 1);
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
    double a = 0, x1 = 0, x2 = 0;   
    double x = 0;

    
    cout << "Enter x1: ";
    cin >> x1;
    // cout << "Enter x2: ";
    // cin >> x2;
    double tolerance = 0;
    cout << "Enter the error tolerance: ";
    cin >> tolerance;
    int iter = 0;
    cout << "the root of the polynomial is: " << iterative_method(x1, tolerance, coeff, iter) << endl;
    return 0;
}