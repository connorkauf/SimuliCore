// this file inc
#include "array2d.hpp"

// system

// 3rd

// cla3p
//#include "../bulk/dns.hpp"
//#include "../bulk/dns_math.hpp"
//#include "../bulk/dns_io.hpp"
//#include "../checks/all_checks.hpp"
//#include "../support/error.hpp"
//#include "../support/utils.hpp"
#include "../support/imalloc.hpp"
//#include "../perms/perm_matrix.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
template <typename T_Scalar>
Array2D<T_Scalar>::Array2D()
{
	defaults();
}
/*-------------------------------------------------*/
template <typename T_Scalar>
Array2D<T_Scalar>::~Array2D()
{
	clear();
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Array2D<T_Scalar>::defaults()
{
	setRsize(0);
	setCsize(0);
	setValues(nullptr);
}
/*-------------------------------------------------*/
template <typename T_Scalar> 
void Array2D<T_Scalar>::setRsize(uint_t nr) 
{ 
	m_rsize = nr; 
}
/*-------------------------------------------------*/
template <typename T_Scalar> 
void Array2D<T_Scalar>::setCsize(uint_t nc) 
{
	m_csize = nc; 
}
/*-------------------------------------------------*/
template <typename T_Scalar> 
void Array2D<T_Scalar>::setValues(T_Scalar* vals) 
{ 
	m_values = vals; 
}
/*-------------------------------------------------*/
template <typename T_Scalar> 
uint_t Array2D<T_Scalar>::rsize() const
{ 
	return m_rsize; 
}
/*-------------------------------------------------*/
template <typename T_Scalar> 
uint_t Array2D<T_Scalar>::csize() const
{
	return m_csize; 
}
/*-------------------------------------------------*/
template <typename T_Scalar> 
T_Scalar* Array2D<T_Scalar>::values() 
{ 
	return m_values; 
}
/*-------------------------------------------------*/
template <typename T_Scalar> 
const T_Scalar* Array2D<T_Scalar>::values() const
{ 
	return m_values; 
}
/*-------------------------------------------------*/
template <typename T_Scalar>
void Array2D<T_Scalar>::clear()
{
	i_free(values());
	defaults();
}
/*-------------------------------------------------*/
template <typename T_Scalar>
bool Array2D<T_Scalar>::empty() const
{
	return (!rsize() || !csize());
}
/*-------------------------------------------------*/
#if 0
template <typename T, typename Tr>
void GenericObject<T,Tr>::defaults()
{
	UniversalMetaData::defaults();

	Property prop;

	setLd    (0);
	setValues(nullptr);
	setProp  (prop);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::creator(const Property& pr, uint_t nr, uint_t nc, T *vals, uint_t ldv, bool owner)
{
	dns_consistency_check(pr, nr, nc, vals, ldv);

	// meta data
	setAllMeta(nr, nc, owner);

	// additional
	setValues(vals);
	setLd    (ldv );
	setProp  (pr);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::fill(T val)
{
	if(prop().isHermitian()) {
		T diag = val;
		setim(diag,0);
		bulk::dns::fill(prop().uplo(), rsize(), csize(), values(), ld(), val, diag);
	} else if(prop().isSkew()) {
		T diag = 0;
		bulk::dns::fill(prop().uplo(), rsize(), csize(), values(), ld(), val, diag);
	} else {
		bulk::dns::fill(prop().uplo(), rsize(), csize(), values(), ld(), val);
	}
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::clear()
{
	if(owner()) {
		i_free(values());
	} // owner

	defaults();
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::scaleWith(T coeff)
{
	bulk::dns::scale(prop().uplo(), rsize(), csize(), values(), ld(), coeff);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::copyTo(GenericObject<T,Tr>& trg) const
{
	if(this == &trg) return; // do not apply on self 

	if(!empty()) {
		trg.blankCreator(prop(), rsize(), csize(), rsize());
		bulk::dns::copy(prop().uplo(), rsize(), csize(), values(), ld(), trg.values(), trg.ld());
	} else {
		trg.clear();
	}// (!)empty
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::moveTo(GenericObject<T,Tr>& trg)
{
	if(this == &trg) return; // do not apply on self 

	trg.clear();

	if(!empty()) {
		trg.creator(prop(), rsize(), csize(), values(), ld(), owner());
	} // !empty

	unbind();
	clear();
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::cloneTo(GenericObject<T,Tr>& trg)
{
	if(this == &trg) return; // do not apply on self 

	trg.clear();

	if(!empty()) {
		trg.creator(prop(), rsize(), csize(), values(), ld(), false);
	} // !empty
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
std::string GenericObject<T,Tr>::info(bool is2D,
		const std::string& msg, 
		const std::string& otype, 
		const std::string& dtype, 
		const std::string& dprec) const
{
	std::string top;
	std::string bottom;
	fill_info_margins(msg, top, bottom);

	std::stringstream ss;

	ss << top << "\n";

	ss << "  Object type.......... " << otype << "\n";
	ss << "  Datatype............. " << dtype << "\n";
	ss << "  Precision............ " << dprec << "\n";

	if(is2D) {
		ss << "  Number of rows....... " <<         rsize ()  << "\n";
		ss << "  Number of columns.... " <<         csize ()  << "\n";
		ss << "  Leading dimension.... " <<         ld    ()  << "\n";
		ss << "  Values............... " <<         values()  << "\n";
		ss << "  Property............. " <<         prop  ()  << "\n";
		ss << "  Owner................ " << bool2yn(owner ()) << "\n";
	} else {
		ss << "  Size................. " <<         rsize ()  << "\n";
		ss << "  Values............... " <<         values()  << "\n";
		ss << "  Owner................ " << bool2yn(owner ()) << "\n";
	} // 1/2D

	ss << bottom << "\n";

	return ss.str();
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::print(uint_t nsd) const
{
	bulk::dns::print(prop().uplo(), rsize(), csize(), values(), ld(), nsd);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
std::string GenericObject<T,Tr>::printToString(uint_t nsd) const
{
	return bulk::dns::print_to_string(prop().uplo(), rsize(), csize(), values(), ld(), nsd);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
Tr GenericObject<T,Tr>::normOne() const
{ 
	return bulk::dns::norm_one(prop().type(), prop().uplo(), rsize(), csize(), values(), ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
Tr GenericObject<T,Tr>::normInf() const
{ 
	return bulk::dns::norm_inf(prop().type(), prop().uplo(), rsize(), csize(), values(), ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
Tr GenericObject<T,Tr>::normMax() const
{ 
	return bulk::dns::norm_max(prop().type(), prop().uplo(), rsize(), csize(), values(), ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
Tr GenericObject<T,Tr>::normFro() const
{ 
	return bulk::dns::norm_fro(prop().type(), prop().uplo(), rsize(), csize(), values(), ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
Tr GenericObject<T,Tr>::normEuc() const
{ 
	if(csize() > 1) {
		throw Exception("Euclidian norm is applied on single column objects only");
	} // csize
	return bulk::dns::norm_euc(rsize(), values());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
T& GenericObject<T,Tr>::operator()(uint_t i, uint_t j)
{
	return bulk::dns::entry(ld(), values(), i, j);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
const T& GenericObject<T,Tr>::operator()(uint_t i, uint_t j) const
{
	return bulk::dns::entry(ld(), values(), i, j);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::transposeTo(GenericObject<T,Tr>& trg) const
{
	transp_op_consistency_check(prop().type(), false);

	trg.blankCreator(prop(), csize(), rsize(), csize());
	bulk::dns::transpose(rsize(), csize(), values(), ld(), trg.values(), trg.ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::ctransposeTo(GenericObject<T,Tr>& trg) const
{
	transp_op_consistency_check(prop().type(), true);
	
	trg.blankCreator(prop(), csize(), rsize(), csize());
	bulk::dns::conjugate_transpose(rsize(), csize(), values(), ld(), trg.values(), trg.ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::conjugateIp()
{
	bulk::dns::conjugate(prop().uplo(), rsize(), csize(), values(), ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::convertToGeneral(GenericObject<T,Tr>& trg) const
{
	copyTo(trg);
	trg.convertToGeneralIp();
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::convertToGeneralIp()
{
	if(prop().isGeneral()) {

		// do nothing

	} else if(prop().isSymmetric()) {

		bulk::dns::sy2ge(prop().uplo(), csize(), values(), ld());
		setProp(Property(prop_t::GENERAL,uplo_t::F));

	} else if(prop().isHermitian()) {

		bulk::dns::he2ge(prop().uplo(), csize(), values(), ld());
		setProp(Property(prop_t::GENERAL,uplo_t::F));

	} else if(prop().isTriangular()) {

		bulk::dns::tr2ge(prop().uplo(), rsize(), csize(), values(), ld());
		setProp(Property(prop_t::GENERAL,uplo_t::F));

	} else if(prop().isSkew()) {

		bulk::dns::sk2ge(prop().uplo(), csize(), values(), ld());
		setProp(Property(prop_t::GENERAL,uplo_t::F));

	} else {

		throw Exception();

	} // property 
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::gePermuteTo(GenericObject<T,Tr>& trg, const PermMatrix& P, const PermMatrix& Q) const
{
	perm_ge_op_consistency_check(prop().type(), rsize(), csize(), P.size(), Q.size());

	trg.blankCreator(prop(), rsize(), csize(), rsize());
	bulk::dns::permute(prop().type(), prop().uplo(), rsize(), csize(), values(), ld(), trg.values(), trg.ld(), P.values(), Q.values());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::gePermuteToLeft(GenericObject<T,Tr>& trg, const PermMatrix& P) const
{
	perm_ge_op_consistency_check(prop().type(), rsize(), csize(), P.size(), csize());

	trg.blankCreator(prop(), rsize(), csize(), rsize());
	bulk::dns::permute(prop().type(), prop().uplo(), rsize(), csize(), values(), ld(), trg.values(), trg.ld(), P.values(), nullptr);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::gePermuteToRight(GenericObject<T,Tr>& trg, const PermMatrix& Q) const
{
	perm_ge_op_consistency_check(prop().type(), rsize(), csize(), rsize(), Q.size());

	trg.blankCreator(prop(), rsize(), csize(), rsize());
	bulk::dns::permute(prop().type(), prop().uplo(), rsize(), csize(), values(), ld(), trg.values(), trg.ld(), nullptr, Q.values());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::xxPermuteToMirror(GenericObject<T,Tr>& trg, const PermMatrix& P) const
{
	perm_op_consistency_check(rsize(), csize(), P.size(), P.size());

	PermMatrix iP;
	if(prop().isGeneral()) iP = P.inverse();

	trg.blankCreator(prop(), rsize(), csize(), rsize());
	bulk::dns::permute(prop().type(), prop().uplo(), rsize(), csize(), values(), ld(), trg.values(), trg.ld(), P.values(), iP.values());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::gePermuteIp(const PermMatrix& P, const PermMatrix& Q)
{
	GenericObject<T,Tr> tmp;
	gePermuteTo(tmp, P, Q);
	setBlock(tmp, 0, 0);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::gePermuteIpLeft(const PermMatrix& P)
{
	GenericObject<T,Tr> tmp;
	gePermuteToLeft(tmp, P);
	setBlock(tmp, 0, 0);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::gePermuteIpRight(const PermMatrix& Q)
{
	GenericObject<T,Tr> tmp;
	gePermuteToRight(tmp, Q);
	setBlock(tmp, 0, 0);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::xxPermuteIpMirror(const PermMatrix& P)
{
	GenericObject<T,Tr> tmp;
	xxPermuteToMirror(tmp, P);
	setBlock(tmp, 0, 0);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::getBlock(GenericObject<T,Tr>& trg, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	Property blprop = block_op_consistency_check(prop(), rsize(), csize(), ibgn, jbgn, ni, nj);

	trg.blankCreator(blprop, ni, nj, ni);
	bulk::dns::copy(blprop.uplo(), ni, nj, bulk::dns::ptrmv(ld(),values(),ibgn,jbgn), ld(), trg.values(), trg.ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::getBlockReference(GenericObject<T,Tr>& trg, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj)
{
	Property blprop = block_op_consistency_check(prop(), rsize(), csize(), ibgn, jbgn, ni, nj);

	trg.clear();
	trg.creator(blprop, ni, nj, bulk::dns::ptrmv(ld(),values(),ibgn,jbgn), ld(), false);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::setBlock(const GenericObject<T,Tr>& src, uint_t ibgn, uint_t jbgn)
{
	block_op_consistency_check(src.prop(), prop(), rsize(), csize(), ibgn, jbgn, src.rsize(), src.csize());

	bulk::dns::copy(src.prop().uplo(), src.rsize(), src.csize(), src.values(), src.ld(), bulk::dns::ptrmv(ld(),values(),ibgn,jbgn), ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::getRealBlock(GenericObject<Tr,Tr>& trg, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	Property blprop = block_op_consistency_check(prop(), rsize(), csize(), ibgn, jbgn, ni, nj);

	if(blprop.isHermitian()) {
		blprop = Property(prop_t::SYMMETRIC, blprop.uplo());
	}

	trg.blankCreator(blprop, ni, nj, ni);
	bulk::dns::get_real(blprop.uplo(), ni, nj, bulk::dns::ptrmv(ld(),values(),ibgn,jbgn), ld(), trg.values(), trg.ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::getImagBlock(GenericObject<Tr,Tr>& trg, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	Property blprop = block_op_consistency_check(prop(), rsize(), csize(), ibgn, jbgn, ni, nj);

	if(blprop.isHermitian()) {
		blprop = Property(prop_t::SKEW, blprop.uplo());
	}

	trg.blankCreator(blprop, ni, nj, ni);
	bulk::dns::get_imag(blprop.uplo(), ni, nj, bulk::dns::ptrmv(ld(),values(),ibgn,jbgn), ld(), trg.values(), trg.ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::setRealBlock(const GenericObject<Tr,Tr>& src, uint_t ibgn, uint_t jbgn)
{
	real_block_op_consistency_check(src.prop(), prop(), rsize(), csize(), ibgn, jbgn, src.rsize(), src.csize());

	bulk::dns::set_real(src.prop().uplo(), src.rsize(), src.csize(), src.values(), src.ld(), bulk::dns::ptrmv(ld(),values(),ibgn,jbgn), ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::setImagBlock(const GenericObject<Tr,Tr>& src, uint_t ibgn, uint_t jbgn)
{
	imag_block_op_consistency_check(src.prop(), prop(), rsize(), csize(), ibgn, jbgn, src.rsize(), src.csize());

	bulk::dns::set_imag(src.prop().uplo(), src.rsize(), src.csize(), src.values(), src.ld(), bulk::dns::ptrmv(ld(),values(),ibgn,jbgn), ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::getRealPart(GenericObject<Tr,Tr>& trg) const
{
	getRealBlock(trg, 0, 0, rsize(), csize());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::getImagPart(GenericObject<Tr,Tr>& trg) const
{
	getImagBlock(trg, 0, 0, rsize(), csize());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::setRealPart(const GenericObject<Tr,Tr>& src)
{
	op_similarity_check(prop(), rsize(), csize(), src.prop(), src.rsize(), src.csize());

	setRealBlock(src, 0, 0);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::setImagPart(const GenericObject<Tr,Tr>& src)
{
	op_similarity_check(prop(), rsize(), csize(), src.prop(), src.rsize(), src.csize());

	setImagBlock(src, 0, 0);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::blankCreator(const Property& pr, uint_t nr, uint_t nc, uint_t ldim)
{
	clear();
	T *values = bulk::dns::alloc<T>(nr, nc, ldim);
	creator(pr, nr, nc, values, ldim, true);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::zeroCreator(const Property& pr, uint_t nr, uint_t nc, uint_t ldim)
{
	blankCreator(pr, nr, nc, ldim);
	bulk::dns::zero(prop().uplo(), rsize(), csize(), values(), ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::randomCreator(const Property& pr, uint_t nr, uint_t nc, uint_t ldim)
{
	blankCreator(pr, nr, nc, ldim);
	bulk::dns::rand(prop().uplo(), rsize(), csize(), values(), ld());

	if(prop().isHermitian()) {
		for(uint_t j = 0; j < nc; j++) {
			setim((*this)(j,j), 0);
		} // j
	} else if (prop().isSkew()) {
		for(uint_t j = 0; j < nc; j++) {
			(*this)(j,j) = 0;
		} // j
	} // diagonal handling
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::wrapCreator(const Property& pr, uint_t nr, uint_t nc, T *vals, uint_t ldv, bool bind)
{
	clear();
	creator(pr, nr, nc, vals, ldv, bind);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::updateSelf(T alpha, const GenericObject<T,Tr>& A)
{
	op_similarity_check(prop(), rsize(), csize(), A.prop(), A.rsize(), A.csize());
	bulk::dns::update(prop().uplo(), rsize(), csize(), alpha, A.values(), A.ld(), values(), ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::createFromSum(T alpha, const GenericObject<T,Tr>& A, T beta, const GenericObject<T,Tr>& B)
{
	op_similarity_check(A.prop(), A.rsize(), A.csize(), B.prop(), B.rsize(), B.csize());

	blankCreator(A.prop(), A.rsize(), A.csize(), A.rsize());
	bulk::dns::add(prop().uplo(), rsize(), csize(), alpha, A.values(), A.ld(), beta , B.values(), B.ld(), values(), ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::updateSelfWithMatVec(T alpha, const Operation& opA, const GenericObject<T,Tr>& A, const GenericObject<T,Tr>& X)
{
	matvec_mult_check(opA, A.prop(), A.rsize(), A.csize(), X.prop(), X.rsize(), X.csize(), prop(), rsize(), csize());

	if(A.prop().isGeneral()) {

		bulk::dns::gem_x_vec(opA.type(), A.rsize(), A.csize(), alpha, A.values(), A.ld(), X.values(), 1, values());

	} else if(A.prop().isSymmetric()) {

		bulk::dns::sym_x_vec(A.prop().uplo(), A.csize(), alpha, A.values(), A.ld(), X.values(), 1, values());

	} else if(A.prop().isHermitian()) {

		bulk::dns::hem_x_vec(A.prop().uplo(), A.csize(), alpha, A.values(), A.ld(), X.values(), 1, values());

	} else if(A.prop().isTriangular()) {

		GenericObject<T,Tr> tmp(Property(prop_t::GENERAL,uplo_t::F), rsize(), csize(), rsize(), false);
		bulk::dns::trm_x_vec(A.prop().uplo(), opA.type(), A.rsize(), A.csize(), alpha, A.values(), A.ld(), X.values(), tmp.values());
		updateSelf(1, tmp);

	} else {

		throw Exception();

	} // property 
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::updateSelfWithMatMat(T alpha, const Operation& opA, const GenericObject<T,Tr>& A, const Operation& opB, const GenericObject<T,Tr>& B)
{
	mat_x_mat_mult_check(
			A.prop(), A.rsize(), A.csize(), opA,
			B.prop(), B.rsize(), B.csize(), opB,
			prop(), rsize(), csize());

	if(A.prop().isGeneral() && B.prop().isGeneral()) {

		uint_t k = (opA.isTranspose() ? A.rsize() : A.csize());
		bulk::dns::gem_x_gem(rsize(), csize(), k, alpha, opA.type(), A.values(), A.ld(), opB.type(), B.values(), B.ld(), 1, values(), ld());

	} else if(A.prop().isSymmetric() && B.prop().isGeneral()) {

		bulk::dns::sym_x_gem(A.prop().uplo(), rsize(), csize(), alpha, A.values(), A.ld(), B.values(), B.ld(), 1, values(), ld());

	} else if(A.prop().isHermitian() && B.prop().isGeneral()) {

		bulk::dns::hem_x_gem(A.prop().uplo(), rsize(), csize(), alpha, A.values(), A.ld(), B.values(), B.ld(), 1, values(), ld());

	} else if(A.prop().isGeneral() && B.prop().isSymmetric()) {

		bulk::dns::gem_x_sym(B.prop().uplo(), rsize(), csize(), alpha, B.values(), B.ld(), A.values(), A.ld(), 1, values(), ld());

	} else if(A.prop().isGeneral() && B.prop().isHermitian()) {

		bulk::dns::gem_x_hem(B.prop().uplo(), rsize(), csize(), alpha, B.values(), B.ld(), A.values(), A.ld(), 1, values(), ld());

	} else if(A.prop().isTriangular() && B.prop().isGeneral()) {

		GenericObject<T,Tr> tmp(Property(prop_t::GENERAL,uplo_t::F), rsize(), csize(), rsize(), false);
		bulk::dns::trm_x_gem(A.prop().uplo(), opA.type(), rsize(), csize(), B.rsize(), alpha, A.values(), A.ld(), B.values(), B.ld(), tmp.values(), tmp.ld());
		updateSelf(1, tmp);

	} else if(A.prop().isGeneral() && B.prop().isTriangular()) {

		GenericObject<T,Tr> tmp(Property(prop_t::GENERAL,uplo_t::F), rsize(), csize(), rsize(), false);
		bulk::dns::gem_x_trm(B.prop().uplo(), opB.type(), rsize(), csize(), A.rsize(), alpha, B.values(), B.ld(), A.values(), A.ld(), tmp.values(), tmp.ld());
		updateSelf(1, tmp);

	} else {

		throw Exception();

	} // property combos
}
#endif // 0
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template class Array2D<int_t>;
template class Array2D<uint_t>;
template class Array2D<real_t>;
template class Array2D<real4_t>;
template class Array2D<complex_t>;
template class Array2D<complex8_t>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/