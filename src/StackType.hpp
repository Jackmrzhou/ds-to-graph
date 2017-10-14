#pragma once
#ifndef __STACKTYPE__
#define __STACKTYPE__
#include "ArrayType.hpp"
#include <memory>
#include "Base.hpp"
#include "defines.hpp"
using namespace std;
template<typename T, size_t Stack_Size>
class StackType:public Base_DS
	//use array to simulate stack
{
public:
	StackType(VisualDSApp &a, unique_ptr<ArrayType<T, Stack_Size>> &uni_ptr);

	virtual void Draw() const;
	void pop();

private:
	unique_ptr<ArrayType<T, Stack_Size>> stack;
	size_t StackPoint = Stack_Size;
};


template<typename T, size_t Stack_Size>
inline StackType<T, Stack_Size>::StackType(VisualDSApp & a, 
	unique_ptr<ArrayType<T, Stack_Size>> &uni_ptr)
	:stack(std::move(uni_ptr))
{
}
template<typename T, size_t Stack_Size>
inline void StackType<T, Stack_Size>::Draw() const
{
	(*stack).Draw();
}
template<typename T, size_t Stack_Size>
inline void StackType<T, Stack_Size>::pop()
{
	StackPoint -= 1;
	(*stack).SetColor(StackPoint, WHITE);
}
#endif // !__STACKTYPE__