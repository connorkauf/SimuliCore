// this file inc
#include "dns_generic.hpp"

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
GenericObject<T,Tr>::GenericObject(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld, bool wipe)
{
	if(wipe) {
		zero_creator(prop, nrows, ncols, ld);
	} else {
		blank_creator(prop, nrows, ncols, ld);
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
	src.move_to(*this);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
GenericObject<T,Tr>& GenericObject<T,Tr>::operator=(GenericObject<T,Tr>&& src)
{
	src.move_to(*this);
	return *this;
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::defaults()
{
	set_nrows (0);
	set_ncols (0);
	set_ld    (0);
	set_values(nullptr);
	set_prop  (Property(prop_t::NONE));
	set_owner (false);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::creator(const Property& prop, uint_t nrows, uint_t ncols, T *values, uint_t ld, bool owner)
{
	clear();

	if(!nrows || !ncols) return; // policy is on zero dimensions, return empty object

	dns_consistency_check(prop.type(), nrows, ncols, values, ld);

	set_nrows (nrows );
	set_ncols (ncols );
	set_values(values);
	set_ld    (ld    );
	set_prop  (prop  );
	set_owner (owner );
}
/*-------------------------------------------------*/
template <typename T, typename Tr> void GenericObject<T,Tr>::set_nrows (uint_t          nrows ) { m_nrows  = nrows ; }
template <typename T, typename Tr> void GenericObject<T,Tr>::set_ncols (uint_t          ncols ) { m_ncols  = ncols ; }
template <typename T, typename Tr> void GenericObject<T,Tr>::set_ld    (uint_t          ld    ) { m_ld     = ld    ; }
template <typename T, typename Tr> void GenericObject<T,Tr>::set_values(T*              values) { m_values = values; }
template <typename T, typename Tr> void GenericObject<T,Tr>::set_prop  (const Property& prop  ) { m_prop   = prop  ; }
template <typename T, typename Tr> void GenericObject<T,Tr>::set_owner (bool            owner ) { m_owner  = owner ; }
/*-------------------------------------------------*/
template <typename T, typename Tr> uint_t          GenericObject<T,Tr>::nrows () const { return m_nrows ; }
template <typename T, typename Tr> uint_t          GenericObject<T,Tr>::ncols () const { return m_ncols ; }
template <typename T, typename Tr> uint_t          GenericObject<T,Tr>::ld    () const { return m_ld    ; }
template <typename T, typename Tr> T*              GenericObject<T,Tr>::values()       { return m_values; }
template <typename T, typename Tr> const T*        GenericObject<T,Tr>::values() const { return m_values; }
template <typename T, typename Tr> const Property& GenericObject<T,Tr>::prop  () const { return m_prop  ; }
template <typename T, typename Tr> bool            GenericObject<T,Tr>::owner () const { return m_owner ; }
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
	set_owner(false);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::scale(T coeff)
{
	bulk::dns::scale(prop().type(), nrows(), ncols(), values(), ld(), coeff);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::copy_to(GenericObject<T,Tr>& trg) const
{
	trg.blank_creator(prop(), nrows(), ncols(), nrows());
	bulk::dns::copy(prop().type(), nrows(), ncols(), values(), ld(), trg.values(), trg.ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::move_to(GenericObject<T,Tr>& trg)
{
	trg.creator(prop(), nrows(), ncols(), values(), ld(), owner());
	
	unbind();
	clear();
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::clone_to(GenericObject<T,Tr>& trg)
{
	trg.creator(prop(), nrows(), ncols(), values(), ld(), false);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::transpose_to(GenericObject<T,Tr>& trg) const
{
	if(empty()) {
		trg.clear();
	} else {
		transp_op_consistency_check(prop().type(), false);
		trg.blank_creator(prop(), ncols(), nrows(), ncols());
		bulk::dns::transpose(nrows(), ncols(), values(), ld(), trg.values(), trg.ld());
	} // empty
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::ctranspose_to(GenericObject<T,Tr>& trg) const
{
	if(empty()) {
		trg.clear();
	} else {
		transp_op_consistency_check(prop().type(), true);
		trg.blank_creator(prop(), ncols(), nrows(), ncols());
		bulk::dns::conjugate_transpose(nrows(), ncols(), values(), ld(), trg.values(), trg.ld());
	} // empty
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::permute_to(GenericObject<T,Tr>& trg, const prm::pMat& P, const prm::pMat& Q) const
{
	if(empty() && P.empty() && Q.empty()) {
		trg.clear();
	} else {
		perm_ge_op_consistency_check(prop().type(), nrows(), ncols(), P.size(), Q.size());
		trg.blank_creator(prop(), nrows(), ncols(), nrows());
		bulk::dns::permute(prop().type(), nrows(), ncols(), values(), ld(), trg.values(), trg.ld(), P.values(), Q.values());
	} // empty
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::lpermute_to(GenericObject<T,Tr>& trg, const prm::pMat& P) const
{
	if(empty() && P.empty()) {
		trg.clear();
	} else {
		perm_ge_op_consistency_check(prop().type(), nrows(), ncols(), P.size(), ncols());
		trg.blank_creator(prop(), nrows(), ncols(), nrows());
		bulk::dns::permute(prop().type(), nrows(), ncols(), values(), ld(), trg.values(), trg.ld(), P.values(), nullptr);
	} // empty
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::rpermute_to(GenericObject<T,Tr>& trg, const prm::pMat& Q) const
{
	if(empty() && Q.empty()) {
		trg.clear();
	} else {
		perm_ge_op_consistency_check(prop().type(), nrows(), ncols(), nrows(), Q.size());
		trg.blank_creator(prop(), nrows(), ncols(), nrows());
		bulk::dns::permute(prop().type(), nrows(), ncols(), values(), ld(), trg.values(), trg.ld(), nullptr, Q.values());
	} // empty
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::shpermute_to(GenericObject<T,Tr>& trg, const prm::pMat& P) const
{
	if(empty() && P.empty()) {
		trg.clear();
	} else {
		perm_syhe_op_consistency_check(prop().type(), nrows(), ncols(), P.size(), P.size());
		trg.blank_creator(prop(), nrows(), ncols(), nrows());
		bulk::dns::permute(prop().type(), nrows(), ncols(), values(), ld(), trg.values(), trg.ld(), P.values(), nullptr);
	} // empty
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::get_block(GenericObject<T,Tr>& trg, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const
{
	prop_t blptype = block_op_consistency_check(prop().type(), nrows(), ncols(), ibgn, jbgn, ni, nj);
	trg.blank_creator(Property(blptype), ni, nj, ni);
	bulk::dns::copy(blptype, ni, nj, bulk::dns::ptrmv(ld(),values(),ibgn,jbgn), ld(), trg.values(), trg.ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::get_block_reference(GenericObject<T,Tr>& trg, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj)
{
	prop_t blptype = block_op_consistency_check(prop().type(), nrows(), ncols(), ibgn, jbgn, ni, nj);
	trg.creator(Property(blptype), ni, nj, bulk::dns::ptrmv(ld(),values(),ibgn,jbgn), ld(), false);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::set_block(const GenericObject<T,Tr>& src, uint_t ibgn, uint_t jbgn)
{
	block_op_consistency_check(src.prop().type(), prop().type(), nrows(), ncols(), ibgn, jbgn, src.nrows(), src.ncols());
	bulk::dns::copy(src.prop().type(), src.nrows(), src.ncols(), src.values(), src.ld(), bulk::dns::ptrmv(ld(),values(),ibgn,jbgn), ld());
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
std::string GenericObject<T,Tr>::print2str(uint_t nsd) const
{
	return bulk::dns::print2str(prop().type(), nrows(), ncols(), values(), ld(), nsd);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
Tr GenericObject<T,Tr>::norm_one() const
{ 
	return bulk::dns::norm_one(prop().type(), nrows(), ncols(), values(), ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
Tr GenericObject<T,Tr>::norm_inf() const
{ 
	return bulk::dns::norm_inf(prop().type(), nrows(), ncols(), values(), ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
Tr GenericObject<T,Tr>::norm_max() const
{ 
	return bulk::dns::norm_max(prop().type(), nrows(), ncols(), values(), ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
Tr GenericObject<T,Tr>::norm_fro() const
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
template <typename T, typename Tr>
void GenericObject<T,Tr>::blank_creator(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld)
{
	T *values = bulk::dns::alloc<T>(nrows, ncols, ld);
	creator(prop, nrows, ncols, values, ld, true);
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::zero_creator(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld)
{
	blank_creator(prop, nrows, ncols, ld);
	bulk::dns::zero(
			this->prop().type(), 
			this->nrows(), 
			this->ncols(), 
			this->values(), 
			this->ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::random_creator(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld)
{
	blank_creator(prop, nrows, ncols, ld);
	bulk::dns::rand(
			this->prop().type(), 
			this->nrows(), 
			this->ncols(), 
			this->values(), 
			this->ld());
}
/*-------------------------------------------------*/
template <typename T, typename Tr>
void GenericObject<T,Tr>::map_creator(const Property& prop, uint_t nrows, uint_t ncols, T *values, uint_t ld, bool bind)
{
	creator(prop, nrows, ncols, values, ld, bind);
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