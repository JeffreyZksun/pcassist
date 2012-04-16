#pragma once

/************************************************************************
Usage:

	IMP_CLS_DECL_BEGIN_NOBASE(IMP, CLS);
	IMP_CLS_DECL_END;
	IMP_CLS_DEF_NOBASE(IMP, CLS);

	API_CLS_DECL_BEGIN(CLS, BASE, IMP);
	API_CLS_DECL_END;
	API_CLS_DEF(CLS, BASE, IMP);

************************************************************************/

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#define API_CLS_DECL_BEGIN(CLS, BASE, IMP)			\
class IMP;											\
													\
class CLS : public BASE								\
{													\
public:												\
	typedef boost::shared_ptr<CLS>	pointer;		\
	typedef boost::shared_ptr<IMP>	imp_pointer;	\
public:												\
	static pointer		Create();					\
													\
protected:											\
	CLS();											\
													\
private:											\
	imp_pointer         m_pImp;


#define API_CLS_DECL_END };


#define IMP_CLS_DECL_BEGIN_NOBASE(CLS, OWNER)				\
class OWNER;												\
class CLS 													\
{															\
public:														\
	typedef boost::shared_ptr<OWNER>	owner_pointer;		\
	typedef boost::weak_ptr<OWNER>		owner_weak_pointer;	\
public:														\
	CLS(owner_weak_pointer pSelf);							\
															\
	owner_pointer            Self() const;					\
															\
private:													\
	owner_weak_pointer			m_pSelf;

#define IMP_CLS_DECL_END };




