#include <iostream>
#include "QInt.h"
#include <fstream>
#include <vector>
#include <sstream>

//gia tri tra ve mac dinh khi bi tran so, div/0, ngoai le khac
#define RETURN_WHEN_OVERFLOWED ""

using namespace std;

//ham kiem tra ky tu phai he co so
bool isBase(const string& data) {
	return (data == BASE_2 || data == BASE_10 || data == BASE_16);
}

//Ham xu ly, tach chuoi
vector<string> tokenData(const string& data) {
	vector<string> result;
	string tokenData = "";
	for (int i = 0; i < data.length(); ++i) {
		if (data[i] == ' ') {
			result.push_back(tokenData);
			tokenData = "";
		}
		else {
			tokenData.push_back(data[i]);
		}
	}
	if (tokenData != "") result.push_back(tokenData);
	return result;
}

//ham chuyen doi QInt sang 1 he bat ky (dung de xuat so QInt ra 1 dinh dang base)
string qintToBase(QInt qi, const string& base) {
	if (base == BASE_2)
		return qi.reduceBitSet(qi.getData());
	else if (base == BASE_10) {
		return qi.binToDec(qi.getData());
	}
	else if (base == BASE_16)
		return qi.binToHex(qi.getData());
	return RETURN_WHEN_OVERFLOWED;
}

//ham chuyen doi giua cac he co so
string baseConverter(const string& base1, const string& base2, string data) {
	//truong hop base1 = base2 -> khong lam gi
	if (base1 == base2) {
		if (base1 == BASE_2) {
			//xu ly case: 2->2 data = 0101 -> result: 101
			BITSET bin(data);
			QInt qi;
			return qi.reduceBitSet(bin);
		}
		return data;
	}
	
	//khoi tao QInt
	QInt qi(data, base1);
	//he 2 -> he khac
	if (base1 == BASE_2) {
		//2 -> 10
		if (base2 == BASE_10) {
			return qi.binToDec(qi.getData());
		}
		// 2 -> 16
		else
			return qi.binToHex(qi.getData());		
	}
	//he 10 -> he khac
	else if (base1 == BASE_10) {
		//10 -> 2
		if (base2 == BASE_2) 
			return qi.reduceBitSet(qi.getData());	
		//10 -> 16
		else
			return qi.decToHex();
	}
	//he 16 -> he khac
	else if (base1 == BASE_16) {
		//16 -> 2
		if (base2 == BASE_2) 
			return qi.reduceBitSet(qi.hexToBin(data));
		//16 -> 10 (chua co ham)
		else 
			return qi.hexToDec(data);
	}

	//truong hop k hop le
	return RETURN_WHEN_OVERFLOWED;
}

//ham tinh toan toan tu 1 ngoi ~, ror, rol
string unaryOperatorsConverter(const string& base, const string& op, const string& num) {
	QInt qi(num, base);
	QInt result;
	if (op == ROL) {
		result = qi.rol();
	}
	else if (op == ROR) {
		result = qi.ror();
	}
	else if (op == "~") {
		result = ~qi;
	}
	return qintToBase(result, base);
}

//ham tinh toan toan tu 2 ngoi +, -, *, /, >>, <<, &, |, ^
string binaryOperatorsConverter(const string& base, const string& num1, const string& op, const string& num2) {
	QInt result;
	//case op la >> <<
	if (op == "<<" || op == ">>") {
		//chuyen num2 sang int
		int k = 0;
		stringstream strToInt(num2);
		strToInt >> k;
		//tinh toan
		QInt qi(num1, base);
		if (op == "<<")
			result = qi << k;
		else
			result = qi >> k;
	}
	//cac truong hop con lai
	else {
		QInt a(num1, base), b(num2, base);
		if (op == "+")
			result = a + b;
		else if (op == "-")
			result = a - b;
		else if (op == "*")
			result = a * b;
		else if (op == "/") {
			//truong hop b = 0 -> div/0
			if (b.getData() == 0)
				return RETURN_WHEN_OVERFLOWED;
			result = a / b;
		}
		else if (op == "&")
			result = a & b;
		else if (op == "|")
			result = a | b;
		else if (op == "^")
			result = a ^ b;
	}	
	
	// tra ket qua theo he so base
	return qintToBase(result, base);
}

//ham xu ly chinh, se duoc viet lai o ham main sau
bool mainProcess(const string& input, const string& output) {
	int count = 0;
	ifstream in(input);
	ofstream out(output);

	if (in.fail() || out.fail()) {
		cerr << "\n Loi mo file" << endl;
		return 0;
	}
	
	string data;
	string outputData = "";
	//doc, xu ly du lieu
	while (1) {
		//doc du lieu theo dong
		getline(in, data);
		if (in.eof()) break;

		//du lieu da duoc token
		vector<string> datas = tokenData(data);
		int size = datas.size();

		//he co so thu 1, bat buoc co
		string base = datas[0];

		// === CAC CASE === //
		//truong hop chuyen he co so, ~, rol, ror
		if (size == 3) {
			//truong hop chuyen he co so
			if (isBase(datas[1]) == true) {
				//he co so thu 2
				string base2 = datas[1];
				outputData = baseConverter(base, base2, datas[2]);
			}
			// truong hop toan tu 1 ngoi ~, rol, ror
			else {
				//operator
				string op = datas[1];
				outputData = unaryOperatorsConverter(base, op, datas[2]);
			}
		}
		//truong hop toan tu 2 ngoi +, -, *, /, >>, <<, OR, AND, XOR
		else if (size == 4) {
			string num1 = datas[1], op = datas[2], num2 = datas[3];
			outputData = binaryOperatorsConverter(base, num1, op, num2);
		}

		//xuat output ra file
		if (outputData != "") ++count;
		out << outputData << endl;
	}

	in.close();
	out.close();
	return 1;
}

// HAM MAIN()
int main(int argc, char* argv[]) {
	if (argc >= 3) {
		mainProcess(argv[1], argv[2]);
	}
	system("pause");
	return 0;
}
