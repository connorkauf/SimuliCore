// this file inc
#include "dns_rxvector.hpp"

// system

// 3rd

// cla3p
#include "../types/literals.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
#define RxVectorTmpl RxVector<T_Scalar>
#define RxVectorTlst template <typename T_Scalar>
/*-------------------------------------------------*/
RxVectorTlst
RxVectorTmpl::RxVector()
{
}
/*-------------------------------------------------*/
RxVectorTlst
RxVectorTmpl::RxVector(uint_t n)
	: RxVectorTmpl::XxVector(n)
{
}
/*-------------------------------------------------*/
RxVectorTlst
RxVectorTmpl::~RxVector()
{
}
/*-------------------------------------------------*/
RxVectorTlst
void RxVectorTmpl::operator=(T_Scalar val)
{
	RxVectorTmpl::XxVector::operator=(val);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
#undef RxVectorTmpl
#undef RxVectorTlst
/*-------------------------------------------------*/
template class RxVector<real_t>;
template class RxVector<real4_t>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
template<> const std::string& BasicTypeTraits<dns::RxVector<real_t>>::type_name() { return stringDenseVector(); }
template<> const std::string& BasicTypeTraits<dns::RxVector<real4_t>>::type_name() { return stringDenseVector(); }
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

