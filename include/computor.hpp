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
bool ft_readInput(int argc, char **argv, std::string &input);
void ft_removeSpaces(std::string &s);
bool ft_parseEquation(const std::string &input, Equation &eq);

// Reducer
void ft_reduceEquation(Equation &eq);
void ft_printReducedForm(const Equation &eq);

// Solver
void ft_solveEquation(const Equation &eq);

#endif
