#ifndef CLA3P_OPERATIONS_HPP_
#define CLA3P_OPERATIONS_HPP_

#include "../types.hpp"
#include "../dense.hpp"

/*-------------------------------------------------*/

void operator+=(cla3p::dns::RiVector& trg, const cla3p::dns::RiVector& src);
void operator+=(cla3p::dns::RdVector& trg, const cla3p::dns::RdVector& src);
void operator+=(cla3p::dns::RfVector& trg, const cla3p::dns::RfVector& src);
void operator+=(cla3p::dns::CdVector& trg, const cla3p::dns::CdVector& src);
void operator+=(cla3p::dns::CfVector& trg, const cla3p::dns::CfVector& src);

void operator+=(cla3p::dns::RiMatrix& trg, const cla3p::dns::RiMatrix& src);
void operator+=(cla3p::dns::RdMatrix& trg, const cla3p::dns::RdMatrix& src);
void operator+=(cla3p::dns::RfMatrix& trg, const cla3p::dns::RfMatrix& src);
void operator+=(cla3p::dns::CdMatrix& trg, const cla3p::dns::CdMatrix& src);
void operator+=(cla3p::dns::CfMatrix& trg, const cla3p::dns::CfMatrix& src);

cla3p::dns::RiVector operator+(cla3p::dns::RiVector& srcA, const cla3p::dns::RiVector& srcB);
cla3p::dns::RdVector operator+(cla3p::dns::RdVector& srcA, const cla3p::dns::RdVector& srcB);
cla3p::dns::RfVector operator+(cla3p::dns::RfVector& srcA, const cla3p::dns::RfVector& srcB);
cla3p::dns::CdVector operator+(cla3p::dns::CdVector& srcA, const cla3p::dns::CdVector& srcB);
cla3p::dns::CfVector operator+(cla3p::dns::CfVector& srcA, const cla3p::dns::CfVector& srcB);
                    
cla3p::dns::RiMatrix operator+(cla3p::dns::RiMatrix& srcA, const cla3p::dns::RiMatrix& srcB);
cla3p::dns::RdMatrix operator+(cla3p::dns::RdMatrix& srcA, const cla3p::dns::RdMatrix& srcB);
cla3p::dns::RfMatrix operator+(cla3p::dns::RfMatrix& srcA, const cla3p::dns::RfMatrix& srcB);
cla3p::dns::CdMatrix operator+(cla3p::dns::CdMatrix& srcA, const cla3p::dns::CdMatrix& srcB);
cla3p::dns::CfMatrix operator+(cla3p::dns::CfMatrix& srcA, const cla3p::dns::CfMatrix& srcB);

cla3p::dns::RiVector operator*(cla3p::dns::RiMatrix& srcA, const cla3p::dns::RiVector& srcX);
cla3p::dns::RdVector operator*(cla3p::dns::RdMatrix& srcA, const cla3p::dns::RdVector& srcX);
cla3p::dns::RfVector operator*(cla3p::dns::RfMatrix& srcA, const cla3p::dns::RfVector& srcX);
cla3p::dns::CdVector operator*(cla3p::dns::CdMatrix& srcA, const cla3p::dns::CdVector& srcX);
cla3p::dns::CfVector operator*(cla3p::dns::CfMatrix& srcA, const cla3p::dns::CfVector& srcX);

/*-------------------------------------------------*/

#endif // CLA3P_OPERATIONS_HPP_