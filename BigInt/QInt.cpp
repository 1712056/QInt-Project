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
	while (s != "0")
	{
		//Xét số cuối cùng của chuỗi, nếu là số chẵn khi chia 2 sẽ dư 0 
		if ((s[s.length() - 1] - 48) % 2 == 0)  
		{
			a[i++] = 0;
		}
		//Nếu là số âm, chia 2 sẽ dư 1
		else
		{
			a[i++] = 1;
		}

		//Chia chuỗi s cho 2
		s = chia2(s);

	};


	// Bật các bit của data bằng cách OR với giá trị của mảng a tương ứng
	int count = 0;
	int d = 0;
	int temp = 0;
	
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
string PlusBigInt(string a, string b)
{
	if (a.length() < b.length())
	{
		string s = a;
		a = b;
		b = s;
	}
	string result;
	for (int i = 0; i < a.length() + 1; i++)
	{
		result += "0";
	}
	bool remember = false;
	for (int i = 0; i < b.length(); i++)
	{
		int temp = b[b.length() - i - 1] - '0' + a[a.length() - i - 1] - '0';

		if (remember)
			temp++;

		if (temp > 9)
			remember = true;
		else
			remember = false;

		temp = temp % 10;

		result[a.length() - i] = temp + '0';
	}
	for (int i = 0; i < a.length() - b.length(); i++)
	{
		int temp = a[a.length() - b.length() - i - 1] - '0';

		if (remember)
			temp++;
		if (temp > 9)
			remember = true;
		else
			remember = false;

		temp = temp % 10;

		result[a.length() - b.length() - i] = temp + '0';
	}

	result[a.length() + 1] = '\0';

	if (remember)
	{
		result[0] = '1';
	}
	else
	{
		for (int i = 0; i <= a.length(); i++)
			result[i] = result[i + 1];
	}
	return result;
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
