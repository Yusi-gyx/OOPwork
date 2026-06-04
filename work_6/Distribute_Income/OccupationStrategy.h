#pragma once

class OccupationStrategy {								
public:
	virtual ~OccupationStrategy() {}
	virtual double getSalary(double base, double bonus, double level) = 0;
};

class SalesmanStrategy : public OccupationStrategy {
public:
	double getSalary(double base, double bonus, double level) override 
	{
		double salary = base;
		if(level < 60) {}
		else if(level < 70)
		{
			salary += bonus * 0.6;
		}
		else if(level < 80)
		{
			salary += bonus * 0.7;
		}
		else salary += bonus;

		return salary;
	}
};

class DeveloperStrategy : public OccupationStrategy {	
public:
	double getSalary(double base, double bonus, double level) override
	{
		double salary = base;
		double ratio = 0;
		ratio = level / 100;
		salary += bonus * ratio;
		return salary;
	}
};