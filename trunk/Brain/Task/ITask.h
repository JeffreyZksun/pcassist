#pragma once



namespace Ts
{
    class ITask
    {
    public:
        virtual ~ITask(void){};

		virtual bool            IsReady() = 0;
		virtual bool            Execute() = 0;
    };
}