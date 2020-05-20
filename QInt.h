#pragma once
#ifndef _QINT_
#define _QINT_

#include <iostream>
#include <string>
#include <Windows.h>
#include <bitset>

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
	friend ostream& operator << (ostream& os, const QInt& myInt);

	/* === Cac ham GET, SET === */
	int getSize() const;

	/* === Cac ham convert === */
	BITSET decToBin(string decInt);
	//string binToHex();

	/* === Cac operator === */
	//operator=
	QInt& operator = (const QInt& qInt);

	/* === NHOM HAM HO TRO === */
	string divStrByTwo(const string& decInt);
	BITSET complementTwo(BITSET bin);
	//ham huy
	~QInt();
};

#endif // !_QINT_

