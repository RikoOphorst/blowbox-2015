#include "../../blowbox/memory/allocated_memory.h"

#include "../../blowbox/logging.h"

namespace blowbox
{ 
	AllocatedMemory::AllocatedMemory()
	{

	}

	AllocatedMemory& AllocatedMemory::Instance()
	{
		static AllocatedMemory alloc;
		return alloc;
	}

	AllocatedMemory::~AllocatedMemory()
	{
		BLOW_ASSERT(allocations_ == 0 && allocation_size_ == 0, "One or more memory leaks detected!");
	}

	void AllocatedMemory::Increase(int size)
	{
		allocations_++;
		allocation_size_ += size;
	}

	void AllocatedMemory::Decrease(int size)
	{
		allocations_--;
		allocation_size_ -= size;
	}
}