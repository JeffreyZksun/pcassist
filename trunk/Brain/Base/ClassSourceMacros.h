#pragma once


#define API_CLS_DEF(CLS, BASE, IMP)			\
CLS::CLS() : m_pImp()						\
{											\
}											\
											\
CLS::pointer CLS::Create()					\
{											\
	CLS::pointer pNewObj(new CLS());		\
	pNewObj->m_pImp.reset(new IMP(pNewObj));\
											\
	return pNewObj;							\
}

#define IMP_CLS_DEF_NOBASE(CLS, OWNER)		\
											\
CLS::CLS(owner_weak_pointer pSelf)			\
	: m_pSelf(pSelf)						\
{											\
}											\
											\
CLS::owner_pointer CLS::Self() const		\
{											\
	return m_pSelf.lock();					\
}