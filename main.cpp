// Examples

#include "Array.h"
#include <conio.h>
#include <random>
#include <time.h>
#include <algorithm>

using namespace std;

int main()
{
	srand(time(NULL));
	Array<int> arr;
	Array<int> arr2;
	vector<int> vec;

	for (int i(160); i >= 0; i -= 5)
	{
		arr.append(i);
		vec.push_back(i);
	}
	for (int i(0); i < 180; i += 5)
	{
		arr2.append(i);
	}

	_getch();
	return 0;
}