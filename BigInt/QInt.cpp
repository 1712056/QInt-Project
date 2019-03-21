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
	unsigned int a[128] = { 0 };
	string s;
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
	cout << result << endl;
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

void QInt::rol() //Quay trái
{
	bool flag = true;
	if (((data[0] >> 31) & 1) != 1)
	{
		flag = 0;
	}
	*this << 1;
	if (flag == true)
	{
		data[3] = data[3] | 1;
	}
}

void QInt::ror() //Quay phải
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

string QInt::decToBin()
{
	unsigned int a[128] = { 0 };
	// Ð?c các bit c?a data luu vào m?ng a, bit d?u là bit a[127]
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
	string result;
	for (int i = 127; i >= 0; i--)
	{
		result += (a[i] + '0');
	}
	return result;
}
QInt QInt::binToDec(string s)
{
	int count = 0;//d? qu?n lý s? bit c?a 1 ph?n t? ki?u QInt=32 bit
	int resultSize = 3;
	for (int i = s.length() - 1; i >= 0; i--)
	{
		data[resultSize] = data[resultSize] | ((s[i] - '0') << count);// b?t bit cho result
		count++;
		if (count == 32)
		{
			count = 0;
			resultSize--;
		}
	}
	return *this;
}
string QInt::binToHex(string s)
{
	// 10:A, 11:B, 12:C, 13:D, 14:E, 15:F
	string result;
	int *a = new int[s.length()];
	for (int i = 0; i < s.length(); i++)
	{
		a[i] = 0;
	}
	int size = 0;
	for (int i = s.length() - 1; i >= 0; i--)
	{
		a[size] = (s[i] - '0');
		size++;
	}
	int temp = 0;// bi?n nhóm 4 bit c?a chu?i nh? phân r?i chuy?n qua th?p l?c
	int value = 0;
	for (int i = 0; i < 128; i++)
	{
		if (a[i] == 1 || a[i] == 0)
		{
			value += a[i] * pow(2, temp);
			temp++;
			if (temp == 4)
			{
				temp = 0;
				if (value < 9)
				{
					result += (value + '0');
					value = 0;
				}
				else
				{
					switch (value)
					{
					case 10:
						result += "A";
						break;
					case 11:
						result += "B";
						break;
					case 12:
						result += "C";
						break;
					case 13:
						result += "D";
						break;
					case 14:
						result += "E";
						break;
					case 15:
						result += "F";
						break;
					default:
						throw"overflow";
					}
					value = 0;
				}
			}
		}
	}
	reverse(result.begin(), result.end());
	delete[]a;
	return result;
}
string QInt::decToHex()
{
	unsigned int a[128] = { 0 };
	// Ð?c các bit c?a data luu vào m?ng a, bit d?u là bit a[127]
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
	string result;
	int temp = 0;// bi?n nhóm 4 bit c?a chu?i nh? phân r?i chuy?n qua th?p l?c
	int value = 0;
	for (int i = 0; i < 128; i++)
	{
		if (a[i] == 1 || a[i] == 0)
		{
			value += a[i] * pow(2, temp);
			temp++;
			if (temp == 4)
			{
				temp = 0;
				if (value <= 9)
				{
					result += (value + '0');
					value = 0;
				}
				else
				{
					switch (value)
					{
					case 10:
						result += "A";
						break;
					case 11:
						result += "B";
						break;
					case 12:
						result += "C";
						break;
					case 13:
						result += "D";
						break;
					case 14:
						result += "E";
						break;
					case 15:
						result += "F";
						break;
					default:
						throw"overflow";
						break;
					}
					value = 0;
				}
			}
		}
	}
	reverse(result.begin(), result.end());
	return result;
}

//operator +
QInt QInt::operator+(QInt B)
{
	unsigned int a1[128] = { 0 };
	// Ð?c các bit c?a data luu vào m?ng a1, bit d?u là bit a1[127]
	int d1 = 3, count1 = 0;
	for (int i = 0; i < 128; i++)
	{
		a1[i] = 1 & (data[d1] >> count1);
		count1++;
		if (count1 == 32)
		{
			count1 = 0;
			d1--;
		}
	}
	unsigned int a2[128] = { 0 };
	// Ð?c các bit c?a data luu vào m?ng a2, bit d?u là bit a2[127]
	int d2 = 3, count2 = 0;
	for (int i = 0; i < 128; i++)
	{
		a2[i] = 1 & (B.data[d2] >> count2);
		count2++;
		if (count2 == 32)
		{
			count2 = 0;
			d2--;
		}
	}
	unsigned int a3[128] = { 0 };
	int remember = 0;//bi?n nh?
	//TH1: 2 s? cùng duong ho?c cùng âm
	if (a1[127] == a2[127])
	{
		for (int i = 0; i < 127; i++)
		{
			if (a1[i] == 1 || a2[i] == 1)
			{
				if (a1[i] == a2[i])
				{
					if (remember == 1)
						a3[i] = 1;
					else
					{
						a3[i] = 0;
						remember = 1;
					}
				}
				else
				{
					if (remember == 1)
						a3[i] = 0;
					else
					{
						a3[i] = 1;
						remember = 0;
					}
				}
			}
			else
			{
				if (remember == 1)
				{
					a3[i] = 1;
					remember = 0;
				}
				else
					a3[i] = 0;
			}
		}
		if (remember == 1)
		{
			if (a1[127] == 1)//TH bit d?u âm
				a3[127] = 1;
			else//TH bit d?u duong
				throw "Stack Overflow";
		}
	}
	//TH2: 1 s? duong 1 s? âm
	else
	{
		for (int i = 0; i < 127; i++)
		{
			if (a1[i] == 1 || a2[i] == 1)
			{
				if (a1[i] == a2[i])
				{
					if (remember == 1)
						a3[i] = 1;
					else
					{
						a3[i] = 0;
						remember = 1;
					}
				}
				else
				{
					if (remember == 1)
						a3[i] = 0;
					else
					{
						a3[i] = 1;
						remember = 0;
					}
				}
			}
			else
			{
				if (remember == 1)
				{
					a3[i] = 1;
					remember = 0;
				}
				else
					a3[i] = 0;
			}
		}
		//Xét xem các ph?n t? có b?ng 0 hay không, n?u = 0 thì bit d?u = 0 ngu?c l?i = 1
		for (int i = 0; i < 127; i++)
		{
			if (a3[i] == 0)
			{
				a3[127] = 0;
			}
			else
			{
				a3[127] = 1;
				break;
			}
		}
		if (remember == 1)
			a3[127] = 0;
	}
	//Luu k?t qu? vào 1 l?p riêng
	QInt C;
	int count, d;
	d = count = 0;
	for (int i = 127; i >= 0; i--)
	{
		C.data[d] = C.data[d] | (a3[i] << (32 - 1 - count));
		count++;
		if (count == 32)
		{
			count = 0;
			d++;
		}
	}
	return C;
}
//operator -
QInt QInt::operator-(QInt B)
{
	unsigned int a1[128] = { 0 };
	// Ð?c các bit c?a data luu vào m?ng a1, bit d?u là bit a1[127]
	int d1 = 3, count1 = 0;
	for (int i = 0; i < 128; i++)
	{
		a1[i] = 1 & (data[d1] >> count1);
		count1++;
		if (count1 == 32)
		{
			count1 = 0;
			d1--;
		}
	}
	unsigned int a2[128] = { 0 };
	// Ð?c các bit c?a data luu vào m?ng a2, bit d?u là bit a2[127]
	int d2 = 3, count2 = 0;
	for (int i = 0; i < 128; i++)
	{
		a2[i] = 1 & (B.data[d2] >> count2);
		count2++;
		if (count2 == 32)
		{
			count2 = 0;
			d2--;
		}
	}
	unsigned int a3[128] = { 0 };
	//TH1: s? th? 2 là s? duong
	if (a2[127] == 0)
	{
		// Ð?o bit thành d?ng bù 1
		for (int i = 0; i < 127; i++)
		{
			if (a2[i] == 1)
			{
				a2[i] = 0;
			}
			else
			{
				a2[i] = 1;
			}
		}
		//C?ng 1 vào k?t qu? thành d?ng bù 2
		for (int i = 0; i < 127; i++)
		{
			if (a2[i] == 1)
			{
				a2[i] = 0;
			}
			else
			{
				a2[i] = 1;
				break;
			}
		}
		a2[127] = 1;// s? th? 2 tr? thành s? âm
		int remember = 0;//bi?n nh?
		//TH1: 2 s? cùng âm c?ng l?i
		if (a1[127] == a2[127])
		{
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 1 || a2[i] == 1)
				{
					if (a1[i] == a2[i])
					{
						if (remember == 1)
							a3[i] = 1;
						else
						{
							a3[i] = 0;
							remember = 1;
						}
					}
					else
					{
						if (remember == 1)
							a3[i] = 0;
						else
						{
							a3[i] = 1;
							remember = 0;
						}
					}
				}
				else
				{
					if (remember == 1)
					{
						a3[i] = 1;
						remember = 0;
					}
					else
						a3[i] = 0;
				}
			}
			if (remember == 1)
			{
				if (a1[127] == 1)//TH bit d?u âm
					a3[127] = 1;
				else//TH bit d?u duong
					throw "Stack Overflow";
			}
		}
		//TH2: s? th? 1 duong, s? th?  2 âm
		else
		{
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 1 || a2[i] == 1)
				{
					if (a1[i] == a2[i])
					{
						if (remember == 1)
							a3[i] = 1;
						else
						{
							a3[i] = 0;
							remember = 1;
						}
					}
					else
					{
						if (remember == 1)
							a3[i] = 0;
						else
						{
							a3[i] = 1;
							remember = 0;
						}
					}
				}
				else
				{
					if (remember == 1)
					{
						a3[i] = 1;
						remember = 0;
					}
					else
						a3[i] = 0;
				}
			}
			//Xét xem các ph?n t? có b?ng 0 hay không, n?u = 0 thì bit d?u = 0 ngu?c l?i = 1
			for (int i = 0; i < 127; i++)
			{
				if (a3[i] == 0)
				{
					a3[127] = 0;
				}
				else
				{
					a3[127] = 1;
					break;
				}
			}
			if (remember == 1)
				a3[127] = 0;
		}
	}
	//TH2: s? th? 2 là s? âm
	else
	{
		// Tr? 1 d? thành d?ng bù 1
		for (int i = 0; i < 127; i++)
		{
			if (a2[i] == 0)
			{
				a2[i] = 1;
			}
			else
			{
				a2[i] = 0;
				break;
			}
		}
		// Ð?o bit
		for (int i = 0; i < 127; i++)
		{
			if (a2[i] == 1)
				a2[i] = 0;
			else
				a2[i] = 1;
		}
		a2[127] = 0;// s? th? 2 tr? thành s? duong
		int remember = 0;//bi?n nh?
		//TH1: 2 s? cùng duong c?ng l?i
		if (a1[127] == a2[127])
		{
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 1 || a2[i] == 1)
				{
					if (a1[i] == a2[i])
					{
						if (remember == 1)
							a3[i] = 1;
						else
						{
							a3[i] = 0;
							remember = 1;
						}
					}
					else
					{
						if (remember == 1)
							a3[i] = 0;
						else
						{
							a3[i] = 1;
							remember = 0;
						}
					}
				}
				else
				{
					if (remember == 1)
					{
						a3[i] = 1;
						remember = 0;
					}
					else
						a3[i] = 0;
				}
			}
			if (remember == 1)
			{
				if (a1[127] == 1)//TH bit d?u âm
					a3[127] = 1;
				else//TH bit d?u duong
					throw "Stack Overflow";
			}
		}
		//TH2: s? th? 1 âm, s? th? 2 duong
		else
		{
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 1 || a2[i] == 1)
				{
					if (a1[i] == a2[i])
					{
						if (remember == 1)
							a3[i] = 1;
						else
						{
							a3[i] = 0;
							remember = 1;
						}
					}
					else
					{
						if (remember == 1)
							a3[i] = 0;
						else
						{
							a3[i] = 1;
							remember = 0;
						}
					}
				}
				else
				{
					if (remember == 1)
					{
						a3[i] = 1;
						remember = 0;
					}
					else
						a3[i] = 0;
				}
			}
			//Xét xem các ph?n t? có b?ng 0 hay không, n?u = 0 thì bit d?u = 0 ngu?c l?i = 1
			for (int i = 0; i < 127; i++)
			{
				if (a3[i] == 0)
				{
					a3[127] = 0;
				}
				else
				{
					a3[127] = 1;
					break;
				}
			}
			if (remember == 1)
				a3[127] = 0;
		}
	}
	QInt C;
	int count, d;
	d = count = 0;
	for (int i = 127; i >= 0; i--)
	{
		C.data[d] = C.data[d] | (a3[i] << (32 - 1 - count));
		count++;
		if (count == 32)
		{
			count = 0;
			d++;
		}
	}
	return C;
}
//so sanh lon hon
bool QInt::operator>(QInt B)
{
	unsigned int a1[128] = { 0 };
	// Ð?c các bit c?a data luu vào m?ng a1, bit d?u là bit a1[127]
	int d1 = 3, count1 = 0;
	for (int i = 0; i < 128; i++)
	{
		a1[i] = 1 & (data[d1] >> count1);
		count1++;
		if (count1 == 32)
		{
			count1 = 0;
			d1--;
		}
	}
	unsigned int a2[128] = { 0 };
	// Ð?c các bit c?a data luu vào m?ng a2, bit d?u là bit a2[127]
	int d2 = 3, count2 = 0;
	for (int i = 0; i < 128; i++)
	{
		a2[i] = 1 & (B.data[d2] >> count2);
		count2++;
		if (count2 == 32)
		{
			count2 = 0;
			d2--;
		}
	}
	unsigned int a3[128] = { 0 };
	//TH1: 2 s? khác d?u
	if (a1[127] != a2[127])
	{
		if (a1[127] == 0)
			return 1;
		else
			return 0;
	}
	//TH2: 2 s? cùng d?u
	else
	{
		string result1 = "0";
		string temp1;
		string result2 = "0";
		string temp2;
		//TH 2 s? cùng duong
		if (a1[127] == 0)
		{

			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 1)
				{
					temp1 = myPow(i);
					result1 = plusNumInStr(result1, temp1);
				}
			}
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 1)
				{
					temp2 = myPow(i);
					result2 = plusNumInStr(result2, temp2);
				}
			}
			if (result1.length() > result2.length())//a>b
				return 1;
			if (result1.length() < result2.length())//a<b
				return 0;
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] != a2[i])
					break;
				if (i == 126 && a1[i] == a2[i])//a==b
					return 0;
			}
			//s? th? 2 d?o bit thành d?ng bù 1
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 1)
				{
					a2[i] = 0;
				}
				else
				{
					a2[i] = 1;
				}
			}
			//C?ng 1 vào k?t qu? thành d?ng bù 2
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 1)
				{
					a2[i] = 0;
				}
				else
				{
					a2[i] = 1;
					break;
				}
			}
			a2[127] = 1;// s? th? 2 tr? thành s? âm
			int remember = 0;//bi?n nh?
			//l?y s? th? 1 c?ng s? th? 2
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 1 || a2[i] == 1)
				{
					if (a1[i] == a2[i])
					{
						if (remember == 1)
							a3[i] = 1;
						else
						{
							a3[i] = 0;
							remember = 1;
						}
					}
					else
					{
						if (remember == 1)
							a3[i] = 0;
						else
						{
							a3[i] = 1;
							remember = 0;
						}
					}
				}
				else
				{
					if (remember == 1)
					{
						a3[i] = 1;
						remember = 0;
					}
					else
						a3[i] = 0;
				}
			}
			a3[127] = 1;
			if (remember == 1)
				return 1;//a3[127]=0
			if (a3[127] == 1)//a-b ra s? âm
				return 0;
			else//a-b ra s? duong
				return 1;
		}
		//TH 2 s? cùng âm
		else
		{
			//s? th? 1
			// Tr? 1 d? thành d?ng bù 1
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 0)
				{
					a1[i] = 1;
				}
				else
				{
					a1[i] = 0;
					break;
				}
			}
			// Ð?o bit
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 1)
					a1[i] = 0;
				else
					a1[i] = 1;
			}

			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 1)
				{
					temp1 = myPow(i);
					result1 = plusNumInStr(result1, temp1);
				}
			}
			//s? th? 2
			// Tr? 1 d? thành d?ng bù 1
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 0)
				{
					a2[i] = 1;
				}
				else
				{
					a2[i] = 0;
					break;
				}
			}
			// Ð?o bit
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 1)
					a2[i] = 0;
				else
					a2[i] = 1;
			}

			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 1)
				{
					temp2 = myPow(i);
					result2 = plusNumInStr(result2, temp2);
				}
			}
			if (result1.length() > result2.length())//a<b
				return 0;
			if (result1.length() < result2.length())//a>b
				return 1;
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] != a2[i])
					break;
				if (i == 126 && a1[i] == a2[i])//a==b
					return 0;
			}
			// Tr? 1 d? thành d?ng bù 1
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 0)
				{
					a2[i] = 1;
				}
				else
				{
					a2[i] = 0;
					break;
				}
			}
			// Ð?o bit
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 1)
					a2[i] = 0;
				else
					a2[i] = 1;
			}
			a2[127] = 0;// s? th? 2 tr? thành s? duong
			int remember = 0;//bi?n nh?
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 1 || a2[i] == 1)
				{
					if (a1[i] == a2[i])
					{
						if (remember == 1)
							a3[i] = 1;
						else
						{
							a3[i] = 0;
							remember = 1;
						}
					}
					else
					{
						if (remember == 1)
							a3[i] = 0;
						else
						{
							a3[i] = 1;
							remember = 0;
						}
					}
				}
				else
				{
					if (remember == 1)
					{
						a3[i] = 1;
						remember = 0;
					}
					else
						a3[i] = 0;
				}
			}
			if (remember == 1)
				return 0;
			if (a3[127] == 1)//a-b ra s? âm
				return 0;
			else//a-b ra s? duong
				return 1;
		}
	}
}
//so sanh nho hon
bool QInt::operator<(QInt B)
{
	unsigned int a1[128] = { 0 };
	// Ð?c các bit c?a data luu vào m?ng a1, bit d?u là bit a1[127]
	int d1 = 3, count1 = 0;
	for (int i = 0; i < 128; i++)
	{
		a1[i] = 1 & (data[d1] >> count1);
		count1++;
		if (count1 == 32)
		{
			count1 = 0;
			d1--;
		}
	}
	unsigned int a2[128] = { 0 };
	// Ð?c các bit c?a data luu vào m?ng a2, bit d?u là bit a2[127]
	int d2 = 3, count2 = 0;
	for (int i = 0; i < 128; i++)
	{
		a2[i] = 1 & (B.data[d2] >> count2);
		count2++;
		if (count2 == 32)
		{
			count2 = 0;
			d2--;
		}
	}
	unsigned int a3[128] = { 0 };
	//TH1: 2 s? khác d?u
	if (a1[127] != a2[127])
	{
		if (a1[127] == 0)
			return 0;
		else
			return 1;
	}
	//TH2: 2 s? cùng d?u
	else
	{
		string result1 = "0";
		string temp1;
		string result2 = "0";
		string temp2;
		//TH 2 s? cùng duong
		if (a1[127] == 0)
		{

			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 1)
				{
					temp1 = myPow(i);
					result1 = plusNumInStr(result1, temp1);
				}
			}
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 1)
				{
					temp2 = myPow(i);
					result2 = plusNumInStr(result2, temp2);
				}
			}
			if (result1.length() > result2.length())//a>b
				return 0;
			if (result1.length() < result2.length())//a<b
				return 1;
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] != a2[i])
					break;
				if (i == 126 && a1[i] == a2[i])//a==b
					return 0;
			}
			//s? th? 2 d?o bit thành d?ng bù 1
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 1)
				{
					a2[i] = 0;
				}
				else
				{
					a2[i] = 1;
				}
			}
			//C?ng 1 vào k?t qu? thành d?ng bù 2
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 1)
				{
					a2[i] = 0;
				}
				else
				{
					a2[i] = 1;
					break;
				}
			}
			a2[127] = 1;// s? th? 2 tr? thành s? âm
			int remember = 0;//bi?n nh?
			//l?y s? th? 1 c?ng s? th? 2
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 1 || a2[i] == 1)
				{
					if (a1[i] == a2[i])
					{
						if (remember == 1)
							a3[i] = 1;
						else
						{
							a3[i] = 0;
							remember = 1;
						}
					}
					else
					{
						if (remember == 1)
							a3[i] = 0;
						else
						{
							a3[i] = 1;
							remember = 0;
						}
					}
				}
				else
				{
					if (remember == 1)
					{
						a3[i] = 1;
						remember = 0;
					}
					else
						a3[i] = 0;
				}
			}
			a3[127] = 1;
			if (remember == 1)
				return 0;//a3[127]=0
			if (a3[127] == 1)//a-b ra s? âm
				return 1;
			else//a-b ra s? duong
				return 0;
		}
		//TH 2 s? cùng âm
		else
		{
			//s? th? 1
			// Tr? 1 d? thành d?ng bù 1
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 0)
				{
					a1[i] = 1;
				}
				else
				{
					a1[i] = 0;
					break;
				}
			}
			// Ð?o bit
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 1)
					a1[i] = 0;
				else
					a1[i] = 1;
			}

			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 1)
				{
					temp1 = myPow(i);
					result1 = plusNumInStr(result1, temp1);
				}
			}
			//s? th? 2
			// Tr? 1 d? thành d?ng bù 1
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 0)
				{
					a2[i] = 1;
				}
				else
				{
					a2[i] = 0;
					break;
				}
			}
			// Ð?o bit
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 1)
					a2[i] = 0;
				else
					a2[i] = 1;
			}

			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 1)
				{
					temp2 = myPow(i);
					result2 = plusNumInStr(result2, temp2);
				}
			}
			if (result1.length() > result2.length())//a<b
				return 1;
			if (result1.length() < result2.length())//a>b
				return 0;
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] != a2[i])
					break;
				if (i == 126 && a1[i] == a2[i])//a==b
					return 0;
			}
			// Tr? 1 d? thành d?ng bù 1
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 0)
				{
					a2[i] = 1;
				}
				else
				{
					a2[i] = 0;
					break;
				}
			}
			// Ð?o bit
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 1)
					a2[i] = 0;
				else
					a2[i] = 1;
			}
			a2[127] = 0;// s? th? 2 tr? thành s? duong
			int remember = 0;//bi?n nh?
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 1 || a2[i] == 1)
				{
					if (a1[i] == a2[i])
					{
						if (remember == 1)
							a3[i] = 1;
						else
						{
							a3[i] = 0;
							remember = 1;
						}
					}
					else
					{
						if (remember == 1)
							a3[i] = 0;
						else
						{
							a3[i] = 1;
							remember = 0;
						}
					}
				}
				else
				{
					if (remember == 1)
					{
						a3[i] = 1;
						remember = 0;
					}
					else
						a3[i] = 0;
				}
			}
			if (remember == 1)
				return 1;
			if (a3[127] == 1)//a-b ra s? âm
				return 1;
			else//a-b ra s? duong
				return 0;
		}
	}
}
//so sanh bang nhau
bool QInt::operator==(QInt B)
{
	for (int i = 0; i < 4; i++)
	{
		if (data[i] != B.data[i])
			return 0;
	}
	return 1;
}
//so sanh nho hon hoac bang
bool QInt::operator<=(QInt B)
{
	unsigned int a1[128] = { 0 };
	// Ð?c các bit c?a data luu vào m?ng a1, bit d?u là bit a1[127]
	int d1 = 3, count1 = 0;
	for (int i = 0; i < 128; i++)
	{
		a1[i] = 1 & (data[d1] >> count1);
		count1++;
		if (count1 == 32)
		{
			count1 = 0;
			d1--;
		}
	}
	unsigned int a2[128] = { 0 };
	// Ð?c các bit c?a data luu vào m?ng a2, bit d?u là bit a2[127]
	int d2 = 3, count2 = 0;
	for (int i = 0; i < 128; i++)
	{
		a2[i] = 1 & (B.data[d2] >> count2);
		count2++;
		if (count2 == 32)
		{
			count2 = 0;
			d2--;
		}
	}
	unsigned int a3[128] = { 0 };
	//TH1: 2 s? khác d?u
	if (a1[127] != a2[127])
	{
		if (a1[127] == 0)
			return 0;
		else
			return 1;
	}
	//TH2: 2 s? cùng d?u
	else
	{
		string result1 = "0";
		string temp1;
		string result2 = "0";
		string temp2;
		//TH 2 s? cùng duong
		if (a1[127] == 0)
		{

			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 1)
				{
					temp1 = myPow(i);
					result1 = plusNumInStr(result1, temp1);
				}
			}
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 1)
				{
					temp2 = myPow(i);
					result2 = plusNumInStr(result2, temp2);
				}
			}
			if (result1.length() > result2.length())//a>b
				return 0;
			if (result1.length() < result2.length())//a<b
				return 1;
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] != a2[i])
					break;
				if (i == 126 && a1[i] == a2[i])//a==b
					return 1;
			}
			//s? th? 2 d?o bit thành d?ng bù 1
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 1)
				{
					a2[i] = 0;
				}
				else
				{
					a2[i] = 1;
				}
			}
			//C?ng 1 vào k?t qu? thành d?ng bù 2
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 1)
				{
					a2[i] = 0;
				}
				else
				{
					a2[i] = 1;
					break;
				}
			}
			a2[127] = 1;// s? th? 2 tr? thành s? âm
			int remember = 0;//bi?n nh?
							 //l?y s? th? 1 c?ng s? th? 2
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 1 || a2[i] == 1)
				{
					if (a1[i] == a2[i])
					{
						if (remember == 1)
							a3[i] = 1;
						else
						{
							a3[i] = 0;
							remember = 1;
						}
					}
					else
					{
						if (remember == 1)
							a3[i] = 0;
						else
						{
							a3[i] = 1;
							remember = 0;
						}
					}
				}
				else
				{
					if (remember == 1)
					{
						a3[i] = 1;
						remember = 0;
					}
					else
						a3[i] = 0;
				}
			}
			a3[127] = 1;
			if (remember == 1)
				return 0;//a3[127]=0
			if (a3[127] == 1)//a-b ra s? âm
				return 1;
			else//a-b ra s? duong
				return 0;
		}
		//TH 2 s? cùng âm
		else
		{
			//s? th? 1
			// Tr? 1 d? thành d?ng bù 1
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 0)
				{
					a1[i] = 1;
				}
				else
				{
					a1[i] = 0;
					break;
				}
			}
			// Ð?o bit
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 1)
					a1[i] = 0;
				else
					a1[i] = 1;
			}

			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 1)
				{
					temp1 = myPow(i);
					result1 = plusNumInStr(result1, temp1);
				}
			}
			//s? th? 2
			// Tr? 1 d? thành d?ng bù 1
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 0)
				{
					a2[i] = 1;
				}
				else
				{
					a2[i] = 0;
					break;
				}
			}
			// Ð?o bit
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 1)
					a2[i] = 0;
				else
					a2[i] = 1;
			}

			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 1)
				{
					temp2 = myPow(i);
					result2 = plusNumInStr(result2, temp2);
				}
			}
			if (result1.length() > result2.length())//a<b
				return 1;
			if (result1.length() < result2.length())//a>b
				return 0;
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] != a2[i])
					break;
				if (i == 126 && a1[i] == a2[i])//a==b
					return 1;
			}
			// Tr? 1 d? thành d?ng bù 1
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 0)
				{
					a2[i] = 1;
				}
				else
				{
					a2[i] = 0;
					break;
				}
			}
			// Ð?o bit
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 1)
					a2[i] = 0;
				else
					a2[i] = 1;
			}
			a2[127] = 0;// s? th? 2 tr? thành s? duong
			int remember = 0;//bi?n nh?
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 1 || a2[i] == 1)
				{
					if (a1[i] == a2[i])
					{
						if (remember == 1)
							a3[i] = 1;
						else
						{
							a3[i] = 0;
							remember = 1;
						}
					}
					else
					{
						if (remember == 1)
							a3[i] = 0;
						else
						{
							a3[i] = 1;
							remember = 0;
						}
					}
				}
				else
				{
					if (remember == 1)
					{
						a3[i] = 1;
						remember = 0;
					}
					else
						a3[i] = 0;
				}
			}
			if (remember == 1)
				return 1;
			if (a3[127] == 1)//a-b ra s? âm
				return 1;
			else//a-b ra s? duong
				return 0;
		}
	}
}
//so sanh lon hon hoac bang
bool QInt::operator>=(QInt B)
{
	unsigned int a1[128] = { 0 };
	// Ð?c các bit c?a data luu vào m?ng a1, bit d?u là bit a1[127]
	int d1 = 3, count1 = 0;
	for (int i = 0; i < 128; i++)
	{
		a1[i] = 1 & (data[d1] >> count1);
		count1++;
		if (count1 == 32)
		{
			count1 = 0;
			d1--;
		}
	}
	unsigned int a2[128] = { 0 };
	// Ð?c các bit c?a data luu vào m?ng a2, bit d?u là bit a2[127]
	int d2 = 3, count2 = 0;
	for (int i = 0; i < 128; i++)
	{
		a2[i] = 1 & (B.data[d2] >> count2);
		count2++;
		if (count2 == 32)
		{
			count2 = 0;
			d2--;
		}
	}
	unsigned int a3[128] = { 0 };
	//TH1: 2 s? khác d?u
	if (a1[127] != a2[127])
	{
		if (a1[127] == 0)
			return 1;
		else
			return 0;
	}
	//TH2: 2 s? cùng d?u
	else
	{
		string result1 = "0";
		string temp1;
		string result2 = "0";
		string temp2;
		//TH 2 s? cùng duong
		if (a1[127] == 0)
		{

			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 1)
				{
					temp1 = myPow(i);
					result1 = plusNumInStr(result1, temp1);
				}
			}
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 1)
				{
					temp2 = myPow(i);
					result2 = plusNumInStr(result2, temp2);
				}
			}
			if (result1.length() > result2.length())//a>b
				return 1;
			if (result1.length() < result2.length())//a<b
				return 0;
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] != a2[i])
					break;
				if (i == 126 && a1[i] == a2[i])//a==b=>0
					return 1;
			}
			//s? th? 2 d?o bit thành d?ng bù 1
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 1)
				{
					a2[i] = 0;
				}
				else
				{
					a2[i] = 1;
				}
			}
			//C?ng 1 vào k?t qu? thành d?ng bù 2
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 1)
				{
					a2[i] = 0;
				}
				else
				{
					a2[i] = 1;
					break;
				}
			}
			a2[127] = 1;// s? th? 2 tr? thành s? âm
			int remember = 0;//bi?n nh?
							 //l?y s? th? 1 c?ng s? th? 2
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 1 || a2[i] == 1)
				{
					if (a1[i] == a2[i])
					{
						if (remember == 1)
							a3[i] = 1;
						else
						{
							a3[i] = 0;
							remember = 1;
						}
					}
					else
					{
						if (remember == 1)
							a3[i] = 0;
						else
						{
							a3[i] = 1;
							remember = 0;
						}
					}
				}
				else
				{
					if (remember == 1)
					{
						a3[i] = 1;
						remember = 0;
					}
					else
						a3[i] = 0;
				}
			}
			a3[127] = 1;
			if (remember == 1)
				return 1;//a3[127]=0
			if (a3[127] == 1)//a-b ra s? âm
				return 0;
			else//a-b ra s? duong
				return 1;
		}
		//TH 2 s? cùng âm
		else
		{
			//s? th? 1
			// Tr? 1 d? thành d?ng bù 1
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 0)
				{
					a1[i] = 1;
				}
				else
				{
					a1[i] = 0;
					break;
				}
			}
			// Ð?o bit
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 1)
					a1[i] = 0;
				else
					a1[i] = 1;
			}

			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 1)
				{
					temp1 = myPow(i);
					result1 = plusNumInStr(result1, temp1);
				}
			}
			//s? th? 2
			// Tr? 1 d? thành d?ng bù 1
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 0)
				{
					a2[i] = 1;
				}
				else
				{
					a2[i] = 0;
					break;
				}
			}
			// Ð?o bit
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 1)
					a2[i] = 0;
				else
					a2[i] = 1;
			}

			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 1)
				{
					temp2 = myPow(i);
					result2 = plusNumInStr(result2, temp2);
				}
			}
			if (result1.length() > result2.length())//a<b
				return 0;
			if (result1.length() < result2.length())//a>b
				return 1;
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] != a2[i])
					break;
				if (i == 126 && a1[i] == a2[i])//a==b
					return 1;
			}
			// Tr? 1 d? thành d?ng bù 1
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 0)
				{
					a2[i] = 1;
				}
				else
				{
					a2[i] = 0;
					break;
				}
			}
			// Ð?o bit
			for (int i = 0; i < 127; i++)
			{
				if (a2[i] == 1)
					a2[i] = 0;
				else
					a2[i] = 1;
			}
			a2[127] = 0;// s? th? 2 tr? thành s? duong
			int remember = 0;//bi?n nh?
			for (int i = 0; i < 127; i++)
			{
				if (a1[i] == 1 || a2[i] == 1)
				{
					if (a1[i] == a2[i])
					{
						if (remember == 1)
							a3[i] = 1;
						else
						{
							a3[i] = 0;
							remember = 1;
						}
					}
					else
					{
						if (remember == 1)
							a3[i] = 0;
						else
						{
							a3[i] = 1;
							remember = 0;
						}
					}
				}
				else
				{
					if (remember == 1)
					{
						a3[i] = 1;
						remember = 0;
					}
					else
						a3[i] = 0;
				}
			}
			if (remember == 1)
				return 0;
			if (a3[127] == 1)//a-b ra s? âm
				return 0;
			else//a-b ra s? duong
				return 1;
		}
	}
}
//toan tu gan bang
QInt& QInt::operator=(QInt B)
{
	for (int i = 0; i < 4; i++)
	{
		data[i] = B.data[i];
	}
	return *this;
}

QInt& QInt::operator=(string s)
{
	unsigned int a[128];
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

string QInt::decToStr()
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


	string result = "0";
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
	return result;

}

QInt::~QInt()
{
}
