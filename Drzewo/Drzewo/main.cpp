#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdlib.h>

namespace lib {

	struct X {};
	void f(X) { std::cout << "lib_f()" << std::endl; }
}

void f(lib::X) { std::cout << "global_f()" << std::endl; }

int main() {

	lib::X x;
	
	std::vector<int> v = { 1, 2, 1, 3, 1, 4 };
	std::remove(v.begin(), v.end(), 1);
	std::cout << v.size() << std::endl;
	

	system("PAUSE");
}