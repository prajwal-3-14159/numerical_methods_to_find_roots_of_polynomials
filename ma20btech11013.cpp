#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <vector>

#define MAX_ITER 10000

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

double iterative_method(double x0, double tolerance, vector<double> &coeff, int iter, bool &existance) 
{
    if (iter >= MAX_ITER){
        cout << "reached MAX iterations limit,\n";
        existance = false;
        return -1;
    }
    double fx0 = poly(coeff, x0);
    double x1 = x0 - fx0 / poly_prime(coeff, x0);
    if (abs(x1 - x0) < tolerance || iter > MAX_ITER) 
    {
        cout << "after " << iter << " interations, " << endl;
        return x1;
    }
    return iterative_method(x1, tolerance, coeff, iter + 1, existance);
}

double newton_raphson_method(double x, double tolerance, vector<double> &coeff, int iter, bool &existance) 
{
    if (iter >= MAX_ITER){
        cout << "reached MAX iterations limit,\n";
        existance = false;
        return -1;
    }
    double fx = poly(coeff, x);
    double dfx = 0;
    int n = coeff.size();
    for (int i = 0; i < n-1; i++) {
        dfx += (n-1-i) * coeff[i] * pow(x, n-2-i);
    }
    double x1 = x - fx / dfx;
    if (abs(x1 - x) < tolerance || iter > MAX_ITER) 
    {
        cout << "after " << iter << " interations, " << endl;
        return x1;
    }
    return newton_raphson_method(x1, tolerance, coeff, iter + 1, existance);
}


double regula_falsi(vector<double> &coeff, double a, double b, double tol, bool &existance) 
{
    double x = 0;
    int n = coeff.size();
    for (int i = 0; i < MAX_ITER; i++) 
    {
        x = (a * poly(coeff, b) - b * poly(coeff, a)) / (poly(coeff, b) - poly(coeff, a));
        if (fabs(poly(coeff, x)) < tol) 
        {
            cout << "after " << i+1 << " interations, " << endl;
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
    cout << "reached MAX iterations limit,\n";
    existance = false;
    return -1;
}

double bisection_method(double a, double b, double tolerance, vector<double> &coeff, int iter, bool &existance) 
{
    if (iter >= MAX_ITER){
        cout << "reached MAX iterations limit,\n";
        existance = false;
        return -1;
    }
    double c = (a + b) / 2;
    double fa = poly(coeff, a);
    double fb = poly(coeff, b);
    double fc = poly(coeff, c);
    if (abs(fc) < tolerance || iter > MAX_ITER) 
    {
        cout << "after " << iter << " interations, " << endl;
        return c;
    }
    if (fa * fc < 0) {
        return bisection_method(a, c, tolerance, coeff, iter + 1, existance);
    } else {
        return bisection_method(c, b, tolerance, coeff, iter + 1, existance);
    }
}

double secant_method(double x0, double x1, double tolerance, vector<double> &coeff, int iter, bool &existance) 
{
    if (iter >= MAX_ITER){
        cout << "reached MAX iterations limit,\n";
        existance = false;
        return -1;
    }
    double fx0 = poly(coeff, x0);
    double fx1 = poly(coeff, x1);
    double x2 = x1 - fx1 * (x1 - x0) / (fx1 - fx0);
    if (abs(fx1) < tolerance || iter > MAX_ITER) 
    {
        cout << "after " << iter << " interations, " << endl;
        return x2;
    }
    return secant_method(x1, x2, tolerance, coeff, iter + 1, existance);
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
    double delta = 0;
    int breakpoint = 0, temp = 0;
    vector<int> breakpoints;
    double root = 0;
    int choice = 0;
    bool existance = true;

    cout << "enter the method\n";
    cout << "1 -> bisection\n2 -> Newton Raphson\n3 -> Secant\n";
    cout << "4 -> iterative\n5 -> Regula Falsi\n -1 -> exit\n";
    cout << "Enter the choice of method: ";
    cin >> choice;
    while (choice != -1)
    {

        switch (choice)
        {
        case -1:
            return 0;
        
        case 1:
            cout << "enter the upper bound: ";
            cin >> a;
            cout << "enter the lower bound: ";
            cin >> b;
            cout << "enter the tolerance: ";
            cin >> delta;
            root = bisection_method(a, b, delta, coeff, 0, existance);
            if (existance == false){
                cout << "NO real root exists for defined MAX iterations\n";
                existance = true;
                break;
            }
            cout << "the root by bisection method is: " << root << endl;
            break;
        
        case 2:
            cout << "enter the initial guess: ";
            cin >> a;
            cout << "enter the tolerance\n";
            cin >> delta;
            root = newton_raphson_method(a, delta, coeff, 0, existance);
            if (existance == false){
                cout << "NO real root exists for defined MAX iterations\n";
                existance = true;
                break;
            }
            cout << "the root by Newton Raphson method is: " << root << endl;
            break;

        case 3:
            cout << "Enter x1: ";
            cin >> a;
            cout << "Enter x2: ";
            cin >> b;
            cout << "Enter the error tolerance: ";
            cin >> delta;
            root = secant_method(a, b, delta, coeff, 0, existance);
            if (existance == false){
                cout << "NO real root exists for defined MAX iterations\n";
                existance = true;
                break;
            }
            cout << "The root by secant method is: " << root << endl;
            break;

        case 4:
            cout << "enter the initial guess: ";
            cin >> a;
            cout << "enter the tolerance\n";
            cin >> delta;
            root = iterative_method(a, delta, coeff, 0, existance);
            if (existance == false){
                cout << "NO real root exists for defined MAX iterations\n";
                existance = true;
                break;
            }
            cout << "the root by iterative method is: " << root << endl;
            break;

        case 5:
            cout << "enter the upper bound: ";
            cin >> a;
            cout << "enter the lower bound: ";
            cin >> b;
            cout << "enter the tolerance\n";
            cin >> delta;
            root = regula_falsi(coeff, a, b, delta, existance);
            if (existance == false){
                cout << "NO real root exists for defined MAX iterations\n";
                existance = true;
                break;
            }
            cout << "the root by regula falsi method is: " << root << endl;
            break;
        
        default:
            break;
        }
        cout << "enter the method\n";
        cout << "1 -> bisection\n2 -> Newton Raphson\n3 -> Secant\n";
        cout << "4 -> iterative\n5 -> Regula Falsi\n6 -> Strum sequence\n-1 -> exit\n";
        cout << "enter the next method: ";
        cin >> choice;
    }

    return 0;
}