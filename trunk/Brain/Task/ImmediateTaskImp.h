#pragma once

namespace Ts
{
	class ImmediateTask;	

	class ImmediateTaskImp 													
	{															
	public:														
		typedef boost::shared_ptr<ImmediateTask>	owner_pointer;		
		typedef boost::weak_ptr<ImmediateTask>		owner_weak_pointer;	

	public:														
		ImmediateTaskImp(owner_weak_pointer pSelf);							

		owner_pointer   Self() const;	

	public:
		bool            IsReady();
		bool            Execute();

	private:													
		owner_weak_pointer			m_pSelf;
	};
}
