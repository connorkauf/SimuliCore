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

#ifndef CLA3P_PXMATRIX_HPP_
#define CLA3P_PXMATRIX_HPP_

/** 
 * @file
 * The permutation matrix definitions.
 */

#include <string>
#include <ostream>

#include "cla3p/types.hpp"
#include "cla3p/types/literals.hpp"
#include "cla3p/generic/array2d.hpp"
#include "cla3p/generic/guard.hpp"
#include "cla3p/generic/type_traits.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace prm {
/*-------------------------------------------------*/

/**
 * @ingroup module_index_matrices_perm
 * @nosubgrouping
 * @brief The permutation matrix object.
 *
 * Permutation matrices are represented by an array of (unsigned) integers. @n
 * Their purpose is to rearrange indices using a predefined mapping. @n
 * So an n-sized PermMatrix is a 1D entity and its individual values lie in [0, n-1] (0-based indexing).
 */
template <typename T_Int>
class PxMatrix : public Array2D<T_Int> {

	public:

		// no copy
		PxMatrix(const PxMatrix<T_Int>&) = delete;
		PxMatrix& operator=(const PxMatrix<T_Int>&) = delete;

		/** 
		 * @name Constructors
		 * @{
		 */

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty permutation matrix.
		 */
		explicit PxMatrix();

		/**
		 * @brief The dimensional constructor.
		 *
		 * Constructs an n-sized permutation matrix with uninitialized values.
		 *
		 * @param[in] n The permutation matrix size.
		 */
		explicit PxMatrix(uint_t n);

		/**
		 * @brief The move constructor.
		 *
		 * Constructs a permutation matrix with the contents of other, other is destroyed.
		 */
		PxMatrix(PxMatrix<T_Int>&& other) = default;

		/**
		 * @brief Destroys the permutation matrix.
		 */
		~PxMatrix();

		/** @} */

		/** 
		 * @name Operators
		 * @{
		 */

		/**
		 * @brief The move assignment operator.
		 *
		 * Replaces the contents with those of other, other is destroyed.
		 */
		PxMatrix<T_Int>& operator=(PxMatrix<T_Int>&& other) = default;

		/**
		 * @brief Permutation matrix entry operator.
		 * @param[in] i The number of the requested index.
		 * @return A reference to the i-th element of the permutation.
		 */
		T_Int& operator()(uint_t i);

		/**
		 * @brief Permutation matrix entry operator.
		 * @param[in] i The number of the requested index.
		 * @return A reference to the i-th element of the permutation.
		 */
		const T_Int& operator()(uint_t i) const;

		/**
		 * @brief The value setter operator.
		 *
		 * Sets all entries of the permutation matrix to a single value.@n
		 *
		 * @param[in] val The value to be set.
		 */
		void operator=(T_Int val);

		/** @} */

		/** 
		 * @name Arguments
		 * @{
		 */

		/**
		 * @brief The permutation size.
		 * @return The number of permutation size.
		 */
		uint_t size() const;

		/** @} */

		/** 
		 * @name Public Member Functions
		 * @{
		 */

		/**
		 * @brief Prints permutation matrix information to a string.
		 * @param[in] msg Set a header identifier.
		 * @return A string containing the permutation matrix information
		 */
		std::string info(const std::string& msg = "") const;

		/**
		 * @brief Copies the permutation matrix.
		 * @return A deep copy of the permutation matrix.
		 */
		PxMatrix<T_Int> copy() const;

		/**
		 * @brief Copies the permutation matrix.
		 * @return A shallow copy of the permutation matrix.
		 */
		PxMatrix<T_Int> rcopy();

		/**
		 * @brief Copies the permutation matrix.
		 * @return A shallow copy of the permutation matrix.
		 */
		Guard<PxMatrix<T_Int>> rcopy() const;

		/**
		 * @brief Moves the permutation matrix.
		 * @return A shallow copy of the permutation matrix, original matrix is destroyed.
		 */
		PxMatrix<T_Int> move();

		/**
		 * @brief The inverse permutation matrix.
		 * @return The inverse (transpose) of the permutation matrix.
		 */
		PxMatrix<T_Int> inverse() const;

		/**
		 * @brief Permutes a permutation matrix.
		 *
		 * @param[in] P The left side permutation matrix.
		 * @return The permutated permutation matrix (P * (*this)).
		 */
		PxMatrix<T_Int> permuteLeft(const PxMatrix<T_Int>& P) const;

		/**
		 * @brief Permutes a permutation matrix in-place.
		 *
		 * @param[in] P The left side permutation matrix.
		 */
		void ipermuteLeft(const PxMatrix<T_Int>& P);

		/** @} */

		/** 
		 * @name Creators/Generators
		 * @{
		 */

		/**
		 * @brief Creates a permutation matrix.
		 *
		 * Creates an n-dimensional permutation matrix with uninitialized values.
		 *
		 * @param[in] n The permutation matrix size.
		 * @return The newly created permutation matrix.
		 */
		static PxMatrix init(uint_t n);

		/**
		 * @brief Creates an identity permutation matrix
		 *
		 * Creates an n-sized permutation matrix with P(i) = i.
		 *
		 * @param[in] n The permutation matrix size.
		 * @return The newly created permutation matrix.
		 */
		static PxMatrix identity(uint_t n);

		/**
		 * @brief Creates a random permutation matrix
		 *
		 * Creates an n-sized permutation matrix with randomly rearranged indexes.
		 *
		 * @param[in] n The permutation matrix size.
		 * @return The newly created permutation matrix.
		 */
		static PxMatrix random(uint_t n);

		/** @} */
};

/*-------------------------------------------------*/
} // namespace prm
/*-------------------------------------------------*/

template<typename T_Int>
class TypeTraits<prm::PxMatrix<T_Int>> {
	public:
		static std::string type_name() { return msg::PermutationMatrix(); };
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup module_index_stream_operators
 * @brief Writes to os the contents of mat.
 */
template <typename T_Int>
std::ostream& operator<<(std::ostream& os, const cla3p::prm::PxMatrix<T_Int>& mat)
{
	os << mat.toString();
	return os;
}

/*-------------------------------------------------*/

#endif // CLA3P_PXMATRIX_HPP_
