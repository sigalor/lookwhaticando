#include "Coefficient.hpp"



Coefficient::Coefficient(double newXExp, std::initializer_list<Variable> newFactors) : xExp(newXExp)
{
	factors.insert(factors.begin(), newFactors.begin(), newFactors.end());
}

void Coefficient::derive()
{
	factors.push_back(Variable(xExp));
	xExp -= 1.0;
}

void Coefficient::insert(double x)
{
	double temp = pow(x, xExp);
	xExp = 0.0;
	factors.push_back(Variable(temp));
}

bool Coefficient::hasVariable(unsigned int id)
{
	for(Variable& v : factors)
		if(v.getId()  &&  v.getId().value() == id)
			return true;
	return false;
}

double Coefficient::getNumericalFactor()
{
	double ret = 0.0;
	for(Variable& v : factors)
		if(v.getValue())
			ret = v.getValue().value();
	return ret;
}

bool Coefficient::clean()																							//returns true if this coefficient can be removed (one of its factors is 0 so it becomes 0)
{
	double temp = 1.0;
	auto it = factors.begin();
	
	while(it != factors.end())
	{
		it->clean();
		if(it->getValue())
		{
			temp *= it->getValue().value();
			it = factors.erase(it);
			continue;
		}
		++it;
	}
	if(temp == 0.0)
		return true;
	factors.insert(factors.begin(), Variable(temp));
	return false;
}

std::string Coefficient::asString()
{
	std::ostringstream stm;
	unsigned int i = 0;
	
	for(Variable& v : factors)
	{
		if(v.getValue())
			stm << v.getValue().value();
		else
			stm << static_cast<char>('a' + v.getId().value());
		if(i != factors.size()-1)
			stm << "*";
		i++;
	}
	if(xExp != 0.0)
	{
		if(factors.size() != 0)
			stm << "*";
		stm << "x";
		if(xExp != 1.0)
			stm << "^" << xExp;
	}
	
	return stm.str();
}
