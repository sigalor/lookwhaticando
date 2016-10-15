#pragma once



#include <string>
#include <vector>
#include <sstream>
#include <initializer_list>
#include <boost/optional.hpp>

#include "Coefficient.hpp"
#include "Condition.hpp"



class Formula
{
	private:
		boost::optional<double>					result;
		std::vector<Coefficient>				summands;
		
	public:
		Formula(std::initializer_list<Coefficient> = {});
		Formula(int);
		
		void									derive();
		void									derive(int);
		void									insert(double, double);
		void									insert(Condition&);
		double									getNumericalFactor(unsigned int);
		void									clean();
		std::string								asString();
		double									getResult();
};
