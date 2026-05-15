#ifndef __COMPUTER_H__
#define __COMPUTER_H__

#include <iostream>
#include <string>
using namespace std;

class Computer
{
private:
	string name;
	int num = 0;
	int price = 0;

public:
	bool operator< (const Computer& Computer);
	Computer& operator++ ();
	Computer& operator-- ();
	friend ostream& operator<< (ostream& out, const Computer& computer);
	string getName() const
	{
		return name ;
	}
	int getNum() const 
	{
		return num ;
	}
	int getPrice() const
	{
		return price ;
	}
	void addInfo(string name_M , int num_M , int price_M) ;
	void setPrice(int price_M)
	{
		price = price_M ;
	}
};

#endif
