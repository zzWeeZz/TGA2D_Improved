#pragma once
#include "CallableWrappers.hpp"

template <typename Ret, typename... Args>
class Delegate<Ret(Args...)>
{
	friend class Signal<Ret(Args...)>;
public:
	Delegate() : myCallableWrapper(nullptr) {}
	Delegate(const Delegate& aOther) = delete;
	Delegate(Delegate&& aOther) : myCallableWrapper(aOther.myCallableWrapper);

	Delegate& operator=(Delegate const& other) = delete;
	Delegate& operator=(Delegate&& aOther)
	{
		Delegate temp(std::move(aOther));
		std::swap(temp);

		return *this;
	}

	~Delegate()
	{
		delete myCallableWrapper;
		myCallableWrapper = nullptr;
	}

	template<typename T>
	void Bind(T &aInstance, Ret(T::*aPtrToMemFunc)(Args...))
	{
		myCallableWrapper = new MemoryFunctionCallableWrapper<Ret(Args...)>(aInstance, aPtrToMemFunc);
	}

	template<typename T>
	void Bind(T &aInstance, Ret(T::* aPtrToMemFunc)(Args...) const)
	{
		myCallableWrapper = new ConstMemoryFunctionCallableWrapper<T, Ret(Args...)>(aInstance, aPtrToMemFunc);
	}

	explicit operator bool() const { return myCallableWrapper != nullptr; }

	Ret operator()(Args...aArgs)
	{
		return myCallableWrapper->Invoke(std::forward<Args>(aArgs)...);
	}

	Ret Invoke(Args... aArgs)
	{
		return myCallableWrapper->Invoke(std::forward<Args>(aArgs)...);
	}

private:
	CallableWrapper<Ret(Args...)>* myCallableWrapper;
};