#pragma once

namespace blowbox
{
	/**
	* @class blowbox::AllocatedMemory
	* @brief Handles all heap allocated memory
	* @author Riko Ophorst
	*/
	class AllocatedMemory
	{
	public:
		/**
		* @brief Default AllocatedMemory constructor
		*/
		AllocatedMemory();

		/**
		* @brief Default AllocatedMemory destructor
		*/
		~AllocatedMemory();

		/**
		* @brief Retrieve the reference to the allocated memory instance
		*/
		static AllocatedMemory& Instance();

		/**
		* @brief Increases the total allocations and the allocated size on the heap
		* @param[in] size (int size) the size of the pointer to be allocated
		*/
		void Increase(int size);

		/**
		* @brief Decreases the total allocations and the allocated size on the heap
		* @param[in] size (int size) the size of the pointer that is being deallocated
		*/
		void Decrease(int size);
	private:
		int allocations_;
		int allocation_size_;
	};
}