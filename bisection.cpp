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
    for (int i = 0; i < n; i++) {
        result += coeff[i] * pow(x, n-1-i);
    }
    return result;
}

double bisection_method(double a, double b, double tolerance, vector<double> &coeff, int iter) 
{
    double c = (a + b) / 2;
    double fa = poly(coeff, a);
    double fb = poly(coeff, b);
    double fc = poly(coeff, c);
    if (abs(fc) < tolerance || iter > MAX_ITER) 
    {
        cout << iter << endl;
        return c;
    }
    if (fa * fc < 0) {
        return bisection_method(a, c, tolerance, coeff, iter + 1);
    } else {
        return bisection_method(c, b, tolerance, coeff, iter + 1);
    }
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
    cout << "the root of the polynomial is: " << bisection_method(a, b, tolerance, coeff, iter) << endl;
    return 0;
}