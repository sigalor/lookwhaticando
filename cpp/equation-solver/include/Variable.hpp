#pragma once



#include <boost/optional.hpp>



class Variable
{
	private:
		static unsigned int						nextId;
		boost::optional<unsigned int>			id;
		boost::optional<double>					value;
	
	public:
		Variable();
		Variable(double);
		Variable(int);
		Variable(unsigned int);

		void									clean();
		boost::optional<unsigned int>			getId();
		boost::optional<double>					getValue();
};
