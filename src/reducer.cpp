#include <iostream>
#include <map>
#include <cmath>
#include "../include/computor.hpp"

void ft_reduceEquation(Equation &eq)
{
	std::map<int,double> acc;
	for (Term t : eq.terms)
		acc[t.exponent] += t.coefficient;

	eq.terms.clear();
	for (std::map<int,double>::reverse_iterator it = acc.rbegin(); it != acc.rend(); ++it){
		if (fabs(it->second) > 1e-12) // nur Nicht-Null-Terme
			eq.terms.push_back(Term{it->second, it->first});
	}
}

void ft_printReducedForm(const Equation &eq)
{
	std::cout << "Reduced form: ";
	if (eq.terms.empty()) { std::cout << "0 = 0\n"; return; }

	for (size_t i=0;i<eq.terms.size();++i){
		Term t = eq.terms[i];
		if (i>0) std::cout << (t.coefficient>=0?" + ":" - ");
		else if (t.coefficient<0) std::cout << "-";
		std::cout << fabs(t.coefficient) << " * X^" << t.exponent;
	}
	std::cout << " = 0\n";
}
