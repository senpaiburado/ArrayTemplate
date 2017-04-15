// Examples

#include "Array.h"
#include <conio.h>

int main()
{
	Array<int> arr;


	for (int i(0); i < 15; i++)
		arr.append(i);

	for (int i(0); i < 15; i++)
		std::cout << arr[i] << std::endl;

	std::cout << "\n-----------------------------------------------------\n" << std::endl;

	arr.insert(0, 100);

	for (int i(0); i < arr.size(); i++)
		std::cout << arr[i] << std::endl;

	std::cout << "Length: " << arr.length() << std::endl;
	std::cout << "Size: " << arr.size() << std::endl;
	std::cout << "Empty? - " << (arr.isEmpty() ? "Yes!" : "No!") << std::endl;
	std::cout << "First - " << arr.front() << " || Last - " << arr.back() << std::endl;

	//arr.resize(15);

	std::cout << "\n-----------------------------------------------------\n" << std::endl;

	//arr[5] = 10;

	for (int i(0); i < arr.length(); i++)
		std::cout << arr[i] << std::endl;

	std::cout << "Length: " << arr.length() << std::endl;
	std::cout << "Size: " << arr.size() << std::endl;
	std::cout << "Empty? - " << (arr.isEmpty() ? "Yes!" : "No!") << std::endl;
	_getch();
	return 0;
}