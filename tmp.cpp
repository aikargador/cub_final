#include <iostream>
using namespace std;

int main () {
	int	i;
	int	skey;
	int	array[] = {1, 2, 3, 4, 7};
	int size = sizeof(array) / sizeof(*array);

	cout << "enter the search key: ";
	cin >> skey;
	for (i = 0; i < size && skey != array[i]; i++);
	if (i < size)
		cout << "Element found" << endl;
	else
		cout << "Element not found" << endl;
}



