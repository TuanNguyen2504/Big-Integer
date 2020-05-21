#include <iostream>
#include "QInt.h"

using namespace std;

int main(int argc, char* argv[]) {
	QInt myInt;
	cout << "nhap so QInt: ";
	cin >> myInt;
	cout << "bin: " << myInt << endl;
	cout << "hex: " << myInt.binToHex(myInt.getData()) << endl;
	system("pause");
	return 0;
}