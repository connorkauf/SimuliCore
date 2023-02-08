// this file inc
#include "generic_dns.hpp"

// system

// 3rd

// cla3p
#include "../bulk/dns.hpp"
#include "../bulk/dns_io.hpp"
#include "../checks/all_checks.hpp"
#include "../support/error.hpp"
#include "../support/error_internal.hpp"
#include "../support/utils.hpp"
#include "../support/imalloc.hpp"
#include "../prm_mat.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
template <typename T, typename Tr>
GenericObject<T,Tr>::GenericObject()
{
	defaults();
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
GenericObject<T,Tr>::GenericObject(prop_t ptype, uint_t nrows, uint_t ncols, uint_t ld, bool wipe)
{
	if(wipe) {
		zeroCreator(ptype, nrows, ncols, ld);
	} else {
		blankCreator(ptype, nrows, ncols, ld);
	} // wipe
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
GenericObject<T,Tr>::~GenericObject()
{
	clear();
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
GenericObject<T,Tr>::GenericObject(GenericObject<T,Tr>&& src)
{
	src.moveTo(*this);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
GenericObject<T,Tr>& GenericObject<T,Tr>::operator=(GenericObject<T,Tr>&& src)
{
	src.moveTo(*this);
	return *this;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::defaults()
{
	Property prop(prop_t::NONE);

	setNrows (0);
	setNcols (0);
	setLd    (0);
	setValues(nullptr);
	setProp  (prop);
	setOwner (false);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::creator(prop_t ptype, uint_t nrows, uint_t ncols, T *values, uint_t ld, bool owner)
{
	dns_consistency_check(ptype, nrows, ncols, values, ld);

	Property prop(ptype);

	setNrows (nrows );
	setNcols (ncols );
	setValues(values);
	setLd    (ld    );
	setProp  (prop  );
	setOwner (owner );
}
/*-------------------------------------------------*/
template <typename T, typename Tr> void GenericObject<T,Tr>::setNrows (uint_t          nrows ) { m_nrows  = nrows ; }
template <typename T, typename Tr> void GenericObject<T,Tr>::setNcols (uint_t          ncols ) { m_ncols  = ncols ; }
template <typename T, typename Tr> void GenericObject<T,Tr>::setLd    (uint_t          ld    ) { m_ld     = ld    ; }
template <typename T, typename Tr> void GenericObject<T,Tr>::setValues(T*              values) { m_values = values; }
template <typename T, typename Tr> void GenericObject<T,Tr>::setProp  (const Property& prop  ) { m_prop   = prop  ; }
template <typename T, typename Tr> void GenericObject<T,Tr>::setOwner (bool            owner ) { m_owner  = owner ; }
/*-------------------------------------------------*/
template <typename T, typename Tr> uint_t          GenericObject<T,Tr>::nrows () const { return m_nrows ; }
template <typename T, typename Tr> uint_t          GenericObject<T,Tr>::ncols () const { return m_ncols ; }
template <typename T, typename Tr> uint_t          GenericObject<T,Tr>::ld    () const { return m_ld    ; }
template <typename T, typename Tr> T*              GenericObject<T,Tr>::values()       { return m_values; }
template <typename T, typename Tr> const T*        GenericObject<T,Tr>::values() const { return m_values; }
template <typename T, typename Tr> const Property& GenericObject<T,Tr>::prop  () const { return m_prop  ; }
template <typename T, typename Tr> bool            GenericObject<T,Tr>::owner () const { return m_owner ; }
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T, typename Tr>
bool GenericObject<T,Tr>::empty() const
{
	if(nrows() && ncols() && values()) 
		return false;

	return true;
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
template <typename T, typename Tr>
void GenericObject<T,Tr>::unbind()
{
	setOwner(false);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::scale(T coeff)
{
	bulk::dns::scale(prop().type(), nrows(), ncols(), values(), ld(), coeff);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::copyTo(GenericObject<T,Tr>& trg) const
{
	if(!empty()) {
		trg.blankCreator(prop().type(), nrows(), ncols(), nrows());
		bulk::dns::copy(prop().type(), nrows(), ncols(), values(), ld(), trg.values(), trg.ld());
	} else {
		trg.clear();
	}// (!)empty
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::moveTo(GenericObject<T,Tr>& trg)
{
	trg.clear();

	if(!empty()) {
		trg.creator(prop().type(), nrows(), ncols(), values(), ld(), owner());
	} // !empty

	unbind();
	clear();
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::cloneTo(GenericObject<T,Tr>& trg)
{
	trg.clear();

	if(!empty()) {
		trg.creator(prop().type(), nrows(), ncols(), values(), ld(), false);
	} // !empty
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::info(
		const std::string& msg, 
		const std::string& otype, 
		const std::string& dtype, 
		const std::string& dprec) const
{
	std::string top;
	std::string bottom;
	fill_info_margins(msg, top, bottom);

	std::cout << top << "\n";

	std::cout << "  Object type.......... " << otype << "\n";
	std::cout << "  Datatype............. " << dtype << "\n";
	std::cout << "  Precision............ " << dprec << "\n";

	bool is_vector = (otype == "Vector");
	bool is_matrix = (otype == "Matrix");

	if(is_vector) {
		std::cout << "  size................. " <<         nrows () << "\n";
		std::cout << "  values............... " <<         values() << "\n";
		std::cout << "  owner................ " << bool2yn(owner ()) << "\n";
	} // vector

	if(is_matrix) {
		std::cout << "  nrows................ " <<         nrows () << "\n";
		std::cout << "  ncols................ " <<         ncols () << "\n";
		std::cout << "  ld................... " <<         ld    () << "\n";
		std::cout << "  values............... " <<         values() << "\n";
		std::cout << "  prop................. " <<         prop  () << "\n";
		std::cout << "  owner................ " << bool2yn(owner ()) << "\n";
	} // matrix

	std::cout << bottom << "\n";
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::print(uint_t nsd) const
{
	bulk::dns::print(prop().type(), nrows(), ncols(), values(), ld(), nsd);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
std::string GenericObject<T,Tr>::printToString(uint_t nsd) const
{
	return bulk::dns::print_to_string(prop().type(), nrows(), ncols(), values(), ld(), nsd);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
Tr GenericObject<T,Tr>::normOne() const
{ 
	return bulk::dns::norm_one(prop().type(), nrows(), ncols(), values(), ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
Tr GenericObject<T,Tr>::normInf() const
{ 
	return bulk::dns::norm_inf(prop().type(), nrows(), ncols(), values(), ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
Tr GenericObject<T,Tr>::normMax() const
{ 
	return bulk::dns::norm_max(prop().type(), nrows(), ncols(), values(), ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
Tr GenericObject<T,Tr>::normFro() const
{ 
	return bulk::dns::norm_fro(prop().type(), nrows(), ncols(), values(), ld());
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

	trg.blankCreator(prop().type(), ncols(), nrows(), ncols());
	bulk::dns::transpose(nrows(), ncols(), values(), ld(), trg.values(), trg.ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::ctransposeTo(GenericObject<T,Tr>& trg) const
{
	transp_op_consistency_check(prop().type(), true);
	
	trg.blankCreator(prop().type(), ncols(), nrows(), ncols());
	bulk::dns::conjugate_transpose(nrows(), ncols(), values(), ld(), trg.values(), trg.ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::gePermuteTo(GenericObject<T,Tr>& trg, const prm::pMat& P, const prm::pMat& Q) const
{
	perm_ge_op_consistency_check(prop().type(), nrows(), ncols(), P.size(), Q.size());

	trg.blankCreator(prop().type(), nrows(), ncols(), nrows());
	bulk::dns::permute(prop().type(), nrows(), ncols(), values(), ld(), trg.values(), trg.ld(), P.values(), Q.values());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::gePermuteToLeft(GenericObject<T,Tr>& trg, const prm::pMat& P) const
{
	perm_ge_op_consistency_check(prop().type(), nrows(), ncols(), P.size(), ncols());

	trg.blankCreator(prop().type(), nrows(), ncols(), nrows());
	bulk::dns::permute(prop().type(), nrows(), ncols(), values(), ld(), trg.values(), trg.ld(), P.values(), nullptr);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::gePermuteToRight(GenericObject<T,Tr>& trg, const prm::pMat& Q) const
{
	perm_ge_op_consistency_check(prop().type(), nrows(), ncols(), nrows(), Q.size());

	trg.blankCreator(prop().type(), nrows(), ncols(), nrows());
	bulk::dns::permute(prop().type(), nrows(), ncols(), values(), ld(), trg.values(), trg.ld(), nullptr, Q.values());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::shPermuteTo(GenericObject<T,Tr>& trg, const prm::pMat& P) const
{
	perm_syhe_op_consistency_check(prop().type(), nrows(), ncols(), P.size(), P.size());

	trg.blankCreator(prop().type(), nrows(), ncols(), nrows());
	bulk::dns::permute(prop().type(), nrows(), ncols(), values(), ld(), trg.values(), trg.ld(), P.values(), nullptr);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::gePermuteIp(const prm::pMat& P, const prm::pMat& Q)
{
	GenericObject<T,Tr> tmp;
	gePermuteTo(tmp, P, Q);
	bulk::dns::copy(tmp.prop().type(), tmp.nrows(), tmp.ncols(), tmp.values(), tmp.ld(), values(), ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::gePermuteIpLeft(const prm::pMat& P)
{
	GenericObject<T,Tr> tmp;
	gePermuteToLeft(tmp, P);
	bulk::dns::copy(tmp.prop().type(), tmp.nrows(), tmp.ncols(), tmp.values(), tmp.ld(), values(), ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::gePermuteIpRight(const prm::pMat& Q)
{
	GenericObject<T,Tr> tmp;
	gePermuteToRight(tmp, Q);
	bulk::dns::copy(tmp.prop().type(), tmp.nrows(), tmp.ncols(), tmp.values(), tmp.ld(), values(), ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::shPermuteIp(const prm::pMat& P)
{
	GenericObject<T,Tr> tmp;
	shPermuteTo(tmp, P);
	bulk::dns::copy(tmp.prop().type(), tmp.nrows(), tmp.ncols(), tmp.values(), tmp.ld(), values(), ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::getBlock(GenericObject<T,Tr>& trg, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	prop_t blptype = block_op_consistency_check(prop().type(), nrows(), ncols(), ibgn, jbgn, ni, nj);

	trg.blankCreator(blptype, ni, nj, ni);
	bulk::dns::copy(blptype, ni, nj, bulk::dns::ptrmv(ld(),values(),ibgn,jbgn), ld(), trg.values(), trg.ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::getBlockReference(GenericObject<T,Tr>& trg, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj)
{
	prop_t blptype = block_op_consistency_check(prop().type(), nrows(), ncols(), ibgn, jbgn, ni, nj);

	trg.clear();
	trg.creator(blptype, ni, nj, bulk::dns::ptrmv(ld(),values(),ibgn,jbgn), ld(), false);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::setBlock(const GenericObject<T,Tr>& src, uint_t ibgn, uint_t jbgn)
{
	block_op_consistency_check(src.prop().type(), prop().type(), nrows(), ncols(), ibgn, jbgn, src.nrows(), src.ncols());

	bulk::dns::copy(src.prop().type(), src.nrows(), src.ncols(), src.values(), src.ld(), bulk::dns::ptrmv(ld(),values(),ibgn,jbgn), ld());
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::blankCreator(prop_t ptype, uint_t nrows, uint_t ncols, uint_t ld)
{
	clear();
	T *values = bulk::dns::alloc<T>(nrows, ncols, ld);
	creator(ptype, nrows, ncols, values, ld, true);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::zeroCreator(prop_t ptype, uint_t nrows, uint_t ncols, uint_t ld)
{
	blankCreator(ptype, nrows, ncols, ld);
	bulk::dns::zero(
			this->prop().type(), 
			this->nrows(), 
			this->ncols(), 
			this->values(), 
			this->ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::randomCreator(prop_t ptype, uint_t nrows, uint_t ncols, uint_t ld)
{
	blankCreator(ptype, nrows, ncols, ld);
	bulk::dns::rand(
			this->prop().type(), 
			this->nrows(), 
			this->ncols(), 
			this->values(), 
			this->ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::mapCreator(prop_t ptype, uint_t nrows, uint_t ncols, T *values, uint_t ld, bool bind)
{
	clear();
	creator(ptype, nrows, ncols, values, ld, bind);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template class GenericObject<real_t,real_t>;
template class GenericObject<real4_t,real4_t>;
template class GenericObject<complex_t,real_t>;
template class GenericObject<complex8_t,real4_t>;
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/