#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include "../include/computor.hpp"

bool ft_readInput(int argc, char **argv, std::string &input)
{
	if (argc >= 2) {
		for (int i = 1; i < argc; ++i) {
			input += argv[i];
			if (i < argc - 1) input += " ";
		}
	}
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
	ft_removeSpaces(s);
	size_t eqpos = s.find('=');
	std::string lhs = s.substr(0, eqpos);
	std::string rhs = s.substr(eqpos+1);

	std::vector<Term> terms;

	auto ft_addTerms = [&](const std::string &side, int sign){
		// std::cout << "inside ft_addTerms\n";
		std::stringstream ss(side);
		std::string item;
		size_t start = 0;
		for (size_t i=0;i<=side.size();++i){
			if (i==side.size() || side[i]=='+' || side[i]=='-'){
				if (i>start){
					Term t = ft_parseTerm(side.substr(start, i-start));
					t.coefficient *= sign;
					terms.push_back(t);
				}
				start = i;
			}
		}
	};

	// std::cout << "after ft_addTerms\n";

	ft_addTerms(lhs, 1);
	ft_addTerms(rhs, -1);

	// std::cout << "after adding the terms\n";
	eq.terms = terms;
	return true;
}
