#ifndef _LISTTYPE_
#define _LISTTYPE_
#include "Base.hpp"
#include "elements.hpp"
#include <memory>
#include <vector>
#include <cmath>
using namespace std;

constexpr float Node_Radius = 30.f;
constexpr float Node_Dis = 90.f;

/*
template <typename T>
class Node{
public:
    Node(T d):data(d), next(nullptr), prev(nullptr){}
    T data;
    Node *next, *prev;
};
*/

class VisualDSApp;

template <typename T>
class ListType;
template<template<typename> class N, typename T>
class ListType<N<T>>:public Base_DS
{
protected:
    size_t data_off,prev_off, next_off;
    N<T> *Head;
    T access_data(N<T> *node){
        return *reinterpret_cast<T*>(reinterpret_cast<char*>(node)+ data_off);
    }
    N<T>* next(N<T> *node)
    {
        return *reinterpret_cast<N<T>**>(reinterpret_cast<char*>(node) + next_off);
    }
    N<T> *prev(N<T> *node)
    {
        return *reinterpret_cast<N<T>**>(reinterpret_cast<char*>(node) + prev_off);
    }
	void set_offset(T *value, N<T>** Next, N<T>** Prev)
    {
        auto class_begin =min(min(reinterpret_cast<size_t>(value),
            reinterpret_cast<size_t>(Next)),
            reinterpret_cast<size_t>(Prev));
        data_off = reinterpret_cast<size_t>(value) - class_begin;
        next_off = reinterpret_cast<size_t>(Next) - class_begin;
        prev_off = reinterpret_cast<size_t>(Prev) - class_begin;
    }
public:
    ListType(VisualDSApp &a,N<T> *H):app(a), Head(H){
		//constructList();
	}
	//ListType(N<T>* H) :Head(H) {}
	void constructList(T *value, N<T>** Next, N<T>** Prev);
	virtual void Draw() const;
	
private:
	const int MaxSize = 100;
	VisualDSApp &app;
	vector<unique_ptr<Circle>> nodes;
	vector<unique_ptr<Arrow>> arrows;
	void ChangeDirec(D2D1_POINT_2F &d);
	void ThrowError();
	int __size = 0;
};

template<typename T>
class BinaryTreeType;

template<template<typename> class N, typename T>
class BinaryTreeType<N<T>>:public ListType<N<T>>
{
public:
    BinaryTreeType(VisualDSApp &a, N<T> *r):app(a),ListType<N<T>>(a,r), root(r) {
		startX = app.GetSize().width / 2;
		startY = 50.f;
	}
    void set_offset(T *value, N<T>** left, N<T>** right){
        ListType<N<T>>::set_offset(value, right, left); 
    }
	void constructTree(T *value, N<T>** left, N<T>** right);
	virtual void Draw() const;

protected:
    N<T> *root;
    N<T> * Left(N<T> *node){
        return ListType<N<T>>::prev(node);
    }
    N<T>* Right(N<T> *node){
        return ListType<N<T>>::next(node);
    }

	void BuildTree(N<T>* T, D2D1_POINT_2F &p, int depth);
	void ComputeHeight(N<T> *T, int depth);

private:
	using ListType<N<T>>::access_data;
	const int MaxHeight = 6;
	float startX, startY;
	int Height = 1;
	VisualDSApp &app;
	vector<unique_ptr<Circle>> nodes;
	vector<unique_ptr<Arrow>> arrows;
};

///////////////////////////////////////////////////

template<template<typename> class N, typename T>
inline void ListType<N<T>>::Draw() const
{
	for (auto &it : nodes)
		it.get()->Draw();
	for (auto &it : arrows)
		it.get()->Draw();
}

template<template<typename> class N, typename T>
inline void ListType<N<T>>::ChangeDirec(D2D1_POINT_2F & d)
{
	static int prev = 0;
	if (d.x > 0)
	{
		d.y = d.x;
		d.x = 0;
	}
	else if (d.x < 0)
	{
		d.y = -d.x;
		d.x = 0;
	}
	else if (prev == 0)
	{
		d.x = -d.y;
		d.y = 0;
		prev = 1;
	}
	else
	{
		d.x = d.y;
		d.y = 0;
		prev = 0;
	}
}

template<template <typename> class N, typename T>
inline void ListType<N<T>>::ThrowError()
{
	//app.ThrowError();
	//TODO
}

template<template<typename> class N, typename T>
inline void ListType<N<T>>::constructList(T *value, N<T>** Next, N<T>** Prev)
{
	set_offset(value, Next, Prev);
	D2D1_POINT_2F NowPoint = D2D1::Point2F(startX, startY);
	D2D1_POINT_2F NowDirec = D2D1::Point2F(Node_Dis, 0);
	Circle * pr = nullptr;
	auto pp = Head;
	auto p = Head;
	int Rev = 1;
	int flag = 1;
	do {
		__size++;
		if (__size > MaxSize)
		{
			ThrowError();
			return;
		}
		auto NowCircle = app.NewCircle(
			NowPoint.x,
			NowPoint.y,
			Node_Radius,
			access_data(p),
			RED
		);
		if (nodes.size() != 0)
		{
			pr = nodes.back().get();
			auto r = app.NewArrow();
			r->CreateArrow(pr, NowCircle);
			arrows.push_back(std::move(unique_ptr<Arrow>(r)));
			if (pp == prev(p)) {
				auto rr = app.NewArrow();
				rr->CreateArrow(NowCircle, pr);
				arrows.push_back(std::move(unique_ptr<Arrow>(rr)));
			}
			pp = p;
		}
		//Add arrow
		nodes.push_back(std::move(unique_ptr<Circle>(NowCircle)));
		if (flag == -1)
		{
			flag = -flag;
			ChangeDirec(NowDirec);
		}
		else if (NowPoint.x + NowDirec.x + Node_Radius > app.GetSize().width ||
			NowPoint.x + NowDirec.x - Node_Radius < 0)
		{
			flag = -flag;
			ChangeDirec(NowDirec);
		}
		NowPoint.x += NowDirec.x;
		NowPoint.y += NowDirec.y;
		//check boundary
		p = next(p);
	} while (p != Head);


	auto NowCircle = app.NewCircle(
		NowPoint.x,
		NowPoint.y,
		Node_Radius,
		"HEAD",
		RED
	);
	pr = nodes.back().get();
	auto r = app.NewArrow();
	r->CreateArrow(pr, NowCircle);
	arrows.push_back(std::move(unique_ptr<Arrow>(r)));
	if (pp == prev(p)) {
		auto rr = app.NewArrow();
		rr->CreateArrow(NowCircle, pr);
		arrows.push_back(std::move(unique_ptr<Arrow>(rr)));
	}
	nodes.push_back(std::move(unique_ptr<Circle>(NowCircle)));
	//Head again.
}


//////////////////////////////////////////////////////

template<template<typename> class N, typename T>
inline void BinaryTreeType<N<T>>::constructTree(T * value, N<T>** left, N<T>** right)
{
	set_offset(value, left, right);
	D2D1_POINT_2F NowPoint = D2D1::Point2F(startX, startY);
	ComputeHeight(root, 1);
	BuildTree(root, NowPoint, 1);
}

template<template<typename> class N, typename T>
inline void BinaryTreeType<N<T>>::Draw() const
{
	for (auto &it : nodes)
		it.get()->Draw();
	for (auto &it : arrows)
		it.get()->Draw();
}

template<template<typename> class N, typename T>
inline void BinaryTreeType<N<T>>::BuildTree(N<T>* T, D2D1_POINT_2F & p, int depth)
{
	if (T != nullptr && depth < MaxHeight)
	{
		auto NowCircle = app.NewCircle(
			p.x,
			p.y,
			Node_Radius,
			access_data(T),
			RED
		);
		nodes.push_back(std::move(unique_ptr<Circle>(NowCircle)));
	
		D2D1_POINT_2F NextLeft = D2D1::Point2F(p.x - ((pow(2,Height - depth - 2)) * Node_Dis),
			p.y + Node_Dis * sqrt(3.f));
		D2D1_POINT_2F NextRight = D2D1::Point2F(p.x + ((pow(2, Height - depth - 2)) * Node_Dis),
			p.y + Node_Dis * sqrt(3.f));
		if (Left(T) != nullptr)
		{
			auto r = app.NewArrow();
			r->CreateArrow(p, NextLeft, Node_Radius);
			arrows.push_back(std::move(unique_ptr<Arrow>(r)));
		}
		if (Right(T) != nullptr)
		{
			auto r = app.NewArrow();
			r->CreateArrow(p, NextRight, Node_Radius);
			arrows.push_back(std::move(unique_ptr<Arrow>(r)));
		}
		BuildTree(Left(T), NextLeft, depth + 1);
		BuildTree(Right(T), NextRight, depth + 1);
	}
}

template<template<typename> class N, typename T>
inline void BinaryTreeType<N<T>>::ComputeHeight(N<T>* T, int depth)
{
	if (T != nullptr)
	{
		Height = depth > Height ? depth : Height;
		ComputeHeight(Left(T), depth + 1);
		ComputeHeight(Right(T), depth + 1);
	}
}

#endif // !_LISTTYPE_
