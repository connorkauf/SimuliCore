#ifndef CLA3P_ARRAY2D_HPP_
#define CLA3P_ARRAY2D_HPP_

#include <string>

#include "../types.hpp"
#include "../generic/ownership.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns {
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief A basic 2D array class.
 */
template <typename T_Scalar>
class Array2D : public Ownership{

	public:
		Array2D();
		~Array2D();

		// no copy
		Array2D(const Array2D<T_Scalar>&) = delete;
		Array2D<T_Scalar>& operator=(const Array2D<T_Scalar>&) = delete;

		// move
		Array2D(Array2D<T_Scalar>&&);
		Array2D<T_Scalar>& operator=(Array2D<T_Scalar>&&);

		uint_t rsize() const;
		uint_t csize() const;
		uint_t lsize() const;

		/**
		 * @brief The values array.
		 * @return The pointer to the numerical values of the object (column-major).
		 */
		T_Scalar* values();

		/**
		 * @copydoc values()
		 */
		const T_Scalar* values() const;

		/**
		 * @brief Test whether object is empty.
		 * @return whether the object is empty.
		 */
		bool empty() const;

		/**
		 * @brief Fills the object with a value.
		 *
		 * Sets all entries of the object to a single value.
		 *
		 * @param[in] val The value to be set.
		 */
		virtual void fill(T_Scalar val);

		/**
		 * @brief Prints the contents of the object.
		 * @param[in] nsd The number of significant digits (for real/complex types only, otherwise ignored).
		 */
		virtual void print(uint_t nsd = 3) const;

		/**
		 * @brief Prints the contents of the object to a string.
		 * @param[in] nsd The number of significant digits (for real/complex types only, otherwise ignored).
		 * @return The string containing the formatted numerical values of the object.
		 */
		virtual std::string toString(uint_t nsd = 3) const;

	protected:
		void alloc(uint_t, uint_t, uint_t);
		void clear();

		void copyTo(Array2D<T_Scalar>&) const;
		void copyToAllocated(Array2D<T_Scalar>&) const;
		void copyToShallow(Array2D<T_Scalar>&);
		void moveTo(Array2D<T_Scalar>&);

		void permuteToLeftRight(Array2D<T_Scalar>& trg, const uint_t *P, const uint_t *Q) const;
		void permuteToLeft(Array2D<T_Scalar>& trg, const uint_t *P) const;
		void permuteToRight(Array2D<T_Scalar>& trg, const uint_t *Q) const;

		void permuteIpLeftRight(const uint_t *P, const uint_t *Q);
		void permuteIpLeft(const uint_t *P);
		void permuteIpRight(const uint_t *Q);

		virtual T_Scalar& operator()(uint_t i, uint_t j);
		virtual const T_Scalar& operator()(uint_t i, uint_t j) const;

	private:
		uint_t    m_rsize;
		uint_t    m_csize;
		uint_t    m_lsize;
		T_Scalar* m_values;

		void setRsize(uint_t);
		void setCsize(uint_t);
		void setLsize(uint_t);
		void setValues(T_Scalar*);

		void defaults();
};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_ARRAY2D_HPP_
