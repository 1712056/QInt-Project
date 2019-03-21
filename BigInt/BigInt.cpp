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

/*
int main()
{
	string s = "85AF";
	QInt a;
	a.hexToDec(s);
	a.Xuat();

}
*/



int _tmain(int argc, _TCHAR* argv[])
{
	char* inputFile = wchar_to_string(argv[1]); //Tên file  input
	char* outputFile = wchar_to_string(argv[2]); //Tên file output
	string type = wchar_to_string(argv[3]); //Loại tập tin, 1: Số QInt, 2:Float
	freopen(inputFile, "r+", stdin);
	string s1;
	string s2;
	string s3;
	string s4;
	vector <string> result; //Mảng lưu trữ các giá trị kết quả
	if (type == "1") //File QInt
	{
		char c;
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
			
		}
	}
	cout << result.size() << endl;
	freopen(outputFile, "w+", stdout);
	for (int i = 0; i < result.size(); i++)
	{
		cout << result[i]<<endl;
	}

	
}
