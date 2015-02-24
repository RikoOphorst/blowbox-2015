#pragma once

#include <memory>
#include "../../blowbox/logging.h"

namespace blowbox
{
	struct AllocatedMemory
	{
		int allocations;
		int allocated_memory;

		~AllocatedMemory()
		{
			BLOW_ASSERT(allocations == 0 && allocated_memory == 0, "One or more memory leaks detected!");
		}
	};

	static AllocatedMemory& allocated_memory()
	{
		static AllocatedMemory alloc;
		return alloc;
	}

	template<typename T>
	class SharedPtr : public std::shared_ptr < T >
	{
	public:
		SharedPtr()
		{

		}

		SharedPtr(T* ptr) :
			std::shared_ptr<T>(ptr)
		{
			AllocatedMemory& alloc = allocated_memory();
			++alloc.allocations;
			alloc.allocated_memory += sizeof(this);
		}

		SharedPtr(SharedPtr&& other)
		{
			swap(other);
		}

		virtual ~SharedPtr()
		{
			if (use_count() <= 1)
			{
				AllocatedMemory& alloc = allocated_memory();
				--alloc.allocations;
				alloc.allocated_memory -= sizeof(this);
			}
		}
	};
}