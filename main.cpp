#include <iostream>
#include "QInt.h"

using namespace std;

int main(int argc, char* argv[]) {
	QInt myInt;
	cout << "nhap so QInt: ";
	cin >> myInt;
	cout << "hex: " << myInt.decToHex() << endl;
	system("pause");
	return 0;
}