#pragma once
#ifndef __STACKTYPE__
#define __STACKTYPE__
#include "ArrayType.hpp"
#include <memory>
#include "Base.hpp"
#include "defines.hpp"
using namespace std;
template<class _Tc,typename T, size_t Stack_Size>
class StackType:public Base_DS, public _Tc
	//use array to simulate stack
{
public:
	StackType(VisualDSApp &a, unique_ptr<ArrayType<T, Stack_Size>> &uni_ptr);

	virtual void Draw() const;
	virtual void pop();
	virtual void push(T && element);

private:
	unique_ptr<ArrayType<T, Stack_Size>> stack;
	size_t StackPoint = 0;
};


template<class _Tc,typename T, size_t Stack_Size>
inline StackType<_Tc, T, Stack_Size>::StackType(VisualDSApp & a, 
	unique_ptr<ArrayType<T, Stack_Size>> &uni_ptr)
	:stack(std::move(uni_ptr))
{
	for (auto index = StackPoint; index < Stack_Size; ++index)
	{
		(*stack).SetColor(index, WHITE);
		(*stack).SetValue(index, "UnInit");
	}
}
template<class _Tc, typename T, size_t Stack_Size>
inline void StackType<_Tc, T, Stack_Size>::Draw() const
{
	(*stack).Draw();
}
template<class _Tc, typename T, size_t Stack_Size>
inline void StackType<_Tc, T, Stack_Size>::pop()
{
	if (StackPoint > 0)
	{
		StackPoint -= 1;
		(*stack).SetColor(StackPoint, WHITE);
	}
	else
		return;
	_Tc::pop();
}
template<class _Tc, typename T, size_t Stack_Size>
inline void StackType<_Tc, T, Stack_Size>::push(T && element)
{
	if (StackPoint < Stack_Size)
	{
		(*stack).SetColor(StackPoint, RED);
		(*stack).SetValue(StackPoint, element);
		StackPoint += 1;
	}
	else
		return;
	_Tc::push(std::move(element));
}
#endif // !__STACKTYPE__