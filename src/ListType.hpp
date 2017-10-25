#ifndef _LISTTYPE_
#define _LISTTYPE_
#include "Base.hpp"
#include "elements.hpp"
#include <memory>
#include <vector>
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
	void constructList(T *value, N<T>** Next, N<T>** Prev);
	virtual void Draw() const;
	/*
    void walk()
    {
        N<T> *p =Head->prev->next;
        do
        {
            cout << access_data(p) << endl;
            p = next(p);
        } while(p != Head);
    }
	*/
private:
	VisualDSApp &app;
	vector<unique_ptr<Circle>> nodes;
	vector<unique_ptr<Arrow>> arrows;
	void ChangeDirec(D2D1_POINT_2F &d);
};

template<typename T>
class BinaryTreeType;

template<template<typename> class N, typename T>
class BinaryTreeType<N<T>>:public ListType<N<T>>
{
public:
    BinaryTreeType(N<T> *r):ListType<N<T>>(r), root(r) {}
    void set_offset(T *value, N<T>** left, N<T>** right){
        ListType<N<T>>::set_offset(value, right, left); 
    }
	/*
    void test(){
        cout << access_data(root) << endl;
        cout << "LEFT:" << access_data(Left(root)) << endl;
        cout << "RIGHT:" << access_data(Right(root)) << endl;
    }
	*/
protected:
    using ListType<N<T>>::access_data;
    N<T> *root;
    N<T> * Left(N<T> *node){
        return ListType<N<T>>::prev(node);
    }
    N<T>* Right(N<T> *node){
        return ListType<N<T>>::next(node);
    }
};


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
}

#endif // !_LISTTYPE_