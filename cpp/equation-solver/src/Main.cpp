#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

#include "Formula.hpp"
#include "Condition.hpp"
#include "LinearSystem.hpp"



void quit(int code=0)
{
	std::cout << "\n\nFinished.\n";
	exit(code);
}

int main()
{
	std::vector<std::string>	conditionsStrings;
	std::string					temp;
	std::vector<Condition>		conditions;
	std::vector<Formula>		formulas;
	LinearSystem				matrix;
	std::vector<double>			solutions;
	
	std::cout << "Please enter all conditions and finish by entering END\n";
	std::cout << "Examples: f(0.3)=-3.6\n";
	std::cout << "          f'(2.5)=1\n";
	std::cout << "          f''(0)=3\n\n";
	
	do
	{
		std::cout << "Condition " << conditionsStrings.size()+1 << ": ";
		std::getline(std::cin, temp);
		conditionsStrings.push_back(temp);
	}
	while(temp != "END");
	conditionsStrings.pop_back();
	
	//check if enough conditions are given (at least 2 for having a linear equation)
	if(conditionsStrings.size() < 2)
	{
		std::cout << "\nError: You have to enter at least 2 conditions.";
		quit(1);
	}
	
	//try to interpret all conditions
	unsigned int i = 1, numWarnings = 0;
	for(std::string& cs : conditionsStrings)
	{
		try
			{ conditions.push_back(Condition(cs)); }
		catch(const std::runtime_error& e)
			{ std::cout << "\nWarning: Unable to interpret condition " << i << " (" << cs << "), ignored it (" << e.what() << ")."; numWarnings++; }
		i++;
	}
	if(numWarnings != 0)
		std::cout << "\n";
	
	//check if enough conditions were successfully interpreted (like above)
	if(conditions.size() < 2)
	{
		std::cout << "\nError: You have to enter at least 2 interpretable conditions.";
		quit(1);
	}
	
	//generate base formulas for all conditions (in the beginning they all are of (number of conditions - 1)th degree) and use the interpreted conditions with them
	std::cout << "\nResolved formulas:";
	formulas = std::vector<Formula>(conditions.size(), Formula(conditions.size() - 1));
	for(std::size_t i=0; i<conditions.size(); i++)
	{
		formulas[i].insert(conditions[i]);
		std::cout << "\n    " << formulas[i].asString();
	}
	
	//create matrix from formulas
	std::cout << "\n\nSystem of linear equations:";
	matrix.load(formulas);
	std::cout << matrix.asString();
	
	//solve system of linear equations
	std::cout << "\n\nSolutions:";
	try
		{ matrix.solve(); }
	catch(const std::runtime_error& e)
	{
		std::cout << "\nError: Linear system is not solvable (" << e.what() << ").";
		quit(1);
	}
	
	//output solutions
	solutions = matrix.getSolutions();
	for(std::size_t i=0; i<solutions.size(); i++)
		std::cout << "\n    " << static_cast<char>('a' + i) << " = " << solutions[i];
	
	//quit the program with a "Finished." message
	quit(0);
	
	return 0;
}
