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
	//khoi tao tu mot chuoi nhi phan
	QInt(const string& bin);

	/* === Cac ham nhap xuat so QInt === */
	friend istream& operator >> (istream& is, QInt& myInt);
	friend ostream& operator << (ostream& os, QInt myInt);

	/* === Cac ham GET, SET === */
	int getSize() const;
	BITSET getData() const;

	/* === Cac ham convert === */
	//Ham chuyen chuoi so he 10 sang 2
	BITSET decToBin(string decInt);
	//Ham chuyen chuoi so he 2 sang 16
	string binToHex(const BITSET& bin);
	//Ham chuyen chuoi so he 16 sang 2
	BITSET hexToBin(const string& hex);
	//Ham chuyen chuoi so he QInt sang 16
	string decToHex();

	/* === Cac operator === */
	//operator=
	QInt& operator = (const QInt& qInt);

	/* === NHOM HAM HO TRO === */
	// ham rut gon chuoi bitset (vd: 0001010 -> 1010 )
	string reduceBitSet(const BITSET& bin);
	//ham chia 1 chuoi cho 2
	string divStrByTwo(const string& decInt);
	//ham chuyen day nhi phan sang bu 2
	BITSET complementTwo(BITSET bin);

	//ham huy
	~QInt();
};

#endif // !_QINT_


