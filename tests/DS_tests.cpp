#include <stdlib.h>
/*
void testArray()
{
	WCHAR *as[100];
	for (auto &it : as)
		it = new WCHAR[2]{ L"H" };
	ArrayType<WCHAR*, 100> testarray(as);
	g_pRenderTarget->BeginDraw();
	g_pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));
	testarray.Draw();
	g_pRenderTarget->EndDraw();
}
*/
template<class T, size_t size>
class Stack
{
public:
	void pop();
	void push(T element);

//private:
	T data[size];
	size_t StackPoint = 0;
};

template<class T, size_t size>
void Stack<T, size>::pop()
{
	if (StackPoint > 0)
		StackPoint -= 1;
}

template<class T, size_t size>
void Stack<T, size>::push(T element)
{
	if (StackPoint < size)
		data[StackPoint++] = element;
}

////////////////////////////////////////
//ListType Node 

template<typename T>
class Node{
public:
	Node(T d) :data(d), next(nullptr), prev(nullptr) {}
	Node() :next(nullptr), prev(nullptr) {}
	T data;
	Node* next, *prev;
	int color = 1;
};

template<typename T>
void Insert(T head, T node)
{
	T p = head->prev;
	T n = head;
	p->next = node;
	n->prev = node;
	node->prev =p;
	node->next = n;
}

template<typename T>
void BuildTest(T & head)
{
	for (int i = 0; i < 20; ++i)
	{
		auto tmp = new T(i);
		Insert(&head, tmp);
	}
}

//////////////////////////////////////////
////Binary Tree

template<typename T>
class TreeNode {
public:
	TreeNode(T k) :key(k),left(nullptr), right(nullptr) {}
	T key;
	TreeNode *left, *right;
	int color = rand()%2;
};

template<typename T>
void BuildTree(T* &r, int depth) {
	if (depth <= 5) {
		r = new T(123);
		BuildTree(r->left, depth + 1);
		BuildTree(r->right, depth + 1);
	}
}