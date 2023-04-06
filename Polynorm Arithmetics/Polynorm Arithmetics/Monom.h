#pragma once

#include <iostream>
#include <string>
#include <cmath>

class Monom
{
private:
	float coef;
	int SV;
	Monom* next;

public:
	Monom(float _coef = 0, int _fold = -1)
	{
		coef = _coef;
		SV = _fold;
		next = this;
	}

	Monom(std::string str, int maxPr, int count)
	{
		coef = getCoef(str);
		SV = makeSV(str, maxPr, count);
		next = this;
	}

	Monom(const Monom& other)
	{
		coef = other.coef;
		SV = other.SV;
		next = this;
	}

	~Monom()
	{
		next = nullptr;
	}

	Monom& operator=(const Monom& other)
	{
		coef = other.coef;
		SV = other.SV;
		next = this;

		return *this;
	}

	float getCoef(std::string str)
	{
		std::string temp = str;
		float result = 0;
		int pos = temp.find("x");

		if (pos > 1)
		{
			temp.erase(pos);
			result = stof(temp);
		}
		else
		{
			if (pos == 1)
			{
				if (temp[0] == '-')
				{
					result = -1;
				}
				else
				{
					std::string tmp = "";
					tmp = temp[0];
					result = stof(tmp);
				}
			}
			else if (pos == 0)
			{
				result = 1;
			}
		}

		return result;
	}

	int makeSV(std::string str, int maxPr, int count)
	{
		int* arrPr = new int[count];
		int result = 0;

		for (int i = 0; i < count; i++)
		{
			arrPr[i] = 0;
		}

		for (int i = count; i > 0; i--)
		{
			std::string variable = "x" + std::to_string(i);
			int pos = str.find(variable);

			if (pos != std::string::npos)
			{
				str.erase(pos, variable.length());

				if (str[pos] == '^')
				{
					str.erase(pos, 1);
					std::string p = "";

					while (str[pos] != '\0')
					{
						p = p + str[pos];
						str.erase(pos, 1);
					}

					arrPr[count - i] = stoi(p);
				}
				else
				{
					arrPr[count - i] = 1;
				}
			}
		}

		for (int i = 0; i < count; i++)
		{
			result = result + arrPr[i] * pow(maxPr, i);
		}

		return result;
	}

	int getSV()
	{
		return SV;
	}

	void setFold(int value)
	{
		SV = value;
	}

	int getCoef()
	{
		return coef;
	}

	void setCoef(int value)
	{
		coef = value;
	}

	Monom* getNext()
	{
		return next;
	}

	Monom* setNext(Monom* other)
	{
		next = other;
		return this;
	}

	Monom operator+(const Monom& other)
	{
		Monom result;

		if (SV == other.SV)
		{
			if (coef + other.coef != 0)
			{
				result.coef = coef + other.coef;
				result.SV = SV;
			}
		}
		else if (coef == 0)
		{
			result.coef = other.coef;
			result.SV = other.SV;
		}
		else if (other.coef == 0)
		{
			result.coef = coef;
			result.SV = SV;
		}
		else
		{
			std::cout << "Ошибка: сложение мономов с разными свёртками\n";
		}

		return result;
	}

	Monom operator-(const Monom& other)
	{
		Monom result;

		if (SV == other.SV)
		{
			if (coef - other.coef != 0)
			{
				result.coef = coef - other.coef;
				result.SV = SV;
			}
		}
		else if (coef == 0)
		{
			result.coef = (-(other.coef));
			result.SV = other.SV;
		}
		else if (other.coef == 0)
		{
			result.coef = coef;
			result.SV = SV;
		}
		else
		{
			std::cout << "Ошибка: вычитание мономов с разными свёртками\n";
		}

		return result;
	}

	Monom operator*(int value)
	{
		Monom result;

		if (value != 0)
		{
			result.coef = coef * value;
			result.SV = SV;
		}

		return result;
	}

	Monom Multiply(const Monom& other, int maxPr, int count)
	{
		Monom result;

		int newCoef = coef * other.coef;
		int newReduction = 0;
		bool flag = true;

		int rn1 = SV;
		int rn2 = other.SV;

		for (int i = 0; i < count; i++)
		{
			int pr1 = rn1 % (maxPr);
			rn1 = rn1 / (maxPr);
			int pr2 = rn2 % (maxPr);
			rn2 = rn2 / (maxPr);

			if (pr1 + pr2 < maxPr)
			{
				newReduction = newReduction + (pr1 + pr2) * pow(maxPr, i);
			}
			else
			{
				flag = false;
				break;
			}
		}

		if (!flag)
		{
			std::cout << "Error: exceeded maximum power\n";
		}
		else
		{
			result.coef = newCoef;
			result.SV = newReduction;
		}

		return result;
	}

	std::string MonomToString(int maxPr, int count)
	{
		std::string result;

		if (coef == 0)
		{
			result = "0";
		}
		else
		{
			int thisRn = SV;

			for (int i = 0; i < count; i++)
			{
				int rn = thisRn % (maxPr);
				thisRn = thisRn / (maxPr);

				if (rn != 0)
				{
					if (rn == 1)
					{
						result = result + "x" + std::to_string(i + 1) ;
					}
					else
					{
						result = result + "x" + std::to_string(i + 1) + "^" + std::to_string(rn);
					}
				}
			}
			if (coef == -1)
			{
				result = "-" + result;
			}
			else if (coef != 1)
			{
				int roundCoef = round(coef * 100) / 100;
				result = std::to_string(roundCoef) + "*" + result;
			}
		}
		return result;
	}

	Monom getMonom()
	{
		return *this;
	}
};

