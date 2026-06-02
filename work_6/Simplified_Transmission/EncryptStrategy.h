#pragma once
# include <string>

class EncryptStrategy{
public:
	virtual std::string encode(std::string mes) = 0;
};

class InsertStrategy: public EncryptStrategy{
public:
	std::string encode(std::string mes) override
	{
		std::string temp;
		for(int i = 0 ; i < mes.length() ; i ++)
		{
			temp += mes [i];
			temp += '#';
		}
		return temp;
	}
};

class InvertStrategy: public EncryptStrategy{
public:
	std::string encode(std::string mes) override
	{
		std::string temp;
		for(int i = mes.length() - 1; i >= 0 ; i --)
		{
			temp += mes [i];
		}
		return temp;
	}
};