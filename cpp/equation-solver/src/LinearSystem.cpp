#include "LinearSystem.hpp"



LinearSystem::LinearSystem() { }

LinearSystem::LinearSystem(std::vector<Formula>& formulas)
{
	load(formulas);
}

void LinearSystem::load(std::vector<Formula>& formulas)
{
	for(Formula& f : formulas)
	{
		std::vector<double> row;
		for(std::size_t i=0; i<formulas.size(); i++)
			row.push_back(f.getNumericalFactor(i));
		row.push_back(f.getResult());
		matrix.push_back(row);
	}
}

void LinearSystem::solve()
{
	int n = static_cast<int>(matrix.size());
	
	//generate upper triangular matrix (http://martin-thoma.com/solving-linear-equations-with-gaussian-elimination/)
	for(int i=0; i<n; i++)
	{
		//search for maximum in this column
		double maxEl = abs(matrix[i][i]);
		int maxRow = i;
		for(int k=i+1; k<n; k++)
		{
			if(abs(matrix[k][i]) > maxEl)
			{
				maxEl = abs(matrix[k][i]);
				maxRow = k;
			}
		}

		//swap maximum row with current row (column by column)
		for(int k=i; k<n+1;k++)
		{
			double tmp = matrix[maxRow][k];
			matrix[maxRow][k] = matrix[i][k];
			matrix[i][k] = tmp;
		}

		//make all rows below this one 0 in current column
		for (int k=i+1; k<n; k++)
		{
			if(matrix[i][i] == 0.0)
				throw std::runtime_error("Generation of upper triangular matrix failed");
			double c = -matrix[k][i]/matrix[i][i];
			for(int j=i; j<n+1; j++)
			{
				if(i==j)
					matrix[k][j] = 0;
				else
					matrix[k][j] += c * matrix[i][j];
			}
		}
	}
	
	//apply backward substitution
	for(int j=n-1; j>=0; j--)
	{
		double sum = 0.0;
		for(int i=j+1; i<n; i++)
			sum += matrix[j][i]*matrix[i][n];
		if(matrix[j][j] == 0.0)
			throw std::runtime_error("Backward substitution failed");
		matrix[j][n] = (matrix[j][n]-sum) / matrix[j][j];
		for(int i=0; i<n; i++)
			matrix[j][i] = (i==j ? 1.0 : 0.0);
		solutions.insert(solutions.begin(), matrix[j][n]);
	}
}

std::vector<double>& LinearSystem::getSolutions()
{
	return solutions;
}

std::string LinearSystem::asString()
{
	std::ostringstream stm;
	
	for(std::vector<double>& y : matrix)
	{
		unsigned int i = 0;
		stm << "\n    ";
		for(double& d : y)
		{
			stm << std::setw(13) << d;
			if(i != y.size()-1)
				stm << " | ";
			i++;
		}
	}
	
	return stm.str();
}
