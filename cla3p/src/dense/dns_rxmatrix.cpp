// this file inc
#include "dns_rxmatrix.hpp"

// system

// 3rd

// cla3p
#include "../types/literals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
#define RxMatrixTmpl RxMatrix<T_Scalar>
#define RxMatrixTlst template <typename T_Scalar>
/*-------------------------------------------------*/
RxMatrixTlst
RxMatrixTmpl::RxMatrix()
{
}
/*-------------------------------------------------*/
RxMatrixTlst
RxMatrixTmpl::RxMatrix(uint_t nr, uint_t nc, const Property& pr)
	: RxMatrixTmpl::XxMatrix(nr, nc, pr)
{
}
/*-------------------------------------------------*/
RxMatrixTlst
RxMatrixTmpl::~RxMatrix()
{
}
/*-------------------------------------------------*/
RxMatrixTlst
void RxMatrixTmpl::operator=(T_Scalar val)
{
	RxMatrixTmpl::XxMatrix::operator=(val);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
#undef RxMatrixTmpl
#undef RxMatrixTlst
/*-------------------------------------------------*/
template class RxMatrix<real_t>;
template class RxMatrix<real4_t>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
template<> const std::string& BasicTypeTraits<dns::RxMatrix<real_t>>::type_name() { return stringDenseMatrix(); }
template<> const std::string& BasicTypeTraits<dns::RxMatrix<real4_t>>::type_name() { return stringDenseMatrix(); }
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

