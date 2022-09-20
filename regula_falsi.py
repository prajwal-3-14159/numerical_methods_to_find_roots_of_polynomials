import sys
import time


def func_input():
    try:
        n = int(input("Enter degree of the polynomial: "))
        coeffs = [0] * (n + 1)
        for i in range(n):
            coeffs[i] = float(input(f'Coefficient of x^{n-i}: '))
        coeffs[n] = float(input(f'Constant term: '))
        
        func = 'f(x) = '
        for i in range(len(coeffs) - 1):
            if i == 0:
                func += f'{coeffs[i]}x^{n-i} '
                continue
            if coeffs[i] > 0:
                func += f'+ {coeffs[i]}x^{n-i} '
                continue
            if coeffs[i] < 0:
                func += f'{coeffs[i]}x^{n-i} '
                continue
            if coeffs[i] == 0:
                continue
        if coeffs[-1] > 0:
            func += f'+ {coeffs[-1]} '
        elif coeffs[-1] < 0:
            func += f'{coeffs[-1]} '
        else:
            pass

        sys.stdout.write(f'Input function is {func}\n')
        return coeffs

    except ValueError:
        raise Exception("Input not a number")
    

def f(coeffs, x):
    value = 0
    deg = len(coeffs) - 1
    for i, c in enumerate(coeffs):
        value += c * pow(x, (deg - i))
    return value


def regula_falsi(coeffs, x1, x2, tolerance):

    if f(coeffs, x1) * f(coeffs, x2) > 0:
        raise Exception(f'Scalars {x1} and {x2} do not bound a root')
    
    while 1:
        mid = (x1 * f(coeffs, x2) - x2 * f(coeffs, x1)) / (f(coeffs, x2) - f(coeffs, x1))
        
        regula_falsi.iterations += 1
        if f(coeffs, x1) * f(coeffs, mid) < 0:
            x2 = mid
        else:
            x1 = mid
        
        if abs(f(coeffs, mid)) < tolerance:
            break
    
    return mid
        

if __name__ == '__main__':
    
    coefficients = func_input()
    try:
        x1 = float(input("Enter first bound: "))
        x2 = float(input("Enter second bound: "))
        tolerance = float(input("Error tolerance value: "))
        
    except ValueError:
        raise Exception(f'{a}, {b}, {tolerance} all need to be floating point numbers')
    
    regula_falsi.iterations = 0
    start = time.time()
    root = regula_falsi(coefficients, x1, x2, tolerance)
    end = time.time() - start
    sys.stdout.write(f'Approximate root of f(x) = {root}\n')
    sys.stdout.write(f'Iterations to achieve the error tolerance = {regula_falsi.iterations}\n')
    sys.stdout.write(f'Time taken for execution = {end} seconds\n')
