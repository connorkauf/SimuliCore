#ifndef CLA3P_PROPERTY_HPP_
#define CLA3P_PROPERTY_HPP_

/** 
 * @file
 * Property configuration
 */

#include <ostream>
#include <string>

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/

/**
 * @ingroup basic_datatypes_group 
 * @enum prop_t
 * @brief The property type.
 */
enum class prop_t {
	NONE      = 0, /**< No property */
	GENERAL      , /**< General matrix */
	SYMMETRIC    , /**< Symmetric matrix */
	HERMITIAN    , /**< Hermitian matrix */
	TRIANGULAR   , /**< Triangular/trapezoidal matrix */
	SKEW           /**< Skew matrix */
};

/**
 * @ingroup basic_datatypes_group 
 * @enum uplo_t
 * @brief The fill type.
 */
enum class uplo_t : char {
	F = 'F', /**< Both parts are filled */
	U = 'U', /**< The upper part is filled */
	L = 'L'  /**< The lower part is filled */
};

/**
 * @ingroup basic_datatypes_group
 * @brief The property class.
 */
class Property {

	public:

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty property.
		 */
		Property();

		/**
		 * @brief The member constructor.
		 *
		 * Constructs a property with type ptype and fill type ftype.
		 */
		explicit Property(prop_t ptype, uplo_t ftype);

		/**
		 * @brief Destructs the property.
		 */
		~Property();

		/**
		 * @brief The copy constructor.
		 *
		 * Constructs a property with the copy of the contents of other.
		 */
		Property(const Property& other);

		/**
		 * @brief The copy assignment operator.
		 *
		 * Replaces the contents of property with a copy of the contents of other.
		 */
		Property& operator=(const Property& other);

		/**
		 * @brief The compare operator.
		 *
		 * Checks if two properties are equal
		 */
		bool operator==(const Property& other) const;

		/**
		 * @brief The compare operator.
		 *
		 * Checks if two properties are not equal
		 */
		bool operator!=(const Property& other) const;

		/**
		 * @brief The property type.
		 */
		prop_t type() const;

		/**
		 * @brief The property fill type.
		 */
		uplo_t uplo() const;

		/**
		 * @brief The property fill type as a char.
		 */
		char cuplo() const;

		/**
		 * @brief The property name.
		 */
		const std::string& name() const;

		/**
		 * @brief Checks weather the property has a valid type.
		 */
		bool isValid() const;

		/**
		 * @brief Checks weather the property requires matrix to be square.
		 */
		bool isSquare() const;

		/**
		 * @brief Checks weather the property type is general.
		 */
		bool isGeneral() const;

		/**
		 * @brief Checks weather the property type is symmetric.
		 */
		bool isSymmetric() const;

		/**
		 * @brief Checks weather the property type is hermitian.
		 */
		bool isHermitian() const;

		/**
		 * @brief Checks weather the property type is triangular/trapezoidal.
		 */
		bool isTriangular() const;

		/**
		 * @brief Checks weather the property type is skew.
		 */
		bool isSkew() const;

		/**
		 * @brief Checks weather the entire matrix is used.
		 */
		bool isFull() const;

		/**
		 * @brief Checks weather the upper part of the matrix is used.
		 */
		bool isUpper() const;

		/**
		 * @brief Checks weather the lower part of the matrix is used.
		 */
		bool isLower() const;

	private:
		prop_t m_type;
		uplo_t m_uplo;

		void check() const;
};

/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/

/**
 * @ingroup stream_operator_group
 * @brief Writes to os the type of prop.
 */
std::ostream& operator<<(std::ostream& so, const cla3p::Property& prop);

/*-------------------------------------------------*/

#endif // CLA3P_PROPERTY_HPP_