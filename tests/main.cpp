#include "testHead.hpp"
#include "../src/App.hpp"
//#include "DS_tests.cpp"
#include "RBtest.cpp"
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR szCmdLine,
	int iCmdShow)
{
	VisualDSApp app(1200, 1600);
	/*
	auto s = new Stack<int, 10>;
	auto pS = app.NewStack<Stack<int, 10>, int, 10>(s->data);
	pS->push(5);
	app.OnRender();
	Sleep(2000);
	pS->push(6);
	*/
	/*
	auto head = new Node<int>(12345);
	head->next = head;
	head->prev = head;
	BuildTest(*head);
	
	auto pL = app.NewList(head);
	pL->constructList(&head->data, &head->next, &head->prev);
	*/
	/*
	TreeNode<int> *head;
	BuildTree(head, 1);
	*/
	LL_RB_Tree<int> test;
	for (int i = 1; i < 20; ++i)
		test.Insert(i, 0);
	auto head = test.root;
	auto pT = app.NewRBTree(head);
	pT->constructTree(&head->key, &head->left, &head->right, &head->color);
	
	app.OnRender();
	app.RunMessageLoop();
	return 0;
}