# computorv1

A simple polynomial equation solver (up to degree 2) written in C++.  
This is an implementation of the **ComputorV1** project from 42 School.

## Features

- Parses equations in the form `a * X^n + b * X^m = c * X^p + ...`
- Reduces the equation to its canonical form
- Determines the polynomial degree
- Solves linear (degree 1) and quadratic (degree 2) equations
- Supports real and complex solutions
- Handles special cases (infinite solutions, no solution, degree > 2)
- Supports negative, fractional and zero coefficients

## Usage

```
make
./computor "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
```
Examples
Quadratic equation:
```
./computor "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
```
Output:
```
Reduced form: 4 * X^0 + 4 * X^1 - 9.3 * X^2 = 0
Polynomial degree: 2
Discriminant is strictly positive, the two solutions are:
0.905239
-0.475131
```
Linear equation:
```
./computor "5 * X^0 + 4 * X^1 = 4 * X^0"
Output:
Reduced form: 1 * X^0 + 4 * X^1 = 0
Polynomial degree: 1
The solution is:
-0.25
```
See testEQs.txt for more test cases.
```
Building
make          # Compile
make re       # Rebuild
make fclean   # Clean everything
Project Structure
computorv1/
├── Makefile
├── testEQs.txt
├── include/
│   └── computor.hpp
└── src/
    ├── main.cpp
    ├── parser.cpp
    ├── reducer.cpp
    └── solver.cpp
```
Requirements

- C++11 compatible compiler
- make
