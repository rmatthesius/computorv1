#ifndef COMPUTOR_HPP
#define COMPUTOR_HPP

#include <vector>
#include <string>

struct Term {
	double coefficient;
	int exponent;
};

struct Equation {
	std::vector<Term> terms; // alles nach links reduziert, rhs immer 0
};

// Parser & Utils
bool read_input(int argc, char **argv, std::string &input);
void remove_spaces(std::string &s);
bool parse_equation(const std::string &input, Equation &eq);

// Reducer
void reduce_equation(Equation &eq);
void print_reduced_form(const Equation &eq);

// Solver
void solve_equation(const Equation &eq);

#endif
