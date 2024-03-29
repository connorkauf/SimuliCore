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

#ifndef CLA3P_DNS_XXOBJECT_HPP_
#define CLA3P_DNS_XXOBJECT_HPP_

#include "cla3p/generic/array2d.hpp"
#include "cla3p/generic/guard.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns {
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief The dense object class.
 */
template <typename T_Scalar, typename T_Object>
class XxObject : public Array2D<T_Scalar> {
	
	private:
		using T_RScalar = typename TypeTraits<T_Scalar>::real_type;

	public:
		explicit XxObject();
		explicit XxObject(uint_t nr, uint_t nc, uint_t nl, const Property& pr);
		~XxObject();

		// no copy
		XxObject(const XxObject<T_Scalar,T_Object>&) = delete;
		XxObject<T_Scalar,T_Object>& operator=(const XxObject<T_Scalar,T_Object>&) = delete;

		// move
		XxObject(XxObject<T_Scalar,T_Object>&& other) = default;
		XxObject<T_Scalar,T_Object>& operator=(XxObject<T_Scalar,T_Object>&& other) = default;

		virtual const T_Object& self() const = 0;

		/** 
		 * @name Operators
		 * @{
		 */

		/**
		 * @brief Unary minus operator.
		 *
		 * Negates the object.
		 *
		 * @return The result of the operation `-(*this)`.
		 */
		T_Object operator-() const;

		/** @} */

		/** 
		 * @name Public Member Functions
		 * @{
		 */

		/**
		 * @brief Copies an object.
		 * @return A deep copy of `(*this)`.
		 *
		 * @see rcopy() const, rcopy(), move()
		 */
		T_Object copy() const;

		/**
		 * @brief Shallow-copies an object.
		 * @return A shallow copy of `(*this)`, `(*this)` is unchanged.
		 *
		 * @see copy(), rcopy() const, move()
		 */
		T_Object rcopy();

		/**
		 * @brief Shallow-copies an immutable object.
		 * @return A guard shallow copy of `(*this)`.
		 *
		 * @see copy(), rcopy(), move()
		 */
		Guard<T_Object> rcopy() const;

		/**
		 * @brief Moves an object.
		 * @return A shallow copy of `(*this)`, `(*this)` is destroyed.
		 *
		 * @see copy(), rcopy() const, rcopy()
		 */
		T_Object move();

		/**
		 * @brief Multiplies the object by a scalar.
		 * @param[in] val The scaling coefficient.
		 */
		void iscale(T_Scalar val);

		/**
		 * @brief Conjugates the object in-place.
		 */
		void iconjugate();

		/**
		 * @brief The 1-norm.
		 * @return The 1-norm of `(*this)`.
		 */
		T_RScalar normOne() const;

		/**
		 * @brief The infinite norm.
		 * @return The infinite norm of `(*this)`.
		 */
		T_RScalar normInf() const;

		/**
		 * @brief The maximum norm.
		 * @return The maximum norm of `(*this)`.
		 */
		T_RScalar normMax() const;

		/**
		 * @brief The Frobenius norm.
		 * @return The Frobenius norm of `(*this)`.
		 */
		T_RScalar normFro() const;

		/** @} */

	protected:
		T_Object getBlockCopy(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;
		T_Object getBlockReference(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);
		Guard<T_Object> getBlockReference(uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;
		void setBlockCopy(const XxObject<T_Scalar,T_Object>&, uint_t ibgn, uint_t jbgn);

};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup module_index_stream_operators
 * @brief Writes to os the contents of obj.
 */
template <typename T_Object>
std::ostream& operator<<(std::ostream& os, const cla3p::dns::XxObject<typename T_Object::value_type,T_Object>& obj)
{
  os << obj.toString();
  return os;
}

#endif // CLA3P_DNS_XXOBJECT_HPP_
