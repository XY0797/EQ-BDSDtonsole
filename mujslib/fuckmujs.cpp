#include <iostream>

int main(int argc, char** argv)
{
	char* utf8 = new char[4];
	utf8[0] = 56; utf8[1] = 56; utf8[2] = 56; utf8[3] = 0;
	const char* fuck = utf8;
	delete[] utf8;
	std::cout << fuck;
}