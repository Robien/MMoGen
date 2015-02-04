/*
 * shared_ptr.h
 *
 *  Created on: 13 janv. 2015
 *      Author: rguyard
 */

#ifndef ANDROID_AUTO_PROJECTION_PROTOCOL_CORE_UTIL_SHARED_PTR_H
#define ANDROID_AUTO_PROJECTION_PROTOCOL_CORE_UTIL_SHARED_PTR_H

#ifdef __QNXNTO__
#include <atomic.h>
#endif

#include <stdint.h>
#include <cstddef>

#include <iostream>

/**
 * A partial implementation of a shared pointer. This implementation only
 * has the methods that we need and so is a subset of std::shared_ptr.
 *
 * TODO: Customize this to work on your platform.
 */

template<typename T> class shared_ptr
{
public:
	shared_ptr() :
			mRefcount(NULL), mPtr(NULL)
	{
	}
	/**
	 * Lets the shared_ptr own this block of memory.
	 */
	shared_ptr(T* raw)
	{
		mPtr = raw;
		mRefcount = new unsigned int;
		*mRefcount = 1;
	}
	/**
	 * Copy constructors share ownership. The newly constructed object
	 * gains a ref and the old object keeps its ref too.
	 */
	shared_ptr(const shared_ptr<T>& other)
	{
		mPtr = other.mPtr;
		mRefcount = other.mRefcount;
		// Allow construction from another NULL shared pointer.
		if (mRefcount != NULL)
		{
			getRef();
		}
	}
	/**
	 * This is a copy assignment. If you copy-assign to an already populated
	 * shared pointer, the ref on the existing block of memory is dropped and
	 * the pointer is forgotten.
	 */
	void operator=(const shared_ptr<T>& other)
	{
		if (mRefcount != NULL)
		{
			putRef();
		}
		mPtr = other.mPtr;
		mRefcount = other.mRefcount;
		// Allow for assigning a NULL shared_ptr to another shared_ptr.
		if (mRefcount != NULL)
		{
			getRef();
		}
	}
	/**
	 * Pointer dereference operator that allows this:
	 * shared_ptr<Foo> foo(new Foo());
	 * foo->bar();
	 */
	T* operator->() const
	{
		return mPtr;
	}
	/**
	 * Test if the owned pointer is the same as a raw pointer.
	 */
	bool operator==(T* raw)
	{
		return mPtr == raw;
	}
	/**
	 * Test if owned pointer is not the same as a raw pointer.
	 */
	bool operator!=(T* raw)
	{
		return mPtr != raw;
	}
	/**
	 * Drops the reference on the raw pointer. This may or may not delete
	 * the actual pointer, depending on the refcount.
	 */
	~shared_ptr()
	{
		if (mRefcount != NULL)
		{
			putRef();
		}
	}
	/**
	 * Get a handle to the raw pointer. Use with caution.
	 * @return The raw pointer.
	 */
	const T* get() const
	{
		return mPtr;
	}
private:
	void getRef()
	{
#ifdef __QNXNTO__
		atomic_add_value(mRefcount, 1);
#else
		__sync_add_and_fetch(mRefcount, 1);
#endif
	}

	void putRef()
	{
#ifdef __QNXNTO__
		if (atomic_sub_value(mRefcount, 1) == 1)
		{
#else
		if (__sync_add_and_fetch(mRefcount, -1) == 0)
		{
#endif
			delete mPtr;
			mPtr = NULL;
			delete mRefcount;
			mRefcount = NULL;
		}
	}

	volatile unsigned int* mRefcount;
	T* mPtr;
};

#endif // ANDROID_AUTO_PROJECTION_PROTOCOL_CORE_UTIL_SHARED_PTR_H
