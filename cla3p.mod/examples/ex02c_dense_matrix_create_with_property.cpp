#include <iostream>
#include "cla3p/dense.hpp"

int main()
{
	/*
	 * Create a properties for A, B and C
	 */

	cla3p::Property prA(cla3p::prop_t::General  , cla3p::uplo_t::F); // the default property
	cla3p::Property prB(cla3p::prop_t::Symmetric, cla3p::uplo_t::L); // symmetric lower property
	cla3p::Property prC(cla3p::prop_t::Hermitian, cla3p::uplo_t::U); // hermitian upper property

	/*
	 * Declare matrices with a property
	 */

	{
		cla3p::dns::RfMatrix A(3, 4, prA);
		cla3p::dns::RfMatrix B(3, 3, prB);
		cla3p::dns::CdMatrix C(3, 3, prC);
		std::cout << A.info("A") << B.info("B") << C.info("C") << std::endl;
	}

	/*
	 * Use the init() function to allocate space with property
	 */

	{
		cla3p::dns::RfMatrix A = cla3p::dns::RfMatrix::init(3, 4, prA);
		cla3p::dns::RfMatrix B = cla3p::dns::RfMatrix::init(3, 3, prB);
		cla3p::dns::CdMatrix C = cla3p::dns::CdMatrix::init(3, 3, prC);
	}

	return 0;
}