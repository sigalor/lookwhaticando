#pragma once



#include <string>
#include <vector>
#include <sstream>
#include <initializer_list>

#include "Variable.hpp"



class Coefficient
{
	private:
		double									xExp;
		std::vector<Variable>					factors;
		
	public:
		Coefficient(double, std::initializer_list<Variable> = {});
	
		void									derive();
		void									insert(double);
		bool									hasVariable(unsigned int);
		double									getNumericalFactor();
		bool									clean();
		std::string								asString();
};
