// BigInt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "QInt.h"

using namespace std;

int main()
{
	QInt a;
	QInt b;
	a.Nhap();
	b.Nhap();
	QInt c;
	c = a - b;
	c.Xuat();
}