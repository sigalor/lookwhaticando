#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cstdio>
#include <cstring>
//#include <conio.h>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/replace.hpp>

#define LET_AND_OP '&'
#define LET_OR_OP  '|'
#define LET_NOT_OP '!'

using namespace std;
using namespace boost;

string appName;
bool   debug = false;

class LET_TERM
{
	private:
		string			rawTerm;
		vector<char>	variables;
		
		static bool isBracket(char c)
		{
			if(c == '('  ||  c == ')')
				return true;
			return false;
		}
		
		static bool is2OperandOp(char c)
		{
			if(c == LET_AND_OP  ||  c == LET_OR_OP)
				return true;
			return false;
		}
		
		static bool isBoolNum(char c)
		{
			if(c == '0'  ||  c == '1')
				return true;
			return false;
		}
		
		static bool isLetter(char c)
		{
			if((c >= 'A'  &&  c <= 'Z')  ||  (c >= 'a'  &&  c <= 'z'))
				return true;
			return false;
		}
		
		static bool isLetterOrBool(char c)
		{
			if(isLetter(c)  ||  isBoolNum(c))
				return true;
			return false;
		}
		
		static bool isBadChar(char c)
		{
			if(isLetter(c)  ||  isBracket(c)  ||  isBoolNum(c)  ||  is2OperandOp(c)  ||  c == LET_NOT_OP)
				return false;
			return true;
		}
		
		static void solveMostInnerBracket(string &term)
		{
			unsigned long partBegin = 0;
			unsigned long partEnd   = term.size()-1;
			string        part;
			
			for(unsigned long i=0; i<term.size(); i++)
			{
				if(term[i] == '(')
					partBegin = i+1;
				else if(term[i] == ')')
				{
					partEnd = i-1;
					break;
				}
			}
			
			part = term.substr(partBegin, partEnd-partBegin+1);
			
			//Solve NOT operations
			for(unsigned long i=0; i<part.size()-1; i++)
			{
				if(part[i] == LET_NOT_OP)
				{
					part.erase(i, 1);
					part[i] = (!(part[i]-'0')) + '0';
				}
			}
			if(debug)
				printf("    Step 2.1: %s\n", part.c_str());
			
			//Solve AND operations
			for(unsigned long i=1; i<part.size()-1; i++)
			{
				if(part[i] == LET_AND_OP)
				{
					char sol = ((part[i-1]-'0') & (part[i+1]-'0')) + '0';
					part[i-1] = sol;
					part.erase(i, 2);
				}
			}
			if(debug)
				printf("    Step 2.2: %s\n", part.c_str());
			
			//Solve OR operations
			for(unsigned long i=1; i<part.size()-1; i++)
			{
				if(part[i] == LET_OR_OP)
				{
					char sol = ((part[i-1]-'0') | (part[i+1]-'0')) + '0';
					part[i-1] = sol;
					part.erase(i, 2);
				}
			}
			if(debug)
				printf("    Step 2.3: %s\n", part.c_str());
			
			term.replace(term.begin()+partBegin, term.begin()+partEnd+1, part);
		}
		
		static void stripBrackets(string &term)
		{
			replace_all(term, "(0)", "0");
			replace_all(term, "(1)", "1");
		}
		
	public:
		void set(string newRawTerm)
		{
			rawTerm = newRawTerm;
			rawTerm.erase(remove_if(rawTerm.begin(), rawTerm.end(), &isBadChar), rawTerm.end());
			replace_all(rawTerm, "()", "");
			if(rawTerm != newRawTerm)
				printf("%s: info:  stripped invalid characters, new expression: %s\n", appName.c_str(), rawTerm.c_str());
		}
		
		bool parse()
		{
			int brackets = 0;
			
			//Two subsequent letters are not allowed
			for(unsigned long i=0; i<rawTerm.size()-1; i++)
			{
				if(isLetterOrBool(rawTerm[i])  &&  isLetterOrBool(rawTerm[i+1]))
				{
					printf("%s: error: parsing error near character %ld (\"%c%c\" is invalid)\n", appName.c_str(), i, rawTerm[i], rawTerm[i+1]);
					return false;
				}
			}
			
			//Count number of open and closed brackets, detect possible inequality
			for(unsigned long i=0; i<rawTerm.size(); i++)
			{
				if(rawTerm[i] == '(')
					brackets++;
				else if(rawTerm[i] == ')')
					brackets--;
			}
			if(brackets != 0)
			{
				printf("%s: error: unequal number of open and closed brackets\n", appName.c_str());
				return false;
			}
			
			//Check AND and OR correctness (only "A|B", "A|!", "A|(", ")|(", ")|!" and ")|B" are correct [also & instead of | and 0 or 1 instead of A or B, respectively])
			for(unsigned long i=0; i<rawTerm.size(); i++)
			{
				if(is2OperandOp(rawTerm[i]))
				{
					if(i == 0  ||  i == rawTerm.size()-1)
					{
						printf("%s: error: parsing error near character %ld (\"%c%c\" is invalid)\n", appName.c_str(), i, rawTerm[i-(i==0?0:1)], rawTerm[i+(i==0?1:0)]);
						return false;
					}
					if(!((isLetterOrBool(rawTerm[i-1])  &&  isLetterOrBool(rawTerm[i+1]))  ||  (isLetterOrBool(rawTerm[i-1])  &&  rawTerm[i+1] == LET_NOT_OP)  ||  (isLetterOrBool(rawTerm[i-1])  &&  rawTerm[i+1] == '(')  ||  (rawTerm[i-1] == ')'  &&  rawTerm[i+1] == '(')  ||  (rawTerm[i-1] == ')'  &&  rawTerm[i+1] == LET_NOT_OP)  ||  (rawTerm[i-1] == ')'  &&  isLetterOrBool(rawTerm[i+1]))))
					{
						printf("%s: error: parsing error near character %ld (\"%c%c%c\" is invalid)\n", appName.c_str(), i, rawTerm[i-1], rawTerm[i], rawTerm[i+1]);
						return false;
					}
				}
			}
			
			//Check NOT correctness (only "!A" and "!(" are correct, but not "A!B")
			for(unsigned long i=0; i<rawTerm.size(); i++)
			{
				if(rawTerm[i] == LET_NOT_OP)
				{
					if(i == rawTerm.size()-1)
					{
						printf("%s: error: parsing error near character %ld (\"%c\" is invalid)\n", appName.c_str(), i, rawTerm[i]);
						return false;
					}
					if(i == 0)
					{
						if(!(isLetterOrBool(rawTerm[i+1])  ||  rawTerm[i+1] == '('))
						{
							printf("%s: error: parsing error near character %ld (\"%c%c\" is invalid)\n", appName.c_str(), i, rawTerm[i], rawTerm[i+1]);
							return false;
						}
					}
					else
					{
						if(!(isLetterOrBool(rawTerm[i+1])  ||  rawTerm[i+1] == '('))
						{
							printf("%s: error: parsing error near character %ld (\"%c%c\" is invalid)\n", appName.c_str(), i, rawTerm[i], rawTerm[i+1]);
							return false;
						}
						if(!(is2OperandOp(rawTerm[i-1])  ||  rawTerm[i-1] == '('))
						{
							printf("%s: error: parsing error near character %ld (\"%c%c\" is invalid)\n", appName.c_str(), i, rawTerm[i-1], rawTerm[i]);
							return false;
						}
					}
				}
			}
			
			//Get variables
			for(unsigned long i=0; i<rawTerm.size(); i++)
			{
				if(isLetter(rawTerm[i])  &&  find(variables.begin(), variables.end(), rawTerm[i]) == variables.end())
					variables.push_back(rawTerm[i]);
			}
			/*if(variables.size() == 0)
			{
				printf("%s: error: no variables recognized\n", appName.c_str());
				return false;
			}*/
			
			return true;
		}
		
		int evaluate(vector<bool> values)
		{
			string filledTerm = rawTerm;
			
			if(values.size() != variables.size())
			{
				printf("%s: error: unequal number of recognized (%lu) and provided (%lu) variables\n", appName.c_str(), variables.size(), values.size());
				return -1;
			}
			
			for(unsigned long i=0; i<values.size(); i++)
				replace_all(filledTerm, lexical_cast<string>(variables[i]), lexical_cast<string>(values[i]));
			
			//Continue: solve most inner bracket (not->and/or)
			while(filledTerm.size() != 1)
			{
				if(debug)
					printf("Step 1: %s\n", filledTerm.c_str());
				
				solveMostInnerBracket(filledTerm);
				if(debug)
					printf("Step 2: %s\n", filledTerm.c_str());
				
				stripBrackets(filledTerm);
				if(debug)
				{
					printf("Step 3: %s\n\n", filledTerm.c_str());
					//getch();
				}
				
			}
			
			return filledTerm[0]-'0';
		}
		
		vector<char> *getVariables()
		{
			return &variables;
		}
};

int main(int argc, char **argv)
{
	LET_TERM		term;
	string			rawTerm;
	vector<bool>	values;
	vector<bool>	results;

	//Name of executable is first provided argument
	appName = argv[0];
	
	//If no other arguments are provided, output usage information
	if(argc == 1)
	{
		printf("Usage: %s [term]\n", appName.c_str());
		exit(0);
	}
	
	//Create raw term by reading second argument
	rawTerm = argv[1];
	
	//If third argument is "TRUE", print debug information
	if(argc >= 3  &&  (string)argv[2] == "TRUE")
		debug = true;
	
	//Create and parse term
	term.set(rawTerm);
	if(!term.parse())
	{
		printf("%s: error: parsing failed\n", appName.c_str());
		exit(1);
	}
	
	//Print table header
	printf("\n");
	for(unsigned long i=0; i<term.getVariables()->size(); i++)
		printf(" %c |", term.getVariables()->at(i));
	printf("\n");
	for(unsigned long i=0; i<=term.getVariables()->size(); i++)
	{
		printf("---");
		if(i != term.getVariables()->size())
			printf("+");
	}
	printf("\n");
	
	//Evaluate and print all true-false-combinations of all variables
	for(unsigned long i=0; i<(unsigned long)1<<term.getVariables()->size(); i++)
	{
		values.clear();
		for(unsigned long j=0; j<term.getVariables()->size(); j++)
			values.push_back((bool)((i&(1<<j)) >> j));
		reverse(values.begin(), values.end());
		
		results.push_back(term.evaluate(values));
		if(results.back() == -1)
		{
			printf("%s: error: evaluation failed\n", appName.c_str());
			exit(1);
		}
		
		for(unsigned long j=0; j<term.getVariables()->size(); j++)
			printf(" %d |", (int)values[j]);
		printf(" %d\n", (int)results.back());
	}
	
	printf("\n% 3.2f%% true\n", (float)count(results.begin(), results.end(), true)/(float)results.size()*100.0f);
	
	return 0;
}
