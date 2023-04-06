#pragma once
#include <iostream>
#include <string>
#include <conio.h>
using namespace std;

class MyString
{
private:
	char* mem;
	int count;
	int size;
public:
	MyString(string str = "") {
		if (str.length() > 256) {
			size = str.length();
		}
		else {
			size = 256;
		}
		count = str.length();
		mem = new char[size];
		for (int i = 0; i < count; i++) {
			mem[i] = str[i];
		}
	};
	MyString(char* src, int k) {
		count = k;

		if (k > 256) {
			size = k;
		}
		else {
			size = 256;
		}

		mem = new char[size];

		for (int i = 0; i < count; i++) {
			mem[i] = src[i];
		}
	};
	MyString(int num)
	{
		size = 128;
		count = 0;
		char tmp;
		mem = new char[size];
		/*char nums[] = {'0','1','2','3','4','5','6','7','8','9'};*/
		while (num > 0)
		{
			int char_number = num % 10 + 48;
			mem[count++] = char_number;

			num /= 10;
		}

		for (int i = 0; i < count; i++)
		{
			tmp = mem[i];
			mem[i] = mem[count - 1 - i];
			mem[count - 1 - i] = tmp;
		}
	}
	~MyString() { delete[] mem; };
	MyString(const MyString& tmp) {
		count = tmp.count;
		size = tmp.size;

		mem = new char[size];
		for (int i = 0; i < count; i++) {
			mem[i] = tmp.mem[i];
		}
	};
	MyString& operator=(MyString tmp) {
		if (size != tmp.size) {
			if (size != 0) {
				delete[]mem;
			}

			size = tmp.size;
			mem = new char[size];
		}

		count = tmp.count;
		for (int i = 0; i < count; i++) {
			mem[i] = tmp.mem[i];
		}

		return *this;
	};

	MyString& operator=(string tmp) {
		if (size != tmp.size()) {
			if (size != 0) {
				delete[]mem;
			}

			size = tmp.size();
			mem = new char[size];
		}

		count = tmp.length();
		for (int i = 0; i < count; i++) {
			mem[i] = tmp[i];
		}

		return *this;
	};

	int GetCount() {
		return this->count;
	}
	char& operator[](int k) {
		if (k >= 0 && k < count) {
			return mem[k];
		}

		char a = NULL;

		return a;
	}
	int length() {
		return this->count;
	}
	MyString copy(int start, int _count) {
		int len;

		if (start + _count > this->count) {
			len = this->count - start;
		}
		else {
			len = _count;
		}

		char* str;
		str = new char[len];

		for (int i = start; i < start + len; i++) {
			str[i - start] = this->mem[i];
		}

		MyString new_string(str, len);

		return new_string;
	}
	void del(int start, int _count) {
		if (start < 0) {
			this->count = 0;
		}
		else if (start < this->count) {
			for (int i = 0; i < this->count - start; i++) {
				mem[start + i] = mem[start + _count + i];
			}

			if (start + _count > this->count) {
				this->count = start;
			}
			else {
				this->count -= _count;
			}
		}
	}
	MyString operator+(MyString tmp) {
		char* str;

		str = new char[count + tmp.count];

		for (int i = 0; i < count; i++) {
			str[i] = mem[i];
		}

		for (int i = 0; i < tmp.count; i++) {
			str[i + count] = tmp.mem[i];
		}

		int new_count = count + tmp.count;

		MyString new_str(str, new_count);

		return new_str;
	}
	MyString operator+(string tmp) {
		char* str;

		str = new char[count + tmp.length()];

		for (int i = 0; i < count; i++) {
			str[i] = mem[i];
		}

		for (int i = 0; i < tmp.length(); i++) {
			str[i + count] = tmp[i];
		}

		int new_count = count + tmp.length();

		MyString new_str(str, new_count);

		return new_str;
	}
	int find(MyString dst, int start = 0) {
		int l = -1;
		int index = 0;

		while (l == -1 && index < count - dst.count - start) {
			if (mem[start + index] == dst.mem[0]) {
				l = start + index;
			}

			index++;
		}

		for (int i = 0; i < dst.count && l >= 0; i++) {
			if (mem[l + i] != dst.mem[i]) {
				l = -1;
			}
		}

		return l;
	}
	int find(char dst, int start = 0) {
		int l = -1;
		int index = 0;

		while (l == -1 && index < count - start) {
			if (mem[start + index] == dst) {
				l = start + index;
			}

			index++;
		}

		return l;
	}
	int find(string dst, int start = 0) {
		int l = -1;
		int index = 0;

		while (l == -1 && index < count - dst.length() - start) {
			if (mem[start + index] == dst[0]) {
				l = start + index;
			}

			index++;
		}

		for (int i = 0; i < dst.length() && l >= 0; i++) {
			if (mem[l + i] != dst[i]) {
				l = -1;
			}
		}

		return l;
	}

	void string_split_smart(MyString razd, MyString*& result, int& new_count) {
		for (int i = 0; i < count; i++) {
			int l = razd.find(mem[i]);
			if (l < 0 || l > razd.count) {
				result[new_count] = result[new_count] + mem[i];
			}
			else {
				if (mem[i] == ' ') {
					if (result[new_count] != "") {
						result[++new_count] = "";
					}
				}
				else {
					if (result[new_count] != "") {
						new_count++;
					}
					result[new_count] = mem[i];
					result[++new_count] = "";
				}
			}
		}
	}
	MyString& operator+= (const char c)
	{
		count++;
		mem = (char*)realloc(mem, count * sizeof(char));
		mem[count - 1] = c;
		mem[count] = NULL;
		return *this;
	};

	istream& getline(istream& is, MyString& str)
	{
		char* c = new char[100];
		is.get(c, 100);
		int i = 0;
		while (c[i] != '\n' && i < strlen(c))
		{
			str += c[i];
			++i;
		}
		str.mem[str.count] = NULL;
		delete[]c;
		return is;
	};



	int operator == (MyString tmp)
	{
		int result = 1; //сравнимые строки одинаковы
		if (count != tmp.count)
		{
			int result = 0;
		}
		else
		{
			for (int i = 0; i < count && result == 0; i++)
			{
				if (mem[i] != tmp.mem[i])
				{
					result = 0;
				}
			}
		}
		return result;
	}
	int operator == (string tmp)
	{
		int result = 1; //сравнимые строки одинаковы
		if (count != tmp.length())
		{
			int result = 0;
		}
		else
		{
			for (int i = 0; i < count && result == 0; i++)
			{
				if (mem[i] != tmp[i])
				{
					result = 0;
				}
			}
		}
		return result;
	}
	int operator != (string tmp)
	{
		int result = 0; //сравнимые строки одинаковы
		if (count != tmp.length())
		{
			int result = 1;
		}
		else
		{
			for (int i = 0; i < count && result == 0; i++)
			{
				if (mem[i] != tmp[i])
				{
					result = 1;
				}
			}
		}
		return result;
	}
	int operator > (MyString tmp)
	{
		int result = 0;
		for (int i = 0; i < count && i < tmp.count; i++)
		{
			if (mem[i] > tmp.mem[i])
			{
				result = -1;
			}
			if (count > tmp.count)
			{
				result = -1;
			}
		}
		return result;
	}
	int operator < (MyString tmp)
	{
		int result = 0;
		for (int i = 0; i < count && i < tmp.count; i++)
		{
			if (mem[i] < tmp.mem[i])
			{
				result = -1;
			}
			if (count < tmp.count)
			{
				result = -1;
			}
		}
		return result;
	}

	friend ostream& operator<<(ostream& out, MyString str) {

		for (int i = 0; i < str.GetCount(); i++) {
			out << str[i];
		}

		return out;
	}
	MyString& operator+=(const MyString& b)
	{
		int a_size = count;
		char* a_string = (char*)malloc(a_size * sizeof(char));
		for (int i = 0; i < a_size; i++)
		{
			a_string[i] = mem[i];
		}
		a_string[a_size] = NULL;

		count = a_size + b.count;
		mem = (char*)realloc(mem, count * sizeof(char));
		for (int i = 0; i < count; i++)
		{
			if (i < a_size)
				mem[i] = a_string[i];
			else
				mem[i] = b.mem[i - a_size];
		}
		mem[count] = NULL;
		return *this;
	};



	friend istream& operator>>(istream& in, MyString& p)
	{
		char key;
		int val;
		p.count = 0;
		p.mem = new char[512];
		while (1)
		{
			key = _getch();
			val = key;
			if (val == 13)
				break;
			cout << key;
			p.count++;
			p.mem = (char*)realloc(p.mem, 100 * sizeof(char));
			p.mem[p.count - 1] = key;
		}
		p.mem[p.count] = NULL;
		cout << endl;
		return in;
	};

	void getline(MyString p)
	{
		char key;
		int val;
		p.count = 0;
		p.mem = new char[512];
		while (1)
		{
			key = _getch();
			val = key;
			if (val == 13)
				break;
			cout << key;
			p.count++;
			p.mem = (char*)realloc(p.mem, 100 * sizeof(char));
			p.mem[p.count - 1] = key;
		}
		p.mem[p.count] = NULL;
		cout << endl;
	};


	istream& getline(istream& is, MyString& str, char delim)
	{
		char* c = new char[100];
		is.get(c, 100, delim);
		int i = 0;
		while (c[i] != delim && i < strlen(c))
		{
			str += c[i];
			++i;
		}
		str.mem[str.count] = NULL;
		delete[]c;
		return is;
	};

	operator std::string ()
	{
		return std::string(mem);
	}
};




