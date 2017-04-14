// Exaples

#include "Array.h"
#include <conio.h>

int main()
{
	Array<int> arr(Array<int>::Mode::Immutable, 17);


	for (int i(0); i < 15; i++)
		arr.append(i);

	for (int i(0); i < 15; i++)
		std::cout << arr[i] << std::endl;

	std::cout << "\n-----------------------------------------------------\n" << std::endl;

	arr.push_front(50);
	arr.push_front(30);
	arr.push_front(40);

	for (int i(0); i < arr.size(); i++)
		std::cout << arr[i] << std::endl;

	std::cout << "Length: " << arr.length() << std::endl;
	std::cout << "Size: " << arr.size() << std::endl;
	std::cout << "Empty? - " << (arr.isEmpty() ? "Yes!" : "No!") << std::endl;

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