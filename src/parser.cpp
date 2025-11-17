#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cctype>
#include "../include/computor.hpp"

bool read_input(int argc, char **argv, std::string &input)
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

void remove_spaces(std::string &s)
{
	std::string out;
	for (char c : s)
		if (!isspace(c)) out += c;
	s = out;
}

// Hilfsfunktion: Term "a*X^p" extrahieren
static Term parse_term(const std::string &s)
{
	Term t;
	size_t pos = s.find("*X^");
	std::string coef = s.substr(0, pos);
	std::string exp = s.substr(pos+3);
	t.coefficient = std::atof(coef.c_str());
	t.exponent = std::atoi(exp.c_str());
	return t;
}

bool parse_equation(const std::string &input, Equation &eq)
{
	std::string s = input;
	remove_spaces(s);
	size_t eqpos = s.find('=');
	std::string lhs = s.substr(0, eqpos);
	std::string rhs = s.substr(eqpos+1);

	std::vector<Term> terms;

	auto add_terms = [&](const std::string &side, int sign){
		std::stringstream ss(side);
		std::string item;
		size_t start = 0;
		for (size_t i=0;i<=side.size();++i){
			if (i==side.size() || side[i]=='+' || side[i]=='-'){
				if (i>start){
					Term t = parse_term(side.substr(start, i-start));
					t.coefficient *= sign;
					terms.push_back(t);
				}
				start = i;
			}
		}
	};

	add_terms(lhs, 1);
	add_terms(rhs, -1);

	eq.terms = terms;
	return true;
}
