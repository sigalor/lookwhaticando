#include "Condition.hpp"



Condition::Condition(std::string str)
{
	interpret(str);
}

Condition::Condition(double newX, double newY, unsigned int newDerivativeId) : x(newX), y(newY), derivativeId(newDerivativeId) { }

void Condition::interpret(std::string str)
{
	try
	{
		if(str.at(0) != 'f')
			throw std::runtime_error("The first letter needs to be 'f'");
	}
	catch(const std::out_of_range& e)
	{
		throw std::runtime_error("Cannot look at the first letter");
	}
	
	
	derivativeId = 0;
	auto apostr = std::find(str.begin(), str.end(), '\'');
	while(*apostr == '\''  &&  apostr != str.end())
	{
		derivativeId++;
		apostr++;
	}
	
	
	auto openPar = std::find(str.begin(), str.end(), '(');
	if(openPar == str.end())
		throw std::runtime_error("Missing opening parenthesis after 'f'");
	auto closePar = std::find(str.begin(), str.end(), ')');
	if(closePar == str.end())
		throw std::runtime_error("Missing closing parenthesis after 'f'");
	
	auto openParIdx = std::distance(str.begin(), openPar);
	auto closeParIdx = std::distance(str.begin(), closePar);
	if(openParIdx > closeParIdx)
		throw std::runtime_error("Parenthesis mismatch after 'f'");
	std::string xStr = str.substr(openParIdx+1, closeParIdx-openParIdx-1);
	
	try
		{ x = boost::lexical_cast<double>(xStr); }
	catch(const boost::bad_lexical_cast& e)
		{ throw std::runtime_error("Cannot convert '" + xStr + "' to a number"); }
		
		
	auto equalSign = std::find(closePar, str.end(), '=');
	if(equalSign == str.end())
		throw std::runtime_error("Missing equal sign");
	
	auto equalSignIdx = std::distance(str.begin(), equalSign);
	std::string yStr = str.substr(equalSignIdx+1);
	
	try
		{ y = boost::lexical_cast<double>(yStr); }
	catch(const boost::bad_lexical_cast& c)
		{ throw std::runtime_error("Cannot convert '" + yStr + "' to a number"); }
		
		
	//cout << "\nFinished interpreting!    x = " << x << ", y = " << y << ", derivativeId = " << derivativeId;
}

double Condition::getX()
{
	return x;
}

double Condition::getY()
{
	return y;
}

unsigned int Condition::getDerivativeId()
{
	return derivativeId;
}
