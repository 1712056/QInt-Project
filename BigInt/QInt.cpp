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

string multiple2(string s)
{
	int temp = 0, carry = 0;;
	int _length = s.length();
	int a_size = _length + 1;
	int *a = new int[a_size];
	string result;
	for (int i = 0; i < a_size; i++)
		a[i] = 0;
	for (int i = _length - 1; i >= 0; i--)
	{
		temp = (s[i] - '0') * 2;
		if (carry == 1)
			temp++;
		if (temp > 9)
			carry = 1;
		else
			carry = 0;
		a[i + 1] += temp % 10;

	}
	if (carry == 1)
	{
		a[0] = 1;
	}
	else
	{
		for (int i = 0; i < a_size - 1; i++)
			a[i] = a[i + 1];
		a_size--;
	}
	for (int i = 0; i < a_size; i++)
	{
		result += (a[i] + '0');
	}
	return result;
}

string myPow(int n) //n là số mũ
{
	string temp = "2";
	if (n == 0)
		return "1";
	if (n == 1)
		return "2";
	for (int i = 0; i < n - 1; i++)
	{
		temp = multiple2(temp);
	}
	return temp;
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
	//Nhập một số lớn dạng chuỗi
	string s;
	unsigned int a[128] = { 0 };
	cout << "Nhap so: ";
	cin >> s;

	//Tiến hành đổi s sang dạng nhị phân lưu vào mảng a
	int i = 0;
	if (s[0] != '-' || s[0] == '+') //Số nhập vào là số dương
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
		a[127] = 0; //Bit dấu
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
		a[127] = 1; //Bit dấu

					// Đảo bit thành dạng bù 1
		for (int i = 0; i < 127; i++)
		{
			if (a[i] == 1)
			{
				a[i] = 0;
			}
			else
			{
				a[i] = 1;
			}
		}

		//Cộng 1 vào kết quả thành dạng bù 2
		for (int i = 0; i < 127; i++)
		{
			if (a[i] == 1)
			{
				a[i] = 0;
			}
			else
			{
				a[i] = 1;
				break;
			}
		}
	}

	// Bật các bit của data bằng cách OR với giá trị của mảng a tương ứng, bit dấu a[127]
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

//Hàm cộng 2 số dạng chuỗi
string plusNumInStr(string a, string b)
{
	string result; //biến chứa kết quả

	int i = a.length() - 1; 
	int j = b.length() - 1;
	int nho = 0;
	while (i >= 0 && j >= 0) //Vòng lặp cộng các chữ số ở cuối của a, b 
	{
		int temp = (a[i] - 48) + (b[j] - 48) +nho;
		char c = (temp % 10) + 48;
		if (temp > 9)
		{
			nho = 1;
		}
		else
			nho = 0;
		result += c;
		i--;
		j--;
	}
	
	// Trường hợp số a nhiều chữ số hơn
	while (i >= 0)
	{
		int temp = (a[i] - 48) + nho;
		char c = (temp % 10) + 48;
		if (temp > 9)
		{
			nho = 1;
		}
		else
			nho = 0;
		result += c;
		i--;
	}

	//Trường hợp số b nhiều chữ số hơn
	while (j >= 0)
	{
		int temp = (b[j] - 48) + nho;
		char c = (temp % 10) + 48;
		if (temp > 9)
		{
			nho = 1;
		}
		else
			nho = 0;
		result += c;
		j--;
	}

	// Nếu sau khi cộng xong mà vẫn còn nhớ 1 thì ghi thêm 1 vào kết quả
	if (nho == 1)
	{
		result += "1";
	}

	reverse(result.begin(), result.end()); //Vì kết quả lưu ngược nên phải đảo chuỗi cho đúng 
	return result;
}

void QInt::Xuat()
{
	unsigned int a[128] = { 0 };
	// Đọc các bit của data lưu vào mảng a, bit dấu là bit a[127]
	int d = 3, count = 0;
	for (int i = 0; i < 128; i++)
	{
		a[i] = 1 & (data[d] >> count);
		count++;
		if (count == 32)
		{
			count = 0;
			d--;
		}
	}
	
	
	string result="0";
	string temp;
	if (a[127] == 0) //Bit dấu = 0
	{
		for (int i = 0; i < 127; i++)
		{
			if (a[i] == 1)
			{
				temp = myPow(i);
				result = plusNumInStr(result, temp);
			}
		}
	}
	else //Bit dấu = 1
	{
		// Trừ 1 để thành dạng bù 1
		for (int i = 0; i < 127; i++)
		{
			if (a[i] == 0)
			{
				a[i] = 1;
			}
			else
			{
				a[i] = 0;
				break;
			}
		}
		// Đảo bit
		for (int i = 0; i < 127; i++)
		{
			if (a[i] == 1)
				a[i] = 0;
			else
				a[i] = 1;
		}

		for (int i = 0; i < 127; i++)
		{
			if (a[i] == 1)
			{
				temp = myPow(i);
				result = plusNumInStr(result, temp);
			}
		}
		reverse(result.begin(), result.end()); //Đảo chuỗi
		result += "-"; //Thêm dấu âm vào cuối chuỗi
		reverse(result.begin(), result.end()); //Đảo chuỗi cho đúng kết quả
	}
	cout << result;
}

QInt QInt::operator~()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			data[i] = data[i] ^ ( 1 << (32 - 1 - j) );
		}
	}
	return *this;
}

QInt QInt::operator|(QInt b)
{
	QInt result;
	for (int i = 3; i >=0; i--)
	{
		result.data[i] = data[i] | b.data[i];
	}
	return result;
}

QInt QInt::operator&(QInt b)
{
	QInt result;
	for (int i = 3; i >= 0; i--)
	{
		result.data[i] = data[i] & b.data[i];
	}
	return result;
}

QInt QInt::operator^(QInt b)
{
	QInt result;
	for (int i = 3; i >= 0; i--)
	{
		result.data[i] = data[i] ^ b.data[i];
	}
	return result;
}

QInt QInt::operator<<(int n)
{
	if (n < 0)
	{
		cout << "Loi";
		exit(0);
	}
	else if (n == 0)
	{
		return *this;
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			if (i == 3)
			{
				data[i] = data[i] << n;
			}
			else
			{
				data[i] = (data[i] << n) | (data[i + 1] >> (32 - n));
			}
		}
	}
	return *this;
}

QInt QInt::operator>>(int n)
{
	if (n < 0)
	{
		cout << "Loi";
		exit(0);
	}
	else
	{
		for (int i = 3; i >= 0; i--)
		{
			if (i == 0)
			{
				data[i] = data[i] >> n;
			}
			else
			{
				data[i] = (data[i] >> n) | (data[i - 1] << (32 - n));
			}
		}
	}
	return *this;
}

void QInt::rol()
{
	bool flag = true;
	if (((data[0] >> 128) & 1) != 1)
	{
		flag = 0;
	}
	*this << 1;
	if (flag == true)
	{
		data[3] = data[3] | 1;
	}
}

void QInt::ror()
{
	bool flag = 1;
	if ((data[3] & 1) == 0)
	{
		flag = 0;
	}
	*this >> 1;
	if (flag == 1)
	{
		data[0] == data[0] | (1 << 31);
	}
}


QInt::~QInt()
{
}
