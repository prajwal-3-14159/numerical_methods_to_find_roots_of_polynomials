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

double newton_raphson_method(double x, double tolerance, vector<double> &coeff, int iter) 
{
    double fx = poly(coeff, x);
    double dfx = 0;
    int n = coeff.size();
    for (int i = 0; i < n-1; i++) {
        dfx += (n-1-i) * coeff[i] * pow(x, n-2-i);
    }
    double x1 = x - fx / dfx;
    if (abs(x1 - x) < tolerance || iter > MAX_ITER) 
    {
        cout << iter << endl;
        return x1;
    }
    return newton_raphson_method(x1, tolerance, coeff, iter + 1);
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
    double a = 0, guess = 0;   
    double x = 0;

    
    cout << "Enter an initial guess: ";
    cin >> guess;
    double tolerance = 0;
    cout << "Enter the error tolerance: ";
    cin >> tolerance;
    int iter = 0;
    cout << "the root of the polynomial is: " << newton_raphson_method(guess, tolerance, coeff, iter) << endl;
    return 0;
}