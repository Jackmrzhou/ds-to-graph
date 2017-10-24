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
	auto tmp1 = new T(1234);
	auto tmp2 = new T(123);
	auto tmp3 = new T(12);
	Insert(&head, tmp1);
	Insert(&head, tmp2);
	Insert(&head, tmp3);
}
