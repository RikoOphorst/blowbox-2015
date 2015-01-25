#pragma once

#include "../precompile/definitions.h"
#include <memory>

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
class SharedPtr : public std::shared_ptr<T>
{
public:
	SharedPtr(T* ptr) :
		std::shared_ptr<T>(ptr)
	{
		AllocatedMemory& alloc = allocated_memory();
		++alloc.allocations;
		alloc.allocated_memory += sizeof(this);
	}

	SharedPtr(SharedPtr&& other)
	{
		AllocatedMemory& alloc = allocated_memory();
		++alloc.allocations;
		alloc.allocated_memory += sizeof(this);
		swap(other);
	}

	virtual ~SharedPtr()
	{
		AllocatedMemory& alloc = allocated_memory();
		--alloc.allocations;
		alloc.allocated_memory -= sizeof(this);
	}
};