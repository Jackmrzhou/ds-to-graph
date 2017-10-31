#include <iostream>
#include <fstream>
#include <random>

using namespace std;
using _color_type = bool;
constexpr _color_type Red = true;
constexpr _color_type Black = false;
template<typename T>
class Node
{
public:
	Node(int k, const T &v) : key(k), value(v), left(nullptr), right(nullptr), color(Red) {}
	//new nodes are always red
	int key;
	//integer key for demo
	T value;
	Node<T> *left, *right;
	_color_type color;
};
template <typename T>
class LL_RB_Tree
{
public:
	LL_RB_Tree() :root(nullptr) {}
	void Insert(int key, const T &value) {
		root = Insert(root, key, value);
		root->color = Black;
	}
	// void inorder_print(){
	//     inorder_print(root);
	// }
	// void inorder_print(Node<T> *x){
	//     if (x != nullptr)
	//     {
	//         inorder_print(x->left);
	//         cout << x->key << ": "<<x->value<<", ";
	//         inorder_print(x->right);
	//     }
	// }
	void pre()
	{
		pre(root);
	}

	void pre(Node<T> *t) {
		if (t != nullptr)
		{
			if (t->color == Black)
				std::cout << t->key << ' ';
			else
				std::cout << '-' << t->key << ' ';
			pre(t->left);
			pre(t->right);
		}
	}
	void pre(ofstream &f, Node<T> *t) {
		if (t != nullptr) {
			if (t->color == Black)
				f << t->key << ' ';
			else
				f << '-' << t->key << ' ';
			pre(f, t->left);
			pre(f, t->right);
		}
	}

	void shuffle_pre(ofstream &f, Node<T> *t) {
		if (t != nullptr) {
			if (rand() % 2)
				f << t->key << ' ';
			else
				f << '-' << t->key << ' ';
			pre(f, t->left);
			pre(f, t->right);
		}
	}
	void write_into_file(int IsShuffle) {
		ofstream file;
		file.open("test_data", ios::app);
		if (IsShuffle == 0)
			pre(file, root);
		else
			shuffle_pre(file, root);
		file << '\n';
		file.close();
	}
private:
	Node<T>* Insert(Node<T> *h, int key, const T &value);
	void colorFilp(Node<T> *h) {
		h->color = !h->color;
		h->left->color = !h->left->color;
		h->right->color = !h->right->color;
	}
	Node<T> *leftRotate(Node<T> *h);
	Node<T> *rightRotate(Node<T> *h);
	bool isRed(Node<T> *h);
public:
	Node<T> *root;
};

template<typename T>
bool LL_RB_Tree<T>::isRed(Node<T> *h)
{
	if (h == nullptr)
		return false;
	else
		return h->color == Red;
}

template<typename T>
Node<T> *LL_RB_Tree<T>::rightRotate(Node<T> *h) {
	auto x = h->left;
	h->left = x->right;
	x->right = h;
	x->color = h->color;
	h->color = Red;
	return x;
}

template<typename T>
Node<T> *LL_RB_Tree<T>::leftRotate(Node<T> *h) {
	auto x = h->right;
	h->right = x->left;
	x->left = h;
	x->color = h->color;
	h->color = Red;
	return x;
}

template<typename T>
Node<T>* LL_RB_Tree<T>::Insert(Node<T> *h, int key, const T &value)
{
	if (h == nullptr)
		return new Node<T>(key, value);
	if (isRed(h->left) && isRed(h->right))
		colorFilp(h);
	if (key < h->key)
		h->left = Insert(h->left, key, value);
	else if (key > h->key)
		h->right = Insert(h->right, key, value);
	else
		h->value = value;
	if (!isRed(h->left) && isRed(h->right))
		h = leftRotate(h);
	if (isRed(h->left) && h->left != nullptr && isRed(h->left->left))
		h = rightRotate(h);
	return h;
}

