#ifndef CLA3P_DECOMP_LU_CHECKS_HPP_
#define CLA3P_DECOMP_LU_CHECKS_HPP_

#include "cla3p/error/error.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

template <typename T>
void lu_decomp_input_check(const T& mat)
{
	bool supported_prop = (mat.prop().isGeneral() || mat.prop().isSymmetric() || mat.prop().isHermitian()); 

	if(mat.empty()) {
		throw InvalidOp("Input matrix is empty");
	} else if(!supported_prop) {
		throw InvalidOp("Matrices with property " + mat.prop().name() + " not supported for LU decomposition");
	} // valid prop

	if(mat.nrows() != mat.ncols()) {
		throw InvalidOp("Only square matrices are supported for linear decomposition");
	} // square
}

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DECOMP_LU_CHECKS_HPP_