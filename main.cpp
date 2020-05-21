#include <iostream>
#include "QInt.h"

using namespace std;

int main(int argc, char* argv[]) {
	QInt myInt;
	cin >> myInt;
	cout << "truoc khi dich trai: " << myInt << endl;
	QInt myInt2 = myInt >> 1;
	cout << "sau khi dich trai: " << myInt2 << endl;
	bitset<8> a("11101110");
	a = a >> 1;
	a[7] = 1;
	cout << "a: " << a << endl;
	system("pause");
	return 0;
}