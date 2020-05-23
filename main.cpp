#include <iostream>
#include "QInt.h"
#include <fstream>
#include <vector>
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

//ham chuyen doi giua cac he co so
string baseConverter(const string& base1, const string& base2, string data) {
	//truong hop base1 = base2 -> khong lam gi
	if (base1 == base2) {
		if (base1 == BASE_2) {
			//xu ly case: 2->2 data = 0101 -> res: 101
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
		//2 -> 10 (chua co ham)
		if (base2 == BASE_10) {
			//return qi.binToDec();
			return "";
		}
		// 2 -> 16
		else
			return qi.binToHex(qi.getData());		
	}
	else if (base1 == BASE_10) {
		//10 -> 2
		if (base2 == BASE_2) 
			return qi.reduceBitSet(qi.getData());	
		//10 -> 16
		else
			return qi.decToHex();
	}
	else if (base1 == BASE_16) {
		//16 -> 2
		if (base2 == BASE_2) 
			return qi.reduceBitSet(qi.hexToBin(data));
		//16 -> 10 (chua co ham)
		else {
			//return qi.hexToDec(data);
			return "";
		}
	}
	return "";
}

//ham tinh toan toan tu 1 ngoi ~, ror, rol (DANG LAM)
string unaryOperatorsConverter(const string& base, const string& op) {
	string result = "";
	return result;
}

//ham tinh toan toan tu 2 ngoi +, -, *, /, >>, <<, &, |, ^ (DANG LAM)
string binaryOperatorsConverter(const string& base, const string& num1, const string& op, const string& num2) {
	string result = "";
	return result;
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
				outputData = unaryOperatorsConverter(base, op);
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
	cout << "so cau da lam: " << count << endl;
	in.close();
	out.close();
	return 1;
}

//HAM MAIN()
int main(int argc, char* argv[]) {
	string input = "input.txt";
	string output = "output.txt";
	//mainProcess(input, output);
	mainProcess(argv[1], argv[2]);
	system("pause");
	return 0;
}