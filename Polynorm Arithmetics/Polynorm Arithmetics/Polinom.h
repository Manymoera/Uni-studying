#pragma once
#include "CircleList.h"
#include "function.h"

class Polinom
{
private:
    int maxPr;
    int count;
    CircleList list;
private:
    void StringToWords(std::string*& str, int& size, std::string polStr)
    {
        std::string monom{};
        for (const auto& sym : polStr)
            if (sym == '+' || sym == '-') ++size;
        ++size;
        str = new std::string[size];
        int index = 0;
        for (const auto& sym : polStr)
        {
            if (sym == ' ') continue;
            if (sym == '+' || sym == '-')
            {

                str[index++] = monom;
                monom.clear();

                if (sym == '-')	monom += '-';
            }
            else monom += sym;
        }
        str[index++] = monom;
    }
public:
    Polinom(int _maxPr = 10, int _count = 5)
    {
        maxPr = _maxPr;
        count = _count;
    }

    Polinom(std::string str, int _maxPr = 10, int _count = 5)
    {
        maxPr = _maxPr;
		count = _count;

		if (str != "")
		{
			std::string* pStr = 0;
			int size = 0;
			StringToWords(pStr, size, str);
			for (int i = 0; i < size; ++i)
			{
				Monom newMon(pStr[i], maxPr, count);

				if (newMon.getCoef() != 0.0)
					list.AddMonom(newMon);
			}
		}
    }

    ~Polinom() {}

    Polinom(const Polinom& other)
    {
        maxPr = other.maxPr;
        count = other.count;
        list = other.list;
    }

    Polinom& operator=(const Polinom& other)
    {
        maxPr = other.maxPr;
        count = other.count;
        list = other.list;

        return (*this);
    }

    std::string getPolinom()
    {
        return list.CircleListToString(maxPr, count);
    }

    Polinom operator+(const Polinom& other)
    {
        Polinom result;

        if ((maxPr == other.maxPr) && (count == other.count))
        {
            result = Polinom(maxPr, count);
            result.list = list + other.list;
        }

        return result;
    }

    Polinom operator-(const Polinom& other)
    {
        Polinom result;

        if ((maxPr == other.maxPr) && (count == other.count))
        {
            result = Polinom(maxPr, count);
            result.list = list - other.list;
        }

        return result;
    }

    Polinom operator*(int value)
    {
        Polinom result;

        if (value != 0)
        {
            result = Polinom(*this);
            result.list = list * value;
        }

        return result;
    }
    Polinom operator*(const Polinom& other)
    {
        Polinom result;

        if ((maxPr == other.maxPr) && (count == other.count))
        {
            result = Polinom(maxPr, count);
            result.list = list.Multiply(other.list, maxPr, count);
        }

        return result;
    }
    void AddMonom(const Monom& monom)
    {
        list.AddMonom(monom);
    }
};