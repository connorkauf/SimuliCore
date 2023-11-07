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

#ifndef CLA3P_DNS_RXMATRIX_HPP_
#define CLA3P_DNS_RXMATRIX_HPP_

#include "cla3p/types/basic_traits.hpp"
#include "cla3p/dense/dns_xxmatrix.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns {
/*-------------------------------------------------*/

template <typename T_Scalar> class RxVector;

/**
 * @nosubgrouping 
 * @brief The dense real matrix class.
 */
template <typename T_Scalar>
class RxMatrix : public XxMatrix<T_Scalar,RxMatrix<T_Scalar>> {

	public:

		using value_type = T_Scalar;

		// no copy
		RxMatrix(const RxMatrix<T_Scalar>&) = delete;
		RxMatrix<T_Scalar>& operator=(const RxMatrix<T_Scalar>&) = delete;

		/**
		 * @name Constructors
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::XxMatrix::XxMatrix()
		 */
		explicit RxMatrix();

		/**
		 * @copydoc cla3p::dns::XxMatrix::XxMatrix(uint_t nr, uint_t nc, const Property& pr)
		 */
		explicit RxMatrix(uint_t nr, uint_t nc, const Property& pr = defaultProperty());

		/**
		 * @copydoc cla3p::dns::XxMatrix::XxMatrix(XxMatrix&& other)
		 */
		RxMatrix(RxMatrix<T_Scalar>&& other) = default;

		/**
		 * @copydoc cla3p::dns::XxMatrix::~XxMatrix()
		 */
		~RxMatrix();

		/** @} */

		/**
		 * @name Operators
		 * @{
		 */

		/**
		 * @copydoc cla3p::dns::XxMatrix::operator=(XxMatrix&& other)
		 */
		RxMatrix<T_Scalar>& operator=(RxMatrix<T_Scalar>&& other) = default;

		/**
		 * @copydoc cla3p::dns::XxMatrix::operator=(T_Scalar val)
		 */
		void operator=(T_Scalar val);

		/** @} */

};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

/*-------------------------------------------------*/
namespace cla3p {
template<typename T_Scalar>
class BasicTypeTraits<dns::RxMatrix<T_Scalar>> {
	public:
		static std::string type_name();
		using real_type = dns::RxMatrix<T_Scalar>;
		using vector_type = dns::RxVector<T_Scalar>;
};
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_RXMATRIX_HPP_
