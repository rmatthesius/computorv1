#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include "../include/computor.hpp"

bool ft_readInput(int argc, char **argv, std::string &input)
{
	// check if argc has the right amount
	if (argc > 2) {
		std::cout << "wrong number of argments. Please enter like this example: ./computor \"5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0\"" << std::endl;
		exit(1);
	}

	// putting the EQ into input
	if (argc == 2) {
		input = argv[1];
	}

	// checks if imput is empty if so I offer you a chance to get it right this time
	if (input.empty()) {
		std::cout << "Please enter an equation: ";
		std::getline(std::cin, input);
	}
	return !input.empty();
}

void ft_removeSpaces(std::string &s)
{
	std::string out;
	for (char c : s)
		if (!isspace(c)) out += c;
	s = out;
}

static Term ft_parseTerm(const std::string &s)
{
	Term t;

	size_t pos = s.find("*X^");

	if (pos == std::string::npos) {
		t.coefficient = std::atof(s.c_str());
		t.exponent = 0;
		return t;
	}

	std::string coef = s.substr(0, pos);
	std::string exp  = s.substr(pos + 3);

	t.coefficient = std::atof(coef.c_str());
	t.exponent = std::atoi(exp.c_str());
	return t;
}


bool ft_parseEquation(const std::string &input, Equation &eq)
{
	std::string s = input;
	// cutting out the spaces for easier parsing#
	// std::cout << "Input before removing spaces: " << s << "\n";
	ft_removeSpaces(s);
	// std::cout << "Input after removing spaces: " << s << "\n";

	// searching for the equal sign and splitting the equation into LHS and RHS
	size_t eqpos = s.find('=');
	std::string lhs = s.substr(0, eqpos);
	std::string rhs = s.substr(eqpos+1);

	// std::cout << "LHS: " << lhs << "\n";
	// std::cout << "RHS: " << rhs << "\n";

	std::vector<Term> terms;

	// lambda function to parse terms from the right side to the left side
	// lambda is a function that captures variables from the surrounding scope with the [&] syntax
	// this function only exists within the scope of ft_parseEquation and is anonymous to other functions
	auto ft_addTerms = [&](const std::string &side, int sign){
		std::stringstream ss(side);
		std::string item;
		size_t start = 0;

		// looping through the side to find either + or - signs to split the terms
		for (size_t i=0;i<=side.size();++i){
			if (i==side.size() || side[i]=='+' || side[i]=='-'){
				
				// start is marking the begining of the term
				if (i>start){
					Term t = ft_parseTerm(side.substr(start, i-start));
					// adjusting the sign of the term based on which side of the equation it is RHS terms get negative sign
					t.coefficient *= sign;
					// std::cout << "Parsed term: coef=" << t.coefficient << ", exp=" << t.exponent << "\n";
					terms.push_back(t);
				}
				start = i;
			}
		}
	};

	// lhs terms are keeping their sign, rhs terms are negated
	ft_addTerms(lhs, 1);
	ft_addTerms(rhs, -1);

	eq.terms = terms;
	return true;
}
