/*
 * Copyright 2023-2024 Connor C. Kaufman (connor.kaufman.gh@outlook.com)
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// this file inc
#include "cla3p/linsol/dns_auto_lsolver.hpp"

// system

// 3rd

// cla3p
#include "cla3p/dense.hpp"
#include "cla3p/proxies/lapack_proxy.hpp"
#include "cla3p/error/exceptions.hpp"

#include "cla3p/checks/decomp_auto_checks.hpp"
#include "cla3p/checks/solve_checks.hpp"
#include "cla3p/checks/lapack_checks.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns { 
/*-------------------------------------------------*/
template <typename T_Matrix>
LSolverAuto<T_Matrix>::LSolverAuto()
{
}
/*-------------------------------------------------*/
template <typename T_Matrix>
LSolverAuto<T_Matrix>::LSolverAuto(uint_t n)
{
	reserve(n);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
LSolverAuto<T_Matrix>::~LSolverAuto()
{
	this->clear();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LSolverAuto<T_Matrix>::reserve(uint_t n)
{
	this->reserveBuffer(n);
	this->reserveIpiv(n);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LSolverAuto<T_Matrix>::decompose(const T_Matrix& mat)
{
	this->factor().clear();
	auto_decomp_input_check(mat);
	this->absorbInput(mat);
	fdecompose();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LSolverAuto<T_Matrix>::idecompose(T_Matrix& mat)
{
	this->factor().clear();
	auto_decomp_input_check(mat);
	this->factor() = mat.move();
	fdecompose();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LSolverAuto<T_Matrix>::solve(T_Matrix& rhs) const
{
	if(this->factor().empty()) {
		throw err::InvalidOp("Decomposition stage is not performed");
	} // empty factor

	default_solve_input_check(this->factor().ncols(), rhs);

	int_t info = 0;

	if(this->factor().prop().isGeneral()) {

		info = lapack::getrs('N', 
				this->factor().ncols(), 
				rhs.ncols(), 
				this->factor().values(), 
				this->factor().ld(), 
				this->ipiv1().data(), 
				rhs.values(), 
				rhs.ld());

	} else if(this->factor().prop().isSymmetric()) {

		info = lapack::sytrs(
				this->factor().prop().cuplo(), 
				this->factor().ncols(), 
				rhs.ncols(), 
				this->factor().values(), 
				this->factor().ld(), 
				this->ipiv1().data(), 
				rhs.values(), 
				rhs.ld());

	} else if(this->factor().prop().isHermitian()) {

		info = lapack::hetrs(
				this->factor().prop().cuplo(), 
				this->factor().ncols(), 
				rhs.ncols(), 
				this->factor().values(), 
				this->factor().ld(), 
				this->ipiv1().data(), 
				rhs.values(), 
				rhs.ld());

	} else {

		throw err::Exception("Unreachable");

	} // prop

	lapack_info_check(info);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LSolverAuto<T_Matrix>::solve(T_Vector& rhs) const
{
	LSolverBase<T_Matrix>::solve(rhs);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void LSolverAuto<T_Matrix>::fdecompose()
{
	if(this->factor().prop().isGeneral()) {

		this->ipiv1().resize(std::min(this->factor().nrows(), this->factor().ncols()));

		this->info() = lapack::getrf(
				this->factor().nrows(), 
				this->factor().ncols(), 
				this->factor().values(), 
				this->factor().ld(), 
				this->ipiv1().data());

	} else if(this->factor().prop().isSymmetric()) {

		this->ipiv1().resize(this->factor().ncols());

		this->info() = lapack::sytrf(
				this->factor().prop().cuplo(), 
				this->factor().ncols(), 
				this->factor().values(), 
				this->factor().ld(), 
				this->ipiv1().data());

	} else if(this->factor().prop().isHermitian()) {

		this->ipiv1().resize(this->factor().ncols());

		this->info() = lapack::hetrf(
				this->factor().prop().cuplo(), 
				this->factor().ncols(), 
				this->factor().values(), 
				this->factor().ld(), 
				this->ipiv1().data());

	} else {

		throw err::Exception("Unreachable");

	} // prop

	lapack_info_check(this->info());
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template class LSolverAuto<RdMatrix>;
template class LSolverAuto<RfMatrix>;
template class LSolverAuto<CdMatrix>;
template class LSolverAuto<CfMatrix>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/
