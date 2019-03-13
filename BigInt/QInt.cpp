#include "stdafx.h"
#include "QInt.h"


string chia2(string s)
{
	string temp;
	int divisor = 0;
	if (s.length() == 1)
	{
		divisor = s[0] - 48;
		temp += (divisor / 2) + 48;
	}
	else
	{
		int i = 0;
		divisor = s[0] - 48;
		for (int i = 0; i < s.length() - 1; i++)
		{
			if (divisor < 2)
			{
				i++;
				divisor = (divisor * 10) + (s[i] - 48);
			}
			char c = (divisor / 2) + 48;
			temp += c;
			divisor = divisor % 2;
			i--;
		}
	}
	s = temp;
	return s;

}


QInt::QInt()
{
	data[0] = 0;
	data[1] = 0;
	data[2] = 0;
	data[3] = 0;
}

void QInt::Nhap()
{
	//Nhập một số lớn dạn chuỗi
	string s;
	unsigned int a[128] = { 0 };
	cout << "Nhap so: ";
	cin >> s;

	//Tiến hành đổi s sang dạng nhị phân lưu vào mảng a
	int i = 0;
	if (s[0] != '-' || s[0]=='+') //Số nhập vào là số dương
	{
		while (s != "0")
		{
			//Xét số cuối cùng của chuỗi, nếu là số chẵn khi chia 2 sẽ dư 0 
			if ((s[s.length() - 1] - 48) % 2 == 0)
			{
				a[i++] = 0;
			}
			//Nếu là số lẻ, chia 2 sẽ dư 1
			else
			{
				a[i++] = 1;
			}

			//Chia chuỗi s cho 2
			s = chia2(s);
			if (i > 126)
			{
				throw "Stack Overflow";
			}

		};
		a[127] = 0;
	}

	else //Số nhập vào là số âm
	{
		string positive_s;
		for (int i = 1; i < s.length(); i++) //Lấy phần sau dấu âm của số
		{
			positive_s += s[i];
		}
		while (positive_s != "0")
		{
			//Xét số cuối cùng của chuỗi, nếu là số chẵn khi chia 2 sẽ dư 0 
			if ((positive_s[positive_s.length() - 1] - 48) % 2 == 0)
			{
				a[i++] = 0;
			}
			//Nếu là số lẻ, chia 2 sẽ dư 1
			else
			{
				a[i++] = 1;
			}

			//Chia chuỗi s cho 2
			positive_s = chia2(positive_s);
			if (i > 126)
			{
				throw "Stack Overflow";
			}

		};
		a[127] = 1;

	}

	// Bật các bit của data bằng cách OR với giá trị của mảng a tương ứng
	int count = 0;
	int d = 0;
	for (int i = 127; i >= 0; i--)
	{
		data[d] = data[d] | (a[i] << (32 - 1 - count));
		count++;
		if (count == 32)
		{
			count = 0;
			d++;
		}
	}
}

void QInt::Xuat()
{
	for (int i = 0; i < 4; i++)
	{
		cout << data[i];
	}

}

QInt::~QInt()
{
}
