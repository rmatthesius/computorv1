#include <iostream>
#include <map>
#include <cmath>
#include "../include/computor.hpp"

void ft_reduceEquation(Equation &eq)
{
	// Accumulator map: key = exponent, value = summed coefficient
	// Using a map makes it easy to gather all coefficients for the same exponent
	std::map<int,double> acc;

	// Sum all coefficients for each exponent into the accumulator.
	// I use a const reference to avoid copying each Term.
	for (const Term &t : eq.terms)
		acc[t.exponent] += t.coefficient;

	// Clear the original term list so I can replace it with the reduced form.
	eq.terms.clear();

	// Iterate the map in reverse order so that higher exponents are pushed
	// first into `eq.terms` (common for displaying polynomials highest-to-lowest).
	for (std::map<int,double>::reverse_iterator it = acc.rbegin(); it != acc.rend(); ++it) {
		// it->first  -> exponent (int)
		// it->second -> summed coefficient (double)

		// Use a small epsilon to ignore numerical noise from floating-point
		// arithmetic. Values with absolute magnitude <= epsilon are treated
		// as zero and therefore omitted from the reduced form.
		if (fabs(it->second) > 1e-12)
			eq.terms.push_back(Term{it->second, it->first});
	}
}

void ft_printReducedForm(const Equation &eq)
{
	// Print the reduced form header
	std::cout << "Reduced form: ";
	// If there are no terms, the reduced form is simply 0 = 0
	if (eq.terms.empty()) { std::cout << "0 = 0\n"; return; }

	// Iterate over all terms (already ordered highest-to-lowest exponent)
	// and print them with correct sign formatting.
	for (size_t i = 0; i < eq.terms.size(); ++i) {
		// Use a const reference to avoid copying each Term
		const Term &t = eq.terms[i];

		// For the first term: print a leading '-' if negative, otherwise
		// do not print a '+' sign. For subsequent terms print ' + ' or ' - '
		// depending on the sign of the coefficient.
		if (i > 0)
			std::cout << (t.coefficient >= 0 ? " + " : " - ");
		else if (t.coefficient < 0)
			std::cout << "-";

		// Print the absolute value of the coefficient so the sign is not
		// duplicated, then the variable part ` * X^exponent`.
		std::cout << fabs(t.coefficient) << " * X^" << t.exponent;
	}

	// Finish the equation display
	std::cout << " = 0\n";
}
