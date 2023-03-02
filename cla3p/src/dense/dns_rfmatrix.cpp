// this file inc
#include "dns_rfmatrix.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
using ThisDataType = real4_t;
using ThisRealType = real4_t;
using ThisObjectType = GenericObject<ThisDataType,ThisRealType>;
using ThisGuardType = Guard<RfMatrix>;
/*-------------------------------------------------*/
static Property propcheck(const Property& prop)
{
	return (prop.isHermitian() ? Property(prop_t::SYMMETRIC,prop.uplo()) : prop);
}
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
#define XxMatrix RfMatrix
#define XxMGuard RfMGuard
#define UniversalConstructor() UniversalMetaTypes(ObjectType::DNS_MATRIX, DataType::REAL, PrecisionType::SINGLE)
/*-------------------------------------------------*/
#include "dns_xxmatrix_source.hpp"
#include "dns_flmatrix_source.hpp"
/*-------------------------------------------------*/
#undef XxMatrix
#undef XxMGuard
#undef UniversalConstructor