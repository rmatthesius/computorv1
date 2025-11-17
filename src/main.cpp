#include <iostream>
#include "../include/computor.hpp"

int main(int argc, char **argv)
{
	std::string input;
	Equation eq;

	if (!read_input(argc, argv, input))
		return 1;

	if (!parse_equation(input, eq))
		return 1;

	reduce_equation(eq);
	print_reduced_form(eq);
	solve_equation(eq);

	return 0;
}
