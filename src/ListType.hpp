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
inline void ListType<N<T>>::constructList(T *value, N<T>** Next, N<T>** Prev)
{
	set_offset(value, Next, Prev);
	D2D1_POINT_2F NowPoint = D2D1::Point2F(startX, startY);
	Circle * prev = nullptr;
	auto p = Head;
	do {
		//TODO: Check Boundary
		auto NowCircle = app.NewCircle(
			NowPoint.x,
			NowPoint.y,
			Node_Radius,
			access_data(p),
			RED
		);
		if (nodes.size() != 0)
		{
			prev = nodes.back().get();
			auto r = app.NewArrow();
			r->CreateArrow(prev, NowCircle);
			arrows.push_back(std::move(unique_ptr<Arrow>(r)));
		}
		nodes.push_back(std::move(unique_ptr<Circle>(NowCircle)));
		NowPoint.x += Node_Dis;
		p = next(p);
	} while (p != Head);
}

#endif // !_LISTTYPE_