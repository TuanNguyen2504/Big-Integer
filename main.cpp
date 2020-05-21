#include <iostream>
#include "QInt.h"

using namespace std;

int main(int argc, char* argv[]) {
	QInt myInt;
	cout << "nhap so QInt: ";
	cin >> myInt;
	cout << "bin: " << myInt << endl;
	cout << "data: " << myInt.getData() << endl;
	string hex = myInt.binToHex(myInt.getData());
	cout << "hex: " << hex << endl;
	cout << "hex to bin: " << myInt.reduceBitSet(myInt.hexToBin(hex)) << endl;
	system("pause");
	return 0;
}