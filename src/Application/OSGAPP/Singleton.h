#pragma once
#include <assert.h>

template <typename T> class Singleton
{
private:
	/** @brief Explicit private copy constructor. This is a forbidden operation.*/
	Singleton(const Singleton<T> &);

	/** @brief Private operator= . This is a forbidden operation. */
	Singleton& operator=(const Singleton<T> &);

protected:
	static T* mSingleton;

public:
	Singleton(void)
	{
		assert(!mSingleton);
		mSingleton = static_cast<T*>(this);
	}
	
	virtual ~Singleton(void)
	{
		assert(mSingleton);  mSingleton = 0;
	}

	/// Get the singleton instance
	static T& getSingleton(void)
	{
		assert(mSingleton);  return (*mSingleton);
	}
	
	/// @copydoc getSingleton
	static T* getSingletonPtr(void)
	{
		return mSingleton;
	}
};

