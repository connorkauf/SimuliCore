#ifndef CLA3P_DENSE2_HPP_
#define CLA3P_DENSE2_HPP_

#include "dense/dns_rxvector.hpp"
#include "dense/dns_cxvector.hpp"

namespace cla3p {
namespace dns {

/**
 * @ingroup dense_vectors
 * @brief Double precision real vector.
 */
using RdVector2 = RxVector<real_t>;

/**
 * @ingroup dense_vectors
 * @brief Single precision real vector.
 */
using RfVector2 = RxVector<real4_t>;

/**
 * @ingroup dense_vectors
 * @brief Double precision complex vector.
 */
using CdVector2 = CxVector<complex_t,real_t>;

/**
 * @ingroup dense_vectors
 * @brief Single precision complex vector.
 */
using CfVector2 = CxVector<complex8_t,real4_t>;

} // namespace dns
} // namespace cla3p

#endif // CLA3P_DENSE2_HPP_
