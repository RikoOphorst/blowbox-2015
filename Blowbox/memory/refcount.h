#pragma once

#include "../../blowbox/memory/allocated_memory.h"

namespace blowbox
{
	/**
	* @class blowbox::RefCount
	* @brief Keeps the count of references a pointer has
	* @author Riko Ophorst
	*/
	template<typename T>
	class RefCount
	{
	public:
		/**
		* @brief Default RefCount constructor
		*/
		RefCount() :
			references_(1),
			ptr_(nullptr)
		{

		}

		/**
		* @brief Default RefCount constructor with custom pointer
		*/
		RefCount(T* ptr) :
			references_(1)
		{
			ptr_ = ptr;
		}

		/**
		* @brief Default RefCount destructor
		*/
		~RefCount();

		/**
		* @brief Increases the refcount
		*/
		inline void Increase()
		{
			++references_;
		}

		/**
		* @brief Decreases the refcount and destroys if necessary
		*/
		inline void Decrease()
		{
			if (--references_ == 0)
				Destroy();
		}

		/**
		* @brief Destroys the pointer and decreases the allocated memory
		*/
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