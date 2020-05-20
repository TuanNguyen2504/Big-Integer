#include "QInt.h"

/* === Cac ham khoi tao so QInt === */
QInt::QInt() {
	this->_data.reset();
}

//khoi tao tu mot chuoi nhi phan
QInt::QInt(const string& bin) {
	int n = bin.length();
	if (n > N_BIT) n = N_BIT;
	for (int i = 0; i < n ; ++i) {
		if(bin[n - i - 1] == '1')
			this->_data.set(i);
	}
}

/* === Cac ham nhap xuat so QInt === */
istream& operator >> (istream& is, QInt& myInt) {
	string decInt;
	getline(is, decInt);
	BITSET bin = myInt.decToBin(decInt);
	myInt._data = bin;
	return is;
}

ostream& operator << (ostream& os, const QInt& myInt) {
	string bitsetToString = "";
	//chuyen sang chuoi string
	bitsetToString = myInt._data.to_string<char, char_traits<char>, allocator<char> >();
	//tim vi tri cuoi cung cua bit 1
	short filnalPosOneBit = bitsetToString.find_first_of('1');
	os << bitsetToString.substr(filnalPosOneBit, bitsetToString.length());
	return os;
}

/* === Cac ham GET, SET === */
int QInt::getSize() const {
	return this->_data.size();
};

/* === NHOM HAM HO TRO === */
//Ham chia mot chuoi so cho 2
string QInt::divStrByTwo(const string& decInt) {
	string result = "";
	int temp = 0;

	for (int i = 0; i < decInt.size(); ++i) {
		temp = temp * 10 + (decInt[i] - '0');
		if (i > 0 || (i == 0 && temp >= 2))
			result += ((temp / 2) + '0');
		temp %= 2;
	}

	return result;
}
// Ham chuyen nhi phan sang bu 2
BITSET QInt::complementTwo(BITSET bin) {
	//dao chuoi
	bin.flip();
	//cong 1 vao day bit vua dao
	if (!bin[0]) bin.set(0, 1);
	else {
		for (int i = 0; i < bin.size(); ++i) {
			if (!bin[i]) {
				bin.set(i, 1);
				return bin;
			}
			bin.set(i, 0);
		}
	}
	return bin;
}

/* === NHOM HAM COVERT === */
//Ham chuyen chuoi so thap phan sang nhi phan
BITSET QInt::decToBin(string decInt) {
	bool sign = false; //true -, false 
	string bin = "";
	//kiem tra so am
	if (decInt[0] == '-') {
		sign = true;
		decInt.erase(0, 1); //xoa dau - ra khoi chuoi
	}
	//chuyen sang nhi phan
	while (decInt != "") {
		bin += ((decInt[decInt.length() - 1] - '0') % 2) + '0'; //lay so cuoi chia lay bit 0 or 1
		decInt = divStrByTwo(decInt);
	}
	//dao nguoc chuoi bit
	reverse(bin.begin(), bin.end());
	QInt result(bin);
	//neu so am, chuyen dang bu 2
	if (sign) 
		return this->complementTwo(result._data);

	return result._data;
}

/* === Cac operator === */
//operator=
QInt& QInt::operator = (const QInt& qInt) {
	this->_data = qInt._data;
	return *this;
}


//Ham huy
QInt::~QInt() {
}