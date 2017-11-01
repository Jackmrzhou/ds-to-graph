# Visual DS

## Features

- [x] Convert Array into Graph.
- [x] Convert Stack(Array Implementaion) into Graph.
- [x] Convert Double Linked List into Graph.
- [x] Convert Binary Tree into Graph.
- [x] Convert Red Black Tree into Graph.


## Usage

```c++
#include "App.hpp"

template<typename T, size_t size>
class Stack{
public:
	T pop();
  	void push(T &v);
private:
  	T data[size];
};

int main()
{
  	app = VisualDSApp(600, 800);
  	//First Create a application, set the Height and the Width of the window.
  	int arr[10];
  	auto a = app.NewArray<int, 10>(arr);
  	//Create a array
  
  	auto s = new Stack<int, 10>;
  	using Sk = Stack<int, 10>;
  	auto pS = app.NewStack<Sk,int, 10>(s->data);
  	//Create a stack by app  
  	pS->push(10);
  	app.OnRender();
  	Sleep(1000);
  	pS->pop();
  	app.OnRender();
  	//use the new stack(pS) to call stack operations, and it will impact you own stack,too.
	
	auto pL = app.NewList(head);
  	//create a double linked-list 
	pL->constructList(&head->data, &head->next, &head->prev);
	//call pL->constructList, and pass three parameters: the address of data, next, and prev.
  	//then all is done, you can call app.OnRender() to see the result.
  
	auto pT = app.NewTree(head);
	pT->constructTree(&head->key, &head->left, &head->right);
  	//similar to double linked-list type.
  	auto pT = app.NewRBTree(head);
  	pT->constructTree(&head->key, &head->left, &head->right, &head->color);
  	//the color type must be bool or int.
    return 0;
}
```

## Environment Requirement

* Windows Only. Because this project is base on Direct2D. Which means you have to make sure there is Direct2D on your computer.(It seems that win10 don't have to worry about this.)
* Build succeed on VS2017, and I don't gurantee it will be successfully complied by other compliers.

## Some screenshots

![Binary Tree](https://github.com/Jackmrzhou/ds-to-graph/blob/master/s1.png?raw=true)

![Double Linked List](https://github.com/Jackmrzhou/ds-to-graph/blob/master/s2.png?raw=true)

![Red Black Tree](https://github.com/Jackmrzhou/ds-to-graph/blob/master/s3.png?raw=true)