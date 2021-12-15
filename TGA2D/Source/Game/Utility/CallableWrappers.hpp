#pragma once
#ifndef CALLABLE_WRAPPER_H
#define CALLABLE_WRAPPER_H

template<typename Type>
class CallableWrapper;

template<typename Ret, typename...Args>
class CallableWrapper<Ret(Args...)>
{
public:
	virtual Ret Invoke(Args...aArgs) = 0;

	virtual ~CallableWrapper() = default;
protected:
	CallableWrapper() = default;
};

//___________________________ Memory Function Editable _____________________//

template<typename ClassT, typename Type>
class MemoryFunctionCallableWrapper;

template <typename ClassT, typename Func, typename...Args>
class MemoryFunctionCallableWrapper<ClassT, Func(Args...)> : public CallableWrapper<Func(Args...)>
{
private:
	using PtrToMemoryFunction = Func(ClassT::*)(Args...);
public:
	MemoryFunctionCallableWrapper(ClassT& aInstance, PtrToMemoryFunction aPtrToMemoryFunction) : myInstance(aInstance), myPtrToMemoryFunction(PtrToMemoryFunction) {}

	Func Invoke(Args...aArgs) override
	{
		return (myInstance.*myPtrToMemoryFunction)(std::forward<Args>(aArgs)...);
	}
private:
	ClassT& myInstance;
	PtrToMemoryFunction myPtrToMemoryFunction;
};


//___________________________ Const Memory Function _____________________//

template<typename  ClassT, typename Type>
class ConstMemoryFunctionCallableWrapper;

template<typename ClassT, typename Func, typename ...Args>
class ConstMemoryFunctionCallableWrapper<ClassT, Func(Args...)> : public CallableWrapper<Func(Args...)>
{
private:
	using PtrToConstMemoryFunction = Func(ClassT::*)(Args...) const;
public:
	ConstMemoryFunctionCallableWrapper(ClassT& aInstance, PtrToMemoryFunction aPtrToMemoryFunction) : myInstance(aInstance), myPtrToConstMemoryFunction(PtrToConstMemoryFunction) {}

	Func Invoke(Args...aArgs) override
	{
		return (myInstance.*myPtrToConstMemoryFunction)(std::forward<Args>(aArgs)...);
	}
private:
	ClassT& myInstance;
	PtrToConstMemoryFunction myPtrToConstMemoryFunction;
};

//___________________________ Function  _____________________//

template<typename ClassT, typename Func, typename...Args>
class FunctionObjectCallableWrapper;

template<typename ClassT, typename Func, typename ...Args>
class FunctionObjectCallableWrapper<ClassT, Func(Args...)> : public CallableWrapper<ClassT, Func(Args...)>
{
public:
	FunctionObjectCallableWrapper(ClassT &functionObject) : myFunctionObject(&functionObject), myAllocated(false){}
	FunctionObjectCallableWrapper(ClassT &&functionObject) : myFunctionObject(new ClassT(std::move(functionObject)), myAllocated(true)) {}

	Func Invoke(Args...aArgs)
	{
		return (*myFunctionObject)(std::forward<Args>(aArgs)...); 
	}

private:
	template <typename U = ClassT, typename = std::enable_if<std::is_function<U>::value>>
	void Destroy();
	template <typename = ClassT, typename U = ClassT, typename = std::enable_if<!std::is_function<U>::value>>
	void Destroy() { if (myAllocated) delete myFunctionObject; }

	ClassT* myFunctionObject;
	bool myAllocated;
};

#endif
