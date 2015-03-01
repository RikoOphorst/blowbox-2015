#pragma once

#include "../../blowbox/memory/allocated_memory.h"
#include "../../blowbox/logging.h"
#include "../../blowbox/memory/refcount.h"

namespace blowbox
{	
	template<typename T>
	class SharedPtr
	{
	public:
		/**
		* @brief Default SharedPtr constructor
		*/
		SharedPtr();

		/**
		* @brief SharedPtr constructor with given pointer
		*/
		SharedPtr(T* ptr);

		/**
		* @brief SharedPtr copy constructor
		*/
		SharedPtr(const SharedPtr<T>& other);

		/**
		* @brief SharedPtr move constructor
		*/
		SharedPtr(SharedPtr<T>&& other);

		/**
		* @brief Default SharedPtr destructor
		*/
		~SharedPtr();

		/**
		* @brief Copy operator overload
		*/
		SharedPtr& operator=(const SharedPtr& other);

		/**
		* @brief Move operator overload
		*/
		SharedPtr& operator=(SharedPtr&& other);

		/**
		* @brief Pointer access operator overload
		*/
		T* operator->(void);

		/**
		* @brief Dereference operator overload
		*/
		T& operator*(void);

		bool operator==(const SharedPtr<T>& other) const;
		bool operator==(const T* other) const;
		bool operator==(std::nullptr_t) const;
		bool operator!=(const SharedPtr<T>& other) const;
		bool operator!=(const T* other) const;
		bool operator!=(std::nullptr_t) const;

		void Swap(SharedPtr<T>& other);
		void Reset();
		void Reset(T* ptr, RefCount<T>* ref);
		void ResetRaw(T* ptr, RefCount<T>* ref);

		T* get();
	private:
		T* ptr_;
		RefCount<T>* ref_;
	};

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	SharedPtr<T>::SharedPtr() : ref_(nullptr), ptr_(nullptr)
	{

	}

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	SharedPtr<T>::SharedPtr(const SharedPtr<T>& other) : ref_(nullptr), ptr_(nullptr)
	{
		Reset(other.ptr_, other.ref_);
	}

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	SharedPtr<T>::SharedPtr(SharedPtr<T>&& other) : ptr_(static_cast<T*>(other.ptr_)), ref_(other.ref_)
	{
		other.ptr_ = nullptr;
		other.ref_ = nullptr;
	}

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	SharedPtr<T>::SharedPtr(T* ptr)
	{
		
		ptr_ = ptr;
		ref_ = new RefCount<T>(ptr);
	}

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	SharedPtr<T>::~SharedPtr()
	{
		if (ref_ != nullptr)
			ref_->Decrease();
	}

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr& other)
	{
		SharedPtr<T>(other).Swap(*this);
		return this;
	}

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr&& other)
	{
		SharedPtr<T>(std::move(other)).Swap(*this);
		return *this;
	}

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	T* SharedPtr<T>::operator->(void)
	{
		
		return ptr_;
	}

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	T& SharedPtr<T>::operator*(void)
	{
		
		return *ptr_;
	}

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	bool SharedPtr<T>::operator==(const SharedPtr<T>& other) const
	{
		return other.get() == get();
	}

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	bool SharedPtr<T>::operator==(const T* other) const
	{
		
		return other == get();
	}

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	bool SharedPtr<T>::operator==(std::nullptr_t) const
	{
		return ptr_ == nullptr;
	}

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	bool SharedPtr<T>::operator!=(const SharedPtr<T>& other) const
	{
		return other.get() != get();
	}

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	bool SharedPtr<T>::operator!=(const T* other) const
	{
		
		return other != get();
	}

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	bool SharedPtr<T>::operator!=(std::nullptr_t) const
	{
		return ptr_ != nullptr;
	}

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	void SharedPtr<T>::Swap(SharedPtr<T>& right)
	{
		std::swap(ref_, right.ref_);
		std::swap(ptr_, right.ptr_);
	}

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	void SharedPtr<T>::Reset()
	{
		if (ref_ != nullptr)
			ref_->Increase();
		ResetRaw(ptr_, ref_);
	}

	//-------------------------------------------------------------------------------------------------
	template<typename T>
	void SharedPtr<T>::Reset(T* ptr, RefCount<T>* ref)
	{
		if (ref != nullptr)
			ref->Increase();
		ResetRaw(ptr, ref);
	}

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	void SharedPtr<T>::ResetRaw(T* ptr, RefCount<T>* ref)
	{
		if (ref_ != nullptr)
			ref_->Decrease();
		ptr_ = ptr;
		ref_ = ref;
	}

	//------------------------------------------------------------------------------------------------------
	template<typename T>
	T* SharedPtr<T>::get()
	{
		return ptr_;
	}
}