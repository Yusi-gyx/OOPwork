#pragma once
#include <string>

class PayStrategy {								
public:
	virtual ~PayStrategy() {}
	virtual double pay(std::string name, double money) = 0;
};


class NormalStrategy : public PayStrategy {	
public:
	double pay(std::string name, double money) override
	{
		return money;
	}
};

class SwiftStrategy : public PayStrategy {	
public:
	double pay(std::string name, double money) override
	{
		if(money <= 10000) return money - 10;
		else 
		{
			if(money * 0.001 > 20) return money - 20;
		}
		return money * 0.999;
	}
};

class BitcoinStrategy : public PayStrategy {	
public:
	double pay(std::string name, double money) override
	{
		return money - 0.01 * (name.length() + 8);
	}
};
