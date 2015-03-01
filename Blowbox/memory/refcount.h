#pragma once

#include "../../blowbox/memory/allocated_memory.h"

namespace blowbox
{
	template<typename T>
	class RefCount
	{
	public:
		RefCount() :
			references_(1),
			ptr_(nullptr)
		{

		}

		RefCount(T* ptr) :
			references_(1)
		{
			ptr_ = ptr;
		}

		~RefCount();

		inline void Increase()
		{
			++references_;
		}

		inline void Decrease()
		{
			if (--references_ == 0)
				Destroy();
		}

		inline void Destroy()
		{
			AllocatedMemory::Instance().Decrease(sizeof(ptr_));

			delete ptr_;
			ptr_ = nullptr;
		}
	private:
		T* ptr_;
		unsigned int references_;
	};
}