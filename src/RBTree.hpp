#ifndef _RB_TREE_H
#define _RB_TREE_H

#include "ListType.hpp"
#include "App.hpp"

template<typename T>
class RBTree;

template<template<typename> class N, typename T>
class RBTree<N<T>> :public BinaryTreeType<N<T>>
{
public:
	RBTree(VisualDSApp &a, N<T>* r) :BinaryTreeType(a, r) {}
	template<typename _Tc>
	void set_offset(T *value, N<T>** left, N<T>** right, _Tc * color) {
		BinaryTreeType<N<T>>::set_offset(value, left, right);
		color_off = reinterpret_cast<size_t>(color)-min(reinterpret_cast<size_t>(value),
			min(reinterpret_cast<size_t>(left), 
			min(reinterpret_cast<size_t>(right), 
			reinterpret_cast<size_t>(color))));
	}
	template<typename _Tc>
	void constructTree(T *value, N<T>** Next, N<T>** Prev, _Tc *color) {
		set_offset(value, Next, Prev, color);
		D2D1_POINT_2F NowPoint = D2D1::Point2F(startX, startY);
		BinaryTreeType<N<T>>::ComputeHeight(root, 1);
		BinaryTreeType<N<T>>::BuildTree(root, NowPoint, 1);
	}
protected:

	virtual int access_color(N<T>* t) {
		return *reinterpret_cast<int*>(reinterpret_cast<char*>(t) + color_off);
	}
private:
	size_t color_off;
};

#endif // !_RB_TREE_H