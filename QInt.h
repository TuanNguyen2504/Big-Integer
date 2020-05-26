#pragma once
#ifndef _QINT_
#define _QINT_

#include <iostream>
#include <string>
#include <Windows.h>
#include <bitset>
#include <map>

//bieu dien so QInt bao nhieu byte 16 byte = 128 bit 
#define N_BYTE 16
#define N_BIT N_BYTE*8
#define BITSET bitset<N_BIT>
#define BASE_2 "2"
#define BASE_10 "10"
#define BASE_16 "16"
#define ROL "rol"
#define ROR "ror"
using namespace std;

class QInt
{
private:
	/*
		- Su dung bitset de bieu dien nhi phan cua so 16 byte
			+ Do duoc ho tro nhieu, khong ton nhieu bo nho nhu char
	*/
	BITSET _data;
public:
	/* === Cac ham khoi tao so QInt === */
	QInt();
	//ham tao tu chuoi bitset
	QInt(const BITSET& bits);
	//khoi tao tu mot chuoi 2, 10, 16
	QInt(const string& bin, const string& base);
	//ham tao sao chep
	QInt(const QInt& qi);

	/* === Cac ham nhap xuat so QInt === */
	friend istream& operator >> (istream& is, QInt& myInt);
	friend ostream& operator << (ostream& os, QInt myInt);

	/* === Cac ham GET, SET === */
	int getSize() const;
	BITSET getData() const;
	void setBit(const BITSET& bits);

	/* === Cac ham convert === */
	//Ham chuyen chuoi so he 10 sang 2
	BITSET decToBin(string decInt);
	//Ham chuyen chuoi so he 2 sang 16
	string binToHex(const BITSET& bin);
	//Ham chuyen chuoi so he 16 sang 2
	BITSET hexToBin(const string& hex);
	//Ham chuyen chuoi so he QInt sang 16
	string decToHex();
	//Ham chuyen doi he 2 sang 10
	string binToDec(const BITSET& bin);
	//Ham chuyen doi he 16 sang 10
	string hexToDec(const string& hex);

	/* === Cac operator === */
	//operator=
	QInt& operator= (const QInt& qInt);
	//phep dich trai k bit
	QInt operator<< (int k) const;
	//phep dich phai so hoc k bit
	QInt operator>> (int k) const;
	//operator+
	QInt operator+ (const QInt& a);
	//operator-
	QInt operator- (const QInt& a);
	//operator*
	QInt operator* (const QInt& a);
	//operator/
	QInt operator/ (QInt a);

	/* === Cac toan tu AND(&) OR(|) XOR(^) NOT(~) === */
	//toan tu AND(&)
	QInt operator& (const QInt& a);
	//toan tu OR(|)
	QInt operator| (const QInt& a);
	//toan tu XOR(^)
	QInt operator^ (const QInt& a);
	//toan tu NOT(~)
	QInt operator~ () const;

	/* === Cac phep xoay bit === */
	//phep xoay trai 1 bit (chua xu ly tran so)
	QInt rol();
	//phep xoay phai 1 bit (chua xu ly tran so)
	QInt ror();

	/* === NHOM HAM HO TRO === */
	//ham rut gon chuoi bitset (vd: 0001010 -> 1010 )
	string reduceBitSet(const BITSET& bin);
	//ham chia 1 chuoi cho 2
	string divStrByTwo(const string& decInt);
	//ham chuyen day nhi phan sang bu 2
	BITSET complementTwo(BITSET bin);
	//ham nhan doi chuoi, ho tro ham binToDec
	string mulByTwo(string src, int additive);

	//ham huy
	~QInt();
};

#endif // !_QINT_

