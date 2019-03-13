#pragma once
#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

class QInt
{
private:
	unsigned int data[4];
public:
	QInt();
	~QInt();
	void Nhap();
	void Xuat();
};

string chia2(string s);
