#include "QInt.h"

/* === Cac ham khoi tao so QInt === */
QInt::QInt() {
	this->_data.reset();
}

//ham tao sao chep
QInt::QInt(const QInt& qi){
	this->_data = qi._data;
}

//ham tao tu chuoi bitset
QInt::QInt(const BITSET& bits) {
	this->_data = bits;
}

//khoi tao tu mot chuoi 2, 10, 16
QInt::QInt(const string& data, const string& base) {
	if (base == BASE_2) {
		int n = data.length();
		if (n > N_BIT) n = N_BIT;
		for (int i = 0; i < n; ++i) {
			if (data[n - i - 1] == '1')
				this->_data.set(i);
		}
	}
	else if (base == BASE_10) {
		BITSET bin = QInt::decToBin(data);
		this->_data = bin;
	}
	else if(base == BASE_16) {
		BITSET bin = QInt::hexToBin(data);
		this->_data = bin;
	}	
}

/* === Cac ham nhap xuat so QInt === */
istream& operator>> (istream& is, QInt& myInt) {
	string decInt;
	getline(is, decInt);
	BITSET bin = myInt.decToBin(decInt);
	myInt._data = bin;
	return is;
}

ostream& operator<< (ostream& os, QInt myInt) {
	os << myInt.binToDec(myInt.getData());
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

//ham nhan doi chuoi, ho tro ham binToDec
string QInt::mulByTwo(string src, int add) {
	string res = "";
	int store = add;

	for (int i = src.length() - 1; i >= 0; --i) {
		int temp = src[i] - '0';
		temp = temp * 2 + store;
		res += (temp % 10 + '0');
		store = temp / 10;
	}

	if (store > 0)
		res += (store + '0');

	reverse(res.begin(), res.end());

	return res;
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
	QInt result(bin, BASE_2);
	//neu so am, chuyen dang bu 2
	if (sign) 
		return this->complementTwo(result._data);

	return result._data;
}

//Ham chuyen chuoi so he 10 sang 16
string QInt::decToHex() {
	return this->binToHex(this->_data);
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

//Ham chuyen doi he so 2 sang 10
string QInt::binToDec(const BITSET& bin) {
	string result = "";
	// Gan bin cho bien tam
	BITSET bintemp = bin;
	bool negative = false;

	// Neu day bit la so am thi dua ve so duong roi them dau vao sau
	if (bin[N_BIT - 1] == 1) {
		bintemp = QInt::complementTwo(bin);
		negative = true;
	}

	// Day bit da duoc rut gon
	string binStr = QInt::reduceBitSet(bintemp);

	// Neu day bit == "0" thi tra ket qua
	if (binStr == "0") {
		result = "0";
		return result;
	}

	// Tim vi tri bit 1 dau tien + 1
	int pos = binStr.find('1', 0) + 1;
	result = "1";

	//tinh toan
	while (pos < binStr.length()) {
		int add = binStr[pos] - '0';
		result = mulByTwo(result, add);
		pos++;
	}

	//them dau vao ket qua
	if (negative)
		result = "-" + result;

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

//Ham chuyen doi he co 16 sang 10
string QInt::hexToDec(const string& hex) {
	BITSET bin = QInt::hexToBin(hex);
	return QInt::binToDec(bin);
}

/* === Cac operator === */
//operator=
QInt& QInt::operator= (const QInt& qInt) {
	this->_data = qInt._data;
	return (*this);
}

//phep dich trai k bits
QInt QInt::operator<< (int k) const {
	if (k <= 0) return *this;
	QInt result;
	result._data = this->_data << k;
	return result;
}

//phep dich phai so hoc k bits
QInt QInt::operator>> (int k) const {
	if (k <= 0) return *this;
	QInt result;
	//dich bit logic
	result._data = this->_data >> k;
	//neu bit trai nhat la 1 tien hanh dich bit so hoc (doi bit 0 thanh 1 o cac vi tri dich)
	if (this->_data[N_BIT - 1] == 1) {
		for (int i = 0; i < k; ++i) {
			result._data.set(N_BIT - 1 - i, 1);
		}
	}
	return result;
}

//operator +
QInt QInt::operator+ (const QInt& a) {
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
QInt QInt::operator- (const QInt& a) {
	QInt temp(a);
	//doi dau cho a vd: 1 - 2 = 1 + (-2) hay 1 - (-2) = 1 + 2 
	temp.setBit(QInt::complementTwo(temp._data));
	return *this + temp;
}

//operator*
QInt QInt::operator* (const QInt& a) {
	//kiem tra bit cuoi cua a
	//neu la 1 thi cong (*this) vao result, roi dich trai 1 bit (<< 1)
	//neu la 0 thi chi dich trai 1 bit (<< 1), vi luc nay cong bit 0 vao result
	QInt result;
	for (int i = 0; i < a.getSize(); ++i) {
		if (a._data[i] == 1) {	//kiem tra bit cuoi cua a		
			result = result + (*this);
		}
		(*this) = (*this) << 1;
	}
	return result;
}

/*=== Cac toan tu AND(&) OR(|) XOR(^) NOT(~) ===*/
//toan tu AND(&)
QInt QInt::operator& (const QInt& a) {
	BITSET res = this->_data & a._data;
	QInt result(res);
	return result;
}

//toan tu OR(|)
QInt QInt::operator| (const QInt& a) {
	BITSET res = this->_data | a._data;
	QInt result(res);
	return result;
}

//toan tu XOR(^)
QInt QInt::operator^ (const QInt& a) {
	BITSET res = this->_data ^ a._data;
	QInt result(res);
	return result;
}

//toan tu NOT(~)
QInt QInt::operator~ () const {
	BITSET res = ~this->_data;
	QInt result(res);
	return result;
}

/* === Cac phep xoay bit === */

//phep xoay trai 1 bit (chua xu ly tran so)
QInt QInt::rol() {
	QInt result(*this);
	//dich toan bo day bit sang trai
	result = result << 1;
	//bit trai nhat thanh bit phai nhat
	result._data[0] = this->_data[N_BIT - 1];
	return result;
}

//phep xoay phai 1 bit (chua xu ly tran so)
QInt QInt::ror() {
	QInt result(*this);
	//dich toan bo day bit sang phai
	result = result >> 1;
	//bit phai nhat thanh bit trai nhat
	result._data[N_BIT - 1] = this->_data[0];
	return result;
}

//Ham huy
QInt::~QInt() {
}