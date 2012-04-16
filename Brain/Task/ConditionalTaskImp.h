#pragma once

namespace Ts
{
	class ConditionalTask;	

	class ConditionalTaskImp 													
	{															
	public:														
		typedef boost::shared_ptr<ConditionalTask>	owner_pointer;		
		typedef boost::weak_ptr<ConditionalTask>		owner_weak_pointer;	

	public:														
		ConditionalTaskImp(owner_weak_pointer pSelf);							

		owner_pointer   Self() const;	

	public:
		bool            IsReady();
		bool            Execute();

	private:													
		owner_weak_pointer			m_pSelf;

	};

}
