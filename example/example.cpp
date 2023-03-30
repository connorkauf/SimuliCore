#include <iostream>
#include <vector>

#include "cla3p/src/dense.hpp"
#include "cla3p/src/support.hpp"
#include "cla3p/src/perms.hpp"
#include "cla3p/src/operations.hpp"
#include "cla3p/src/linsol.hpp"

#if 1
#include "cla3p/src/bulk/dns.hpp"
#include "cla3p/src/bulk/dns_io.hpp"
#include "cla3p/src/bulk/dns_math.hpp"
#include "cla3p/src/bulk/dns_decomp.hpp"
#include "cla3p/src/proxies/lapack_proxy.hpp"
#include "cla3p/src/support/utils.hpp"
#include "cla3p/src/support/error_internal.hpp"
#endif
/*-------------------------------------------------*/
static void check_custom_trsm(cla3p::uplo_t uplo)
{
	cla3p::uint_t n = 100;
	cla3p::uint_t nrhs = 5;

	cla3p::Property prA(cla3p::prop_t::SYMMETRIC, uplo);

	const cla3p::dns::RdMatrix A = cla3p::dns::RdMatrix::random(prA, n, n);
	const cla3p::dns::RdMatrix B = cla3p::dns::RdMatrix::random(n, nrhs);

	cla3p::dns::RdMatrix X1 = B.copy();
	cla3p::dns::RdMatrix X2 = B.copy();
	cla3p::dns::RdMatrix X3 = B.transpose();

	std::vector<cla3p::int_t> ipiv(n);
	cla3p::dns::RdMatrix F = A.copy();
	cla3p::lapack::sytrf(prA.cuplo(), n, F.values(), F.ld(), ipiv.data());

	cla3p::bulk::dns::print(cla3p::uplo_t::F, 1, n, ipiv.data(), 1);

	cla3p::lapack::sytrs(prA.cuplo(), n, nrhs, F.values(), F.ld(), ipiv.data(), X1.values(), X1.ld());

	if(prA.isLower()) {
		cla3p::bulk::dns::itrsm_lln(n, F.values(), F.ld(), nrhs, X2.values(), X2.ld(), ipiv.data());
		cla3p::bulk::dns::itrsm_lld(n, F.values(), F.ld(), nrhs, X2.values(), X2.ld(), ipiv.data());
		cla3p::bulk::dns::itrsm_llt(n, F.values(), F.ld(), nrhs, X2.values(), X2.ld(), ipiv.data());

		cla3p::bulk::dns::itrsm_rlt(n, F.values(), F.ld(), nrhs, X3.values(), X3.ld(), ipiv.data());
		cla3p::bulk::dns::itrsm_rld(n, F.values(), F.ld(), nrhs, X3.values(), X3.ld(), ipiv.data());
		cla3p::bulk::dns::itrsm_rln(n, F.values(), F.ld(), nrhs, X3.values(), X3.ld(), ipiv.data());
	}

	if(prA.isUpper()) {
		cla3p::bulk::dns::itrsm_lun(n, F.values(), F.ld(), nrhs, X2.values(), X2.ld(), ipiv.data());
		cla3p::bulk::dns::itrsm_lud(n, F.values(), F.ld(), nrhs, X2.values(), X2.ld(), ipiv.data());
		cla3p::bulk::dns::itrsm_lut(n, F.values(), F.ld(), nrhs, X2.values(), X2.ld(), ipiv.data());

		cla3p::bulk::dns::itrsm_rut(n, F.values(), F.ld(), nrhs, X3.values(), X3.ld(), ipiv.data());
		cla3p::bulk::dns::itrsm_rud(n, F.values(), F.ld(), nrhs, X3.values(), X3.ld(), ipiv.data());
		cla3p::bulk::dns::itrsm_run(n, F.values(), F.ld(), nrhs, X3.values(), X3.ld(), ipiv.data());
	}

	std::cout << (B - A * X1).normInf() / B.normInf() << std::endl;
	std::cout << (B - A * X2).normInf() / B.normInf() << std::endl;
	std::cout << (B - A * X3.transpose()).normInf() / B.normInf() << std::endl;
}
/*-------------------------------------------------*/
template <typename T>
static void linsol_test()
{
	cla3p::uint_t n = 10;
	cla3p::uint_t nrhs = 5;
	//cla3p::Property prA(cla3p::prop_t::HERMITIAN, cla3p::uplo_t::L);
	cla3p::Property prA(cla3p::prop_t::HERMITIAN, cla3p::uplo_t::U);
	//cla3p::Property prA(cla3p::prop_t::SYMMETRIC, cla3p::uplo_t::L);
	//cla3p::Property prA(cla3p::prop_t::SYMMETRIC, cla3p::uplo_t::U);
	//cla3p::Property prA(cla3p::prop_t::GENERAL, cla3p::uplo_t::F);


	T A = T::random(prA, n, n);
	T B = T::random(n, nrhs);

	//for(cla3p::uint_t i = 0; i < n; i++) A(i,i) *= 1000;

	B.scale(1.e-10);

	//std::cout << A << B;

	cla3p::dns::LSolverAuto<T> def;
	cla3p::dns::LSolverLLt<T> llt;
	cla3p::dns::LSolverLDLt<T> ldlt;
	cla3p::dns::LSolverLU<T> lu;
	cla3p::dns::LSolverCompleteLU<T> clu;

	cla3p::dns::LSolverBase<T>& solver = clu;

	T X = B.copy();

	solver.reserve(n);
	solver.decompose(A);
	solver.solve(X);

	std::cout << (B - A * X).normInf() / B.normInf() << std::endl;
}
/*-------------------------------------------------*/

int main()
{
	check_custom_trsm(cla3p::uplo_t::L);
	check_custom_trsm(cla3p::uplo_t::U);
	return 0;

	linsol_test<cla3p::dns::RdMatrix>();
	linsol_test<cla3p::dns::RfMatrix>();
	linsol_test<cla3p::dns::CdMatrix>();
	linsol_test<cla3p::dns::CfMatrix>();

	return 0;
}
/*-------------------------------------------------*/
