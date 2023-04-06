#pragma once
#include <vector>
#include <string>

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