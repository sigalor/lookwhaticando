#pragma once



#include <string>
#include <stdexcept>
#include <algorithm>
#include <boost/lexical_cast.hpp>



class Condition
{
	private:
		double									x, y;
		unsigned int							derivativeId;
	
	public:
		Condition(std::string);
		Condition(double, double, unsigned int);
		
		void									interpret(std::string);
		double									getX();
		double									getY();
		unsigned int							getDerivativeId();
};
