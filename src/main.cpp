#include <iostream>
#include "../include/computor.hpp"

int main(int argc, char **argv)
{
	std::string input;
	Equation eq;

	if (!ft_readInput(argc, argv, input))
		return 1;

	if (!ft_parseEquation(input, eq))
		return 1;

	ft_reduceEquation(eq);
	ft_printReducedForm(eq);
	ft_solveEquation(eq);

	return 0;
}
