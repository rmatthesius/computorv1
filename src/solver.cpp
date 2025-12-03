#include <iostream>
#include <cmath>
#include "../include/computor.hpp"

// searching through the terms to find the highest exponent and returns it
int ft_getDegree(const Equation &eq)
{
	int deg = 0;
	for (Term t : eq.terms)
		if (t.exponent > deg) deg = t.exponent;
	return deg;
}

void ft_solveEquation(const Equation &eq)
{
	int deg = ft_getDegree(eq);
	std::cout << "Polynomial degree: " << deg << std::endl;

	if (deg > 2) {
		std::cout << "The polynomial degree is strictly greater than 2, I can't solve.\n";
		return;
	}

	// a, b, c for ax^2 + bx + c = 0
	// the equation is already reduced, so missing terms have coefficient 0
	double a=0,b=0,c=0;
	for (Term t : eq.terms){
		if (t.exponent==2) a=t.coefficient;
		else if (t.exponent==1) b=t.coefficient;
		else if (t.exponent==0) c=t.coefficient;
	}

	// Linear equation
	// c = 0  =>  any real number is a solution
	// fabs and 1e-12 to avoid floating point precision issues
	if (deg==0){
		if (fabs(c)<1e-12) std::cout<<"Any real number is a solution.\n";
		else std::cout<<"No solution.\n";
		return;
	}

	// bx + c = 0  =>  x = -c/b
if (deg == 1) {
	// check for b == 0 to avoid division by zero
    if (fabs(b) < 1e-12) {
        std::cout << "Numerical instability: coefficient b is zero.\n";
    } else {
        std::cout << "The solution is:\n" << -c / b << std::endl;
    }
    return;
}

	// Quadratische Gleichung
	// ax^2 + bx + c = 0
	// calculate discriminant to know how to solve
	double disc = b*b - 4*a*c;
	if (disc>0){
		std::cout<<"Discriminant is strictly positive, the two solutions are:\n";
		double r = sqrt(disc);
		std::cout << (-b - r)/(2*a) << "\n" << (-b + r)/(2*a) << std::endl;
	} else if (fabs(disc)<1e-12){
		std::cout<<"Discriminant is zero, the solution is:\n";
		std::cout << -b/(2*a) << std::endl;
	} else {
		std::cout<<"Discriminant is strictly negative, the two complex solutions are:\n";
		double real = -b/(2*a);
		double imag = sqrt(-disc)/(2*a);
		std::cout << real << " + " << imag << "i\n" << real << " - " << imag << "i\n";
	}
}
