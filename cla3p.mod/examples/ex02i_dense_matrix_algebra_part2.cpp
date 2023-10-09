#include <iostream>
#include "cla3p/dense.hpp"
#include "cla3p/operations.hpp"

int main()
{
	cla3p::dns::RdMatrix A(3,3);
	cla3p::dns::RdVector X(3);

	A = 3.;
	X = 2.;
	std::cout << "A:\n" << A;
	std::cout << "X:\n" << X;

	/*
	 * Multiply A & X using operators and the mult function respectively
	 */
	cla3p::dns::RdVector Y1 = A * X;
	std::cout << "Y1 = A * X:\n" << Y1;

	cla3p::op_t opA = cla3p::op_t::N;
	cla3p::dns::RdVector Y2 = cla3p::ops::mult(3., opA, A, X);
	std::cout << "Y2 = cla3p::ops::mult(3.,opA,A,X):\n" << Y2;

	/*
	 * Update Y1 & Y2 using operators and the mult function respectively
	 */
	Y1 += A * X;
	std::cout << "Y1 += A * X:\n" << Y1;

	cla3p::ops::mult(1., opA, A, X, Y2);
	std::cout << "cla3p::ops::mult(1.,opA,A,X,Y2):\n" << Y2;

	return 0;
}
