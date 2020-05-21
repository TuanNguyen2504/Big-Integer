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

ostream& operator << (ostream& os, QInt myInt) {
	os << myInt.reduceBitSet(myInt._data);
	return os;
}

/* === Cac ham GET, SET === */
int QInt::getSize() const {
	return this->_data.size();
};
BITSET QInt::getData() const {
	return this->_data;
}
void QInt::setBit(const BITSET& bits) {
	this->_data = bits;
}

/* === NHOM HAM HO TRO === */
// ham rut gon chuoi bitset (vd: 0001010 -> 1010 )
string QInt::reduceBitSet(const BITSET& bin) {
	string bitsetToString = "";
	//chuyen sang chuoi string
	bitsetToString = bin.to_string<char, char_traits<char>, allocator<char> >();
	//tim vi tri cuoi cung cua bit 1
	short filnalPosOneBit = bitsetToString.find_first_of('1');
	if (filnalPosOneBit == string::npos) return "0";
	return bitsetToString.substr(filnalPosOneBit, bitsetToString.length());
}

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
//Ham chuyen chuoi so he 10 sang 2
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

//Ham chuyen chuoi so he 2 sang 16
string QInt::binToHex(const BITSET& bin) {
	string result = "";
	// day bit da duoc rut gon
	string bits = QInt::reduceBitSet(bin);
	// them vao cho du bo block 4 bits (vd: 11 -> 0011)
	while (bits.length() % 4 != 0){
		bits.insert(bits.begin(), '0');
	}
	//tach them tung bo
	for (int i = 0; i < bits.length(); i += 4) {
		string temp = bits.substr(i, 4);
		if (temp == "0000") result.push_back('0');
		else if (temp == "0001") result.push_back('1');
		else if (temp == "0010") result.push_back('2');
		else if (temp == "0011") result.push_back('3');
		else if (temp == "0100") result.push_back('4');
		else if (temp == "0101") result.push_back('5');
		else if (temp == "0110") result.push_back('6');
		else if (temp == "0111") result.push_back('7');
		else if (temp == "1000") result.push_back('8');
		else if (temp == "1001") result.push_back('9');
		else if (temp == "1010") result.push_back('A');
		else if (temp == "1011") result.push_back('B');
		else if (temp == "1100") result.push_back('C');
		else if (temp == "1101") result.push_back('D');
		else if (temp == "1110") result.push_back('E');
		else result.push_back('F');
	}
	return result;
}

//Ham chuyen chuoi so he 16 sang 2
BITSET QInt::hexToBin(const string& hex) {
	string bin = "";
	for (int i = 0; i < hex.length(); ++i) {
		switch (hex[i]) {
		case '0':
			bin += "0000";
			break;
		case '1':
			bin += "0001";
			break;
		case '2':
			bin += "0010";
			break;
		case '3':
			bin += "0011";
			break;
		case '4':
			bin += "0100";
			break;
		case '5':
			bin += "0101";
			break;
		case '6':
			bin += "0110";
			break;
		case '7':
			bin += "0111";
			break;
		case '8':
			bin += "1000";
			break;
		case '9':
			bin += "1001";
			break;
		case 'A': case 'a':
			bin += "1010";
			break;
		case 'B':
			bin += "1011";
			break;
		case 'C': case 'c':
			bin += "1100";
			break;
		case 'D': case 'd':
			bin += "1101";
			break;
		case 'E': case 'e':	
			bin += "1110";
			break;
		case 'F': case 'f':
			bin += "1111";
			break;
		default:
			break;
		}
	}
	BITSET result(bin);
	return result;
}

//Ham chuyen chuoi so he 10 sang 16
string QInt::decToHex() {
	return this->binToHex(this->_data);
}

/* === Cac operator === */
//operator=
QInt& QInt::operator = (const QInt& qInt) {
	this->_data = qInt._data;
	return *this;
}

//phep dich trai k bits
QInt QInt::operator<<(int k) const {
	if (k <= 0) return *this;
	QInt result;
	result._data = this->_data << k;
	return result;
}

//phep dich phai so hoc k bits
QInt QInt::operator >> (int k) const {
	if (k <= 0) return *this;
	QInt result;
	result._data = this->_data >> k;
	result._data[N_BIT - 1] = this->_data[N_BIT - 1];
	return result;
}

//operator +
QInt QInt::operator+(const QInt& a) {
	QInt result;
	bool bitSave = 0;

	for (int i = 0; i < N_BIT; ++i){
		int sum = this->_data[i] + a._data[i] + bitSave;
		if (sum == 2) {
			result._data.set(i, 0);
			bitSave = 1;
		}
		else if (sum >= 2) {
			result._data.set(i, 1);
			bitSave = 1;
		}
		else{
			result._data.set(i, sum);
			bitSave = 0;
		}
	}

	return result;
}

//operator -
QInt QInt::operator-(const QInt& a) {
	//neu a la so duong thi doi sang dang bu 2
	if (a._data.test(N_BIT - 1) == true) return *this + a;
	//ngc lai thi chuyen a thanh so am
	QInt temp;
	temp._data = QInt::complementTwo(a._data);

	return *this + temp;
}
//Ham huy
QInt::~QInt() {
}