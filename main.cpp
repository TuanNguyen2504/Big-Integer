#include <iostream>
#include "QInt.h"

using namespace std;

int main(int argc, char* argv[]) {
	QInt a;
	QInt b;
	cin >> a;
	cin >> b;
	cout << "a: " << a << endl;
	cout << "b: " << b << endl;
	cout << "a - b = " << a - b << endl;
	system("pause");
	return 0;
}