#pragma once
# include <string>

class VerificationStrategy{
public:
	virtual std::string verify(std::string mes) = 0;
};

class PrefixStrategy: public VerificationStrategy{
public:
	std::string verify(std::string mes) override
	{
		std::string temp;
		for(int i = 0 ; i < 3 ; i ++)
		{
			temp += mes [i];
		}
		return temp;
	}
};

class IntervalStrategy: public VerificationStrategy{
public:
	std::string verify(std::string mes) override
	{
		std::string temp;
		bool whether_catch = true;
		for(int i = 0 ; i < mes.length() ; i ++)
		{
			if(whether_catch)
			{
				temp += mes [i];
				whether_catch = false;
				continue;
			}
			whether_catch = true;
		}
		return temp;
	}
};
