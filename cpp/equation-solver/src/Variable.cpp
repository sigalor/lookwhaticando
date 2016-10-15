#include "Variable.hpp"



unsigned int Variable::nextId = 0;

Variable::Variable() : id(boost::none), value(boost::none)
{
	id = nextId;
	nextId++;
}

Variable::Variable(double newValue) : id(boost::none), value(newValue) { }

Variable::Variable(int newId) : Variable(static_cast<unsigned int>(newId)) { }

Variable::Variable(unsigned int newId) : id(newId), value(boost::none) { }

void Variable::clean()
{
	if(value)
		id = boost::none;
}

boost::optional<unsigned int> Variable::getId()
{
	return id;
}

boost::optional<double> Variable::getValue()
{
	return value;
}
