#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	/* 
	 * (4x3) single precision general complex matrix with random values in [0,1]
	 */

	cla3p::dns::CfMatrix A = cla3p::dns::CfMatrix::random(4,3);
	std::cout << A.info() << A;

	/* 
	 * (4x4) double precision symmetric lower real matrix with random values in [0,1]
	 */

	cla3p::Property prB(cla3p::prop_t::Symmetric, cla3p::uplo_t::L);
	cla3p::dns::RdMatrix B = cla3p::dns::RdMatrix::random(4, 4, prB);
	std::cout << B.info() << B;

	return 0;
}