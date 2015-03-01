#pragma once

namespace blowbox
{
	class AllocatedMemory
	{
	public:
		AllocatedMemory();

		~AllocatedMemory();

		static AllocatedMemory& Instance();

		void Increase(int size);
		void Decrease(int size);
	private:
		int allocations_;
		int allocation_size_;
	};
}