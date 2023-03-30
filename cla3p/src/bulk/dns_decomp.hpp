#ifndef CLA3P_BULK_DNS_DECOMP_HPP_
#define CLA3P_BULK_DNS_DECOMP_HPP_

#include "../types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace bulk {
namespace dns {
/*-------------------------------------------------*/

//
// (P*L)*B = B
//
void itrsm_lln(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1);

//
// D*B = B
//
int_t itrsm_lld(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1);

//
// (P*L)'*B = B
//
void itrsm_llt(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1);

//
// B*(P*L) = B or (P*L)'*B' = B'
//
void itrsm_rln(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1);

//
// B*D = B or D*B' = B'
//
int_t itrsm_rld(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1);

//
// B*(P*L)' = B or (P*L)*B' = B'
//
void itrsm_rlt(int_t n, const real_t *a, int_t lda, int_t nrhs, real_t *b, int_t ldb, const int_t *ipiv1);


/*-------------------------------------------------*/
} // namespace dns
} // namespace bulk
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_BULK_DNS_DECOMP_HPP_
