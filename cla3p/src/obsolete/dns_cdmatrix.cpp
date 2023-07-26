// this file inc
#include "dns_cdmatrix.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
using ThisDataType = complex_t;
using ThisRealType = real_t;
using ThisObjectType = GenericObject<ThisDataType,ThisRealType>;
using ThisGuardType = Guard<CdMatrix>;
/*-------------------------------------------------*/
static Property propcheck(const Property& prop)
{
	return prop;
}
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
#define RxMatrix RdMatrix
#define XxMatrix CdMatrix
#define XxMGuard CdMGuard
#define UniversalConstructor() UniversalMetaTypes(ObjectType::DNS_MATRIX, DataType::COMPLEX, PrecisionType::DOUBLE)
/*-------------------------------------------------*/
#include "dns_xxmatrix_source.hpp"
#include "dns_cxmatrix_source.hpp"
#include "dns_flmatrix_source.hpp"
/*-------------------------------------------------*/
#undef RxMatrix
#undef XxMatrix
#undef XxMGuard
#undef UniversalConstructor