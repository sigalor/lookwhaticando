#include "Formula.hpp"



Formula::Formula(std::initializer_list<Coefficient> newSummands) : result(boost::none)
{
	summands.insert(summands.begin(), newSummands.begin(), newSummands.end());
	clean();
}

Formula::Formula(int n) : result(boost::none)																		//constructs a formula of nth degree (e.g. n=3 --> 0 = a*x^3 + b*x^2 + c*x + d)
{
	for(int i=0; i<=n; i++)
		summands.push_back(Coefficient(static_cast<double>(n-i), { Variable(i) }));
}

void Formula::derive()
{
	for(Coefficient& c : summands)
		c.derive();
	clean();
}


void Formula::derive(int n)																							//derive this formula n times
{
	for(int i=0; i<n; i++)
		derive();
}

void Formula::insert(double x, double y)
{
	result = y;
	for(Coefficient& c : summands)
		c.insert(x);
	clean();
}

void Formula::insert(Condition& c)
{
	derive(c.getDerivativeId());
	insert(c.getX(), c.getY());
}

double Formula::getNumericalFactor(unsigned int id)																	//get the numerical factor of the coefficient that has a variable with the id 'id' in it
{
	for(Coefficient& c : summands)
		if(c.hasVariable(id))
			return c.getNumericalFactor();
	return 0.0;
}

void Formula::clean()
{
	auto it = summands.begin();
	while(it != summands.end())
	{
		if(it->clean())
		{
			it = summands.erase(it);
			continue;
		}
		++it;
	}
}

std::string Formula::asString()
{
	std::ostringstream stm;
	unsigned int i = 0;
	
	if(result)
		stm << result.value();
	else
		stm << "y";
	stm << " = ";
	
	if(summands.size() == 0)
	{
		stm << "0";
		return stm.str();
	}
	for(Coefficient& c : summands)
	{
		stm << c.asString();
		if(i != summands.size()-1)
			stm << " + ";
		i++;
	}
	
	return stm.str();
}

double Formula::getResult()
{
	if(result)
		return result.value();
	return 0.0;
}
