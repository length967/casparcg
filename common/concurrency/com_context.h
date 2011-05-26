#pragma once

#include "executor.h"

#include <Windows.h>

#include <boost/noncopyable.hpp>

#include <functional>

namespace caspar {

template<typename T>
class com_context : public executor
{
	std::unique_ptr<T> instance_;
public:
	com_context(const std::wstring& name) : executor(name)
	{
		executor::begin_invoke([]
		{
			::CoInitialize(nullptr);
		});
	}

	~com_context()
	{
		executor::invoke([&]
		{
			instance_.reset(nullptr);
			::CoUninitialize();
		});
	}
	
	void reset(const std::function<T*()>& factory = nullptr)
	{
		executor::invoke([&]
		{
			instance_.reset();
			if(factory)
				instance_.reset(factory());
		});
	}

	T& operator*() const { return *instance_.get();}  // noexcept

	T* operator->() const { return instance_.get();}  // noexcept

	T* get() const { return instance_.get();}  // noexcept

	operator bool() const {return get() != nullptr;}
};

}