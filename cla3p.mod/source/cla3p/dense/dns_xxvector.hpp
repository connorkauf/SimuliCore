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

#ifndef CLA3P_DNS_XXVECTOR_HPP_
#define CLA3P_DNS_XXVECTOR_HPP_

#include <string>

#include "cla3p/dense/dns_xxobject.hpp"
#include "cla3p/generic/guard.hpp"
#include "cla3p/virtuals/virtual_object.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
/*-------------------------------------------------*/

namespace prm { template <typename T_Int> class PxMatrix; }
namespace dns { template <typename T_Scalar, typename T_Matrix> class XxMatrix; }

/*-------------------------------------------------*/
namespace dns {
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief The dense vector class.
 */
template <typename T_Scalar, typename T_Vector>
class XxVector : public XxObject<T_Scalar,T_Vector> {

	private:
		using T_RScalar = typename TypeTraits<T_Scalar>::real_type;
		using T_Matrix = typename TypeTraits<T_Vector>::matrix_type;

	public:

		// no copy
		XxVector(const XxVector<T_Scalar,T_Vector>&) = delete;
		XxVector<T_Scalar,T_Vector>& operator=(const XxVector<T_Scalar,T_Vector>&) = delete;

		/** 
		 * @name Constructors
		 * @{
		 */

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty vector.
		 */
		explicit XxVector();

		/**
		 * @brief The dimensional constructor.
		 *
		 * Constructs a n-sized vector with uninitialized values.
		 *
		 * @param[in] n The vector size.
		 */
		explicit XxVector(uint_t n);

		/**
		 * @brief The move constructor.
		 *
		 * Constructs a vector with the contents of `other`, `other` is destroyed.
		 */
		XxVector(XxVector<T_Scalar,T_Vector>&& other) = default;

		/**
		 * @brief Destroys the vector.
		 */
		~XxVector();

		/** @} */

		/** 
		 * @name Operators
		 * @{
		 */

		/**
		 * @brief The move assignment operator.
		 *
		 * Replaces the contents of `(*this)` with those of `other`, `other` is destroyed.
		 */
		XxVector<T_Scalar,T_Vector>& operator=(XxVector<T_Scalar,T_Vector>&& other) = default;

		/**
		 * @brief Vector entry operator.
		 * @param[in] i The index of the requested entry.
		 * @return A reference to the i-th element of `(*this)`.
		 */
		T_Scalar& operator()(uint_t i);

		/**
		 * @copydoc cla3p::dns::XxVector::operator()(uint_t i)
		 */
		const T_Scalar& operator()(uint_t i) const;

		/**
		 * @brief The value setter operator.
		 *
		 * Sets all entries of `(*this)` to a single value.
		 *
		 * @param[in] val The value to be set.
		 */
		void operator=(T_Scalar val);

		/** @} */

		/** 
		 * @name Arguments
		 * @{
		 */

		/**
		 * @brief The vector size.
		 * @return The number of entries in `(*this)`.
		 */
		uint_t size() const;

		/** @} */

		/** 
		 * @name Public Member Functions
		 * @{
		 */

		/**
		 * @brief Prints vector information.
		 * @param[in] msg Set a header identifier.
		 */
		std::string info(const std::string& msg = "") const;

		/**
		 * @brief Virtually transposes a vector.
		 */
		VirtualVector<T_Vector> transpose() const;

		/**
		 * @brief Virtually conjugate-transposes a vector.
		 */
		VirtualVector<T_Vector> ctranspose() const;

		/**
		 * @brief Virtually conjugates a vector.
		 */
		VirtualVector<T_Vector> conjugate() const;

		/**
		 * @brief Vector Euclidean norm.
		 * @return The Euclidean norm of `(*this)`.
		 */
		T_RScalar normEuc() const;

		/**
		 * @brief Permutes the entries of a vector
		 *
		 * Creates a permuted copy `P*(*this)` of `(*this)`.
		 *
		 * @param[in] P The left side permutation matrix.
		 * @return The vector `P*(*this)`.
		 *
		 * @see ipermuteLeft()
		 */
		T_Vector permuteLeft(const prm::PxMatrix<int_t>& P) const;

		/**
		 * @brief Permutes the entries of a vector in-place.
		 *
		 * Replaces `(*this)` with `P*(*this)`.
		 *
		 * @param[in] P The left side permutation matrix.
		 *
		 * @see permuteLeft()
		 */
		void ipermuteLeft(const prm::PxMatrix<int_t>& P);

		/**
		 * @brief Gets a subvector with content copy.
		 *
		 * Gets a copy of a ni-sized portion of `(*this)`, starting at ibgn.
		 *
		 * @param[in] ibgn The index that the requested part begins.
		 * @param[in] ni The size of the requested block.
		 * @return A vector with content copy of `(*this)[ibgn:ibgn+ni]`.
		 *
		 * @see rblock()
		 */
		T_Vector block(uint_t ibgn, uint_t ni) const;

		/**
		 * @brief Gets a subvector with content reference.
		 *
		 * Gets a ni-sized vector that references contents of `(*this)`, starting at ibgn.
		 *
		 * @param[in] ibgn The index that the requested part begins.
		 * @param[in] ni The size of the requested block.
		 * @return A vector with content reference to `(*this)[ibgn:ibgn+ni]`.
		 *
		 * @see block()
		 */
		T_Vector rblock(uint_t ibgn, uint_t ni);

		/**
		 * @brief Gets a guarded subvector with content reference.
		 *
		 * Gets a ni-sized guarded vector that references contents of `(*this)`, starting at ibgn.
		 *
		 * @param[in] ibgn The index that the requested part begins.
		 * @param[in] ni The size of the requested block.
		 * @return A guarded vector with content reference to `(*this)[ibgn:ibgn+ni]`.
		 *
		 * @see block(), rblock()
		 */
		Guard<T_Vector> rblock(uint_t ibgn, uint_t ni) const;

		/**
		 * @brief Sets a subvector.
		 *
		 * Copies the contents of `src` to `(*this)[ibgn:ibgn+src.size()]`.
		 *
		 * @param[in] ibgn The index that src will be placed.
		 * @param[in] src The vector to be placed.
		 */
		void setBlock(uint_t ibgn, const XxVector<T_Scalar,T_Vector>& src);

		/**
		 * @brief Converts a vector to a matrix.
		 * @return A copy of `(*this)` as matrix.
		 */
		T_Matrix matrix() const;

		/**
		 * @brief Converts a vector to a matrix.
		 * @return A matrix referencing the contents of `(*this)`.
		 */
		T_Matrix rmatrix();

		/**
		 * @brief Converts an immutable vector to a guarded matrix.
		 * @return A guarded matrix referencing the contents of `(*this)`.
		 */
		Guard<T_Matrix> rmatrix() const;

		/** @} */

		/** 
		 * @name Creators/Generators
		 * @{
		 */

		/**
		 * @brief Creates a vector.
		 *
		 * Creates a n-sized vector with uninitialized values.
		 *
		 * @param[in] n The vector size.
		 * @return The newly created vector.
		 */
		static T_Vector init(uint_t n);

		/**
		 * @brief Creates a vector with random values in (lo,hi).
		 *
		 * Creates a n-sized vector with random values.
		 *
		 * @param[in] n The vector size.
		 * @param[in] lo The smallest value of each generated element.
		 * @param[in] hi The largest value of each generated element.
		 * @return The newly created vector.
		 */
		static T_Vector random(uint_t n, T_RScalar lo = T_RScalar(0), T_RScalar hi = T_RScalar(1));

		/**
		 * @brief Creates a vector from aux data.
		 *
		 * Creates a n-sized vector from bulk data.
		 *
		 * @param[in] n The vector size.
		 * @param[in] vals The array containing the vector values.
		 * @param[in] bind Binds the data to the vector, the vector will deallocate vals on destroy using i_free().
		 * @return The newly created vector.
		 */
		static T_Vector wrap(uint_t n, T_Scalar *vals, bool bind);

		/**
		 * @brief Creates a guard from aux data.
		 *
		 * Creates a n-sized guarded vector from bulk data.
		 *
		 * @param[in] n The vector size.
		 * @param[in] vals The array containing the vector values.
		 * @return The newly created guard.
		 */
		static Guard<T_Vector> wrap(uint_t n, const T_Scalar *vals);

		/** @} */

};

/*-------------------------------------------------*/
} // namespace dns
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_XXVECTOR_HPP_
