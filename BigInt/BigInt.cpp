// BigInt.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "QInt.h"
#include <vector>

using namespace std;

//Chuyển wchar sang chuỗi
char *wchar_to_string(_TCHAR *widechar)
{
	int size = 0;
	while ((char)widechar[size] != '\0')
	{
		size++;
	}
	size++;
	char *charpointer;
	charpointer = new char[size];
	wcstombs(charpointer, widechar, size);
	return charpointer;
}


int _tmain(int argc, _TCHAR* argv[])
{
	char* inputFile = wchar_to_string(argv[1]); //Tên file  input
	char* outputFile = wchar_to_string(argv[2]); //Tên file output
	string type = wchar_to_string(argv[3]); //Loại tập tin, 1: Số QInt, 2:QFloat
	
	freopen(inputFile, "r+", stdin); //Mở file để đọc dữ liệu 
	
	string s1;
	string s2;
	string s3;
	string s4;
	vector <string> result; //Mảng lưu trữ các giá trị kết quả
	
	if (type == "1") //File QInt
	{
		while (cin>>s1) //Đọc giá trị thứ nhất, đây cũng là điều kiện kiểm tra kết thúc file
		{
			cin >> s2; //Đọc giá trị thứ 2
			//Trường hợp 2 tham số đầu đều là p, nghĩa là chuyển đổi cơ số
			if (s2 == "2" || s2 == "10" || s2 == "16") 
			{
				cin >> s3; //Đọc giá trị còn lại trên dòng
				
				if (s1 == "10") //Số cần chuyển ở hệ 10
				{
					QInt a;
					a = s3; //Tạo một QInt có giá trị bằng s3
					if (s2 == "2") //Chuyển hệ 10 sang hệ 2
					{
						string temp = a.decToBin();
						result.push_back(temp);
					}
					else if (s2 == "16") //Chuyển hệ 10 sang 16
					{
						string temp = a.decToHex();
						result.push_back(temp);
					}
					
				}
				
				else if (s1 == "2") //Số cần chuyển ở hệ 2
				{
					if (s2 == "10") // Chuyển hệ 2 sang hệ 10
					{
						QInt a;
						a.binToDec(s3);
						string temp = a.decToStr();
						result.push_back(temp);
					}
					else if (s2 == "16") //Chuyển hệ 2 sang hệ 16
					{
						QInt a;
						string temp = a.binToHex(s3);
						result.push_back(temp);
					}
				}

				else if (s1 == "16") //Số cần chuyển ở hệ 16
				{
					QInt a;
					a.hexToDec(s3);
					if (s2 == "2") //Chuyển hệ 16 sang hệ 2
					{
						string temp = a.decToBin();
						result.push_back(temp);
					}
					else if (s2 == "10") //Chuyển hệ 16 sang hệ 10
					{
						string temp = a.decToStr();
						result.push_back(temp);
					}
				}
			}
			else if(s2!="~")
			{
				cin >> s3; //Biến lưu toán tử
				cin >> s4; 
				
				if (s1 == "2") //Xử lý ở chế độ Bin
				{
					QInt a;
					QInt b;
					a.binToDec(s2);

					if (s3 == "+")
					{
						QInt c;
						b.binToDec(s4);
						try
						{
							c = a + b;
							string temp = c.decToBin();
							result.push_back(temp);
						}
						catch (const char* msg)
						{
							result.push_back(msg);
						}
					}

					else if (s3 == "-")
					{
						QInt c;
						b.binToDec(s4);
						try
						{
							c = a - b;
							string temp = c.decToBin();
							result.push_back(temp);
						}
						catch (const char* msg)
						{
							result.push_back(msg);
						}
					}
					else if (s3 == "/")
					{
						QInt c;
						b.binToDec(s4);
						try
						{
							c = a / b;
							string temp = c.decToBin();
							result.push_back(temp);
						}
						catch (const char* msg)
						{
							result.push_back(msg);
						}
					}
					else if (s3 == "*")
					{
						QInt c;
						b.binToDec(s4);
						try
						{
							c = a * b;
							string temp = c.decToBin();
							result.push_back(temp);
						}
						catch (const char* msg)
						{
							result.push_back(msg);
						}
					}

					else if (s3 == "<")
					{
						b.binToDec(s4);
						string temp;
						if (a < b)
							temp = "True";
						else
							temp = "False";
						result.push_back(temp);
					}

					else if (s3 == ">")
					{
						b.binToDec(s4);
						string temp;
						if (a > b)
							temp = "True";
						else
							temp = "False";
						result.push_back(temp);
					}

					else if (s3 == "==")
					{
						b.binToDec(s4);
						string temp;
						if (a == b)
							temp = "True";
						else
							temp = "False";
						result.push_back(temp);
					}

					else if (s3 == "<=")
					{
						b.binToDec(s4);
						string temp;
						if (a <= b)
							temp = "True";
						else
							temp = "False";
						result.push_back(temp);
					}

					else if (s3 == ">=")
					{
						b.binToDec(s4);
						string temp;
						if (a >= b)
							temp = "True";
						else
							temp = "False";
						result.push_back(temp);
					}

					else if (s3 == "&")
					{
						b.binToDec(s4);
						QInt c;
						c = a & b;
						string temp = c.decToBin();
						result.push_back(temp);
					}

					else if (s3 == "|")
					{
						b.binToDec(s4);
						QInt c;
						c = a | b;
						string temp = c.decToBin();
						result.push_back(temp);
					}

					else if (s3 == "^")
					{
						b.binToDec(s4);
						QInt c;
						c = a ^ b;
						string temp = c.decToBin();
						result.push_back(temp);
					}

					else if (s3 == "<<")
					{
						int n = strToNum(s4);
						QInt c;
						c = a << n;
						string temp = c.decToBin();
						result.push_back(temp);

					}

					else if (s3 == ">>")
					{
					int n = strToNum(s4);
					QInt c;
					c = a >> n;
					string temp = c.decToBin();
					result.push_back(temp);
					}
				}
				else if (s1 == "10") //Xử lý ở chế độ Dec
				{
					QInt a;
					QInt b;
					a = s2; //Gán giá trị cho a bằng giá trị của s2

					if (s3 == "+")
					{
						b = s4;
						QInt c;
						try
						{
							c = a + b;
							string temp = c.decToStr();
							result.push_back(temp);
						}
						catch (const char* msg)
						{
							result.push_back(msg);
						}
					}

					else if (s3 == "-")
					{
						b = s4;
						QInt c;
						try
						{
							c = a - b;
							string temp = c.decToStr();
							result.push_back(temp);
						}
						catch (const char* msg)
						{
							result.push_back(msg);
						}
					}
					else if (s3 == "/")
					{
						b = s4;
						QInt c;
						try
						{
							c = a / b;
							string temp = c.decToStr();
							result.push_back(temp);
						}
						catch (const char* msg)
						{
							result.push_back(msg);
						}
					}
					else if (s3 == "*")
					{
						b = s4;
						QInt c;
						try
						{
							c = a * b;
							string temp = c.decToStr();
							result.push_back(temp);
						}
						catch (const char* msg)
						{
							result.push_back(msg);
						}
					}

					else if (s3 == "<")
					{
						b = s4;
						string temp;
						if (a < b)
							temp = "True";
						else
							temp = "False";
						result.push_back(temp);
					}

					else if (s3 == ">")
					{
						b = s4;
						string temp;
						if (a > b)
							temp = "True";
						else
							temp = "False";
						result.push_back(temp);
					}

					else if (s3 == "==")
					{
						b = s4;
						string temp;
						if (a == b)
							temp = "True";
						else
							temp = "False";
						result.push_back(temp);
					}

					else if (s3 == "<=")
					{
						b = s4;
						string temp;
						if (a <= b)
							temp = "True";
						else
							temp = "False";
						result.push_back(temp);
					}

					else if (s3 == ">=")
					{
						b = s4;
						string temp;
						if (a >= b)
							temp = "True";
						else
							temp = "False";
						result.push_back(temp);
					}

					else if (s3 == "&")
					{
						b = s4;
						QInt c;
						c = a & b;
						string temp = c.decToStr();
						result.push_back(temp);
					}

					else if (s3 == "|")
					{
						b = s4;
						QInt c;
						c = a | b;
						string temp = c.decToStr();
						result.push_back(temp);
					}

					else if (s3 == "^")
					{
						b = s4;
						QInt c;
						c = a ^ b;
						string temp = c.decToStr();
						result.push_back(temp);
					}

					else if (s3 == "<<")
					{
						int n = strToNum(s4);
						QInt c;
						c = a << n;
						string temp = c.decToStr();
						result.push_back(temp);

					}

					else if (s3 == ">>")
					{
						int n = strToNum(s4);
						QInt c;
						c = a >> n;
						string temp = c.decToStr();
						result.push_back(temp);
					}
				}
				else if (s1 == "16") //Xử lý ở chế độ 16
				{
				QInt a;
				QInt b;
				a.hexToDec(s2);

				if (s3 == "+")
				{
					b.hexToDec(s4);
					QInt c;
					try
					{
						c = a + b;
						string temp = c.decToHex();
						result.push_back(temp);
					}
					catch (const char* msg)
					{
						result.push_back(msg);
					}
					
				}

				else if (s3 == "-")
				{
					b.hexToDec(s4);
					QInt c;
					try
					{
						c = a - b;
						string temp = c.decToHex();
						result.push_back(temp);
					}
					catch (const char* msg)
					{
						result.push_back(msg);
					}
				}
				else if (s3 == "/")
				{
					b.hexToDec(s4);
					QInt c;
					try
					{
						c = a / b;
						string temp = c.decToHex();
						result.push_back(temp);
					}
					catch (const char* msg)
					{
						result.push_back(msg);
					}
				}
				else if (s3 == "*")
				{
					b.hexToDec(s4);
					QInt c;
					try
					{
						c = a * b;
						string temp = c.decToHex();
						result.push_back(temp);
					}
					catch (const char* msg)
					{
						result.push_back(msg);
					}
				}

				else if (s3 == "<")
				{
					b.hexToDec(s4);
					string temp;
					if (a < b)
						temp = "True";
					else
						temp = "False";
					result.push_back(temp);
				}

				else if (s3 == ">")
				{
					b.hexToDec(s4);
					string temp;
					if (a > b)
						temp = "True";
					else
						temp = "False";
					result.push_back(temp);
				}

				else if (s3 == "==")
				{
					b.hexToDec(s4);
					string temp;
					if (a == b)
						temp = "True";
					else
						temp = "False";
					result.push_back(temp);
				}

				else if (s3 == "<=")
				{
					b.hexToDec(s4);
					string temp;
					if (a <= b)
						temp = "True";
					else
						temp = "False";
					result.push_back(temp);
				}

				else if (s3 == ">=")
				{
					b.hexToDec(s4);
					string temp;
					if (a >= b)
						temp = "True";
					else
						temp = "False";
					result.push_back(temp);
				}

				else if (s3 == "&")
				{
					b.hexToDec(s4);
					QInt c;
					c = a & b;
					string temp = c.decToHex();
					result.push_back(temp);
				}

				else if (s3 == "|")
				{
					b.hexToDec(s4);
					QInt c;
					c = a | b;
					string temp = c.decToHex();
					result.push_back(temp);
				}

				else if (s3 == "^")
				{
					b.hexToDec(s4);
					QInt c;
					c = a ^ b;
					string temp = c.decToHex();
					result.push_back(temp);
				}

				else if (s3 == "<<")
				{
					int n = strToNum(s4);
					QInt c;
					c = a << n;
					string temp = c.decToHex();
					result.push_back(temp);

				}

				else if (s3 == ">>")
				{
					int n = strToNum(s4);
					QInt c;
					c = a >> n;
					string temp = c.decToHex();
					result.push_back(temp);
				}
				}

			}
			else if (s2 == "~") //Toán tử 1 ngôi ~
			{
				cin >> s3;
				if (s1 == "10")
				{
					QInt a;
					a = s3;
					a = ~a;
					string temp = a.decToStr();
					result.push_back(temp);

				}
				else if (s1 == "2")
				{
					QInt a;
					a.binToDec(s3);
					a = ~a;
					string temp = a.decToBin();
					result.push_back(temp);
				}
				else if (s1 == "16")
				{
					QInt a;
					a.hexToDec(s3);
					a = ~a;
					string temp = a.decToHex();
					result.push_back(temp);
				}
			}
		}
	}
	cout << "DONE !";
	freopen(outputFile, "w+", stdout); //Ghi ra file
	for (int i = 0; i < result.size(); i++)
	{
		cout << result[i]<<endl;
	}

}
