#pragma once



#include <cmath>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>

#include "Formula.hpp"



class LinearSystem
{
	private:
		std::vector<std::vector<double>>		matrix;
		std::vector<double>						solutions;
		
	public:
		LinearSystem();
		LinearSystem(std::vector<Formula>&);
		
		void									load(std::vector<Formula>&);
		void									solve();
		std::vector<double>&					getSolutions();
		std::string								asString();
};
