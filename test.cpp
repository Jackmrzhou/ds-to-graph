#include <iostream>
#include "init.hpp"
using namespace std;

int main()
{
	auto window = InitWindow(800, 600);
	system("pause");
	Cleanup();
	return 0;
}