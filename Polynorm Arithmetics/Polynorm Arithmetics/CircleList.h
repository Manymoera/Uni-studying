#pragma once
#include "Monom.h"

class CircleList
{
private:
	Monom* head;
public:
	CircleList()
	{
		head = new Monom();
	}	

	CircleList(Monom _monom)
	{
		head = new Monom();
		this->AddMonom(_monom);
	}

	CircleList(const CircleList& other)
	{
		if (other.head == (other.head->getNext()))
		{
			head = new Monom;
		}
		else
		{
			head = new Monom(other.head->getCoef(), other.head->getSV());
			
			Monom* currentOther = other.head->getNext();
			Monom* currentNew = head;

			while (currentOther != other.head)
			{
				Monom* newMonom = new Monom(currentOther->getCoef(), currentOther->getSV());
				currentNew->setNext(newMonom);
				currentNew = newMonom;
				currentOther = currentOther->getNext();
			}

			currentNew->setNext(head);
		}
	}
	
	~CircleList()
	{
		Monom* current = head->getNext();

		while (current != head)
		{
			head->setNext(current->getNext());
			current->setNext(nullptr);
			delete current;
			current = head->getNext();
		}

		delete head;
	}

	void AddMonom(Monom other)
	{
		Monom* current = head->getNext();
		Monom* previous = head;

		while ((current->getSV()) > (other.getSV()))
		{
			previous = current;
			current = current->getNext();
		}

		if ((current->getSV()) < (other.getSV()))
		{
			Monom* newMonom = new Monom(other.getCoef(), other.getSV());

			newMonom->setNext(previous->getNext());
			previous->setNext(newMonom);
		}
		else
		{
			if (current->getCoef() + other.getCoef() != 0)
			{
				current->setCoef(current->getCoef() + other.getCoef());
			}
			else
			{
				previous->setNext(current->getNext());
				delete current;
			}
		}
	}

	std::string CircleListToString(int maxpw, int count)
	{
		std::string str = "";

		if (head == head->getNext())
		{
			str = "0";
		}

		Monom* current = head->getNext();

		while (current != head)
		{
			std::string s;
			if (current->getCoef() > 0)
			{
				s = current->MonomToString(maxpw, count);
			}
			else if (current->getCoef() < 0)
			{
				s = "(" + current->MonomToString(maxpw, count) + ")";
			}

			if (s[0] != '0')
			{
				str = str + " " + "+" + " " + s;
			}
			else
			{
				str = str;
			}
			current = current->getNext();
		}
		if (str != "0")
		{
			str.erase(0, 3);

			if (str[str.length() - 2] == '+')
			{
				str.erase(str.length() - 2);
			}
		}



		return str;
	}

	CircleList& operator=(const CircleList& other)
	{
		Monom* current = head;
		while (current != nullptr && (current->getNext()) != head)
		{
			Monom* temp = current;
			current = current->getNext();
			delete temp;
		}

		if (current != nullptr)
		{
			delete current;
		}

		head = nullptr;

		if (other.head != nullptr)
		{
			head = new Monom(other.head->getCoef(), other.head->getSV());

			Monom* currentOther = other.head->getNext();
			Monom* currentNew = head;

			while (currentOther != other.head)
			{
				Monom* newMonom = new Monom(currentOther->getCoef(), currentOther->getSV());
				currentNew->setNext(newMonom);
				currentNew = newMonom;
				currentOther = currentOther->getNext();
			}
			
			currentNew->setNext(head);
		}
		return *this;
	}

	CircleList operator+(const CircleList& other)
	{
		CircleList result(*this);

		Monom* current = other.head->getNext();

		while (current != other.head)
		{
			Monom temp(current->getCoef(), current->getSV());
			result.AddMonom(temp);
			current = current->getNext();
		}

		return result;
	}

	CircleList operator-(const CircleList& other)
	{
		CircleList result(*this);

		Monom* current = other.head->getNext();

		while (current != other.head)
		{
			Monom temp((-(current->getCoef())), current->getSV());
			result.AddMonom(temp);
			current = current->getNext();
		}
		return result;
	}

	CircleList operator*(int k)
	{
		CircleList result;
		if (k != 0)
		{
			Monom* current = head->getNext();
			while (current != head)
			{
				Monom temp(((current->getCoef()) * k), current->getSV());
				result.AddMonom(temp);
				current = current->getNext();
			}
		}
		return result;
	}

	CircleList Multiply(CircleList other, int _maxpw, int _count)
	{
		CircleList Res;
		Monom* current = head->getNext();
		while(current != head)
		{
			Monom* tmp_current = other.head->getNext();
			while (tmp_current != other.head)
			{
				Monom p = (*current).Multiply(*tmp_current, _maxpw, _count);
				if (p.getSV() != -1)
				{
					Res.AddMonom(p);
					tmp_current = tmp_current->getNext();
				}
			}
			current = current->getNext();
		}
		return Res;
	}
};