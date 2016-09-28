// Name: John Padgett
// Class: CS3500 - Programming Languages & Translators
// Assignment 3 - Recursive Descent Parser
// April 19th, 2016
// progparser.cpp

#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>
using namespace std;

//Declarations
string token;
bool Expression();
bool StatementSequence();

void getToken()
{
	cin >> token;
	return;
}

inline bool isDigit(char c)
{
	return('0' <= c && c <= '9');
}

inline bool isAlpha(char c)
{
	char alph[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	
	return(strchr(alph, c) != NULL);
}

bool isInteger(string S) //Lexical Analyzer for Integers
{
	int state = 0;
	int i = 0;
	bool isValid;
	
	while(i < S.length())
	{
		switch(state)
		{
			case 0:
				if(S[i] == '+' || S[i] == '-')
				{
					state = 1;
				}	
				else if(isDigit(S[i]))
				{
					state = 2;
				}
				else
				{
					state = -1;
				}
				break;
			case 1:
				if(isDigit(S[i]))
				{
					state = 2;
				}
				else
				{
					state = -1;
				}
				break;
			case 2:
				if(isDigit(S[i]))
				{
					state = 2;
				}
				else
				{
					state = -1;
				}
				break;
			default:
				i = S.length();
				break;
		} //end of switch-case
				
		i++;
	}
	
	if(i == S.length() && state == 2)
		isValid = true;
	else
		isValid = false;
	
	
	return isValid;
}

bool isDecimal(string S) // Lexical Analyzer for Decimals
{
	int state = 0;
	int i = 0;
	bool isValid;
	
	while(i < S.length())
	{
		switch(state)
		{
			case 0:
				if(S[i] == '+' || S[i] == '-')
				{
					state = 1;
				}	
				else if(isDigit(S[i]))
				{
					state = 1;
				}
				else
				{
					state = -1;
				}
				break;
			case 1:
				if(isDigit(S[i]))
				{
					state = 1;
				}
				else if(S[i] == '.')
				{
					state = 2;
				}
				else
				{
					state = -1;
				}
				break;
			case 2:
				if(isDigit(S[i]))
				{
					state = 3;
				}
				else
				{
					state = -1;
				}
				break;
			case 3:
				if(isDigit(S[i]))
				{
					state = 3;
				}
				else
				{
					state = -1;
				}
				break;
			default:
				i = S.length();
				break;
		} //end of switch-case
				
		i++;
	}
	if(i == S.length() && state == 3)
		isValid = true;
	else
		isValid = false;
	
	return isValid;
}

bool isString(string S) // Lexical Anaylzer for Strings
{
	bool isValid;
	int state = 0;
	int i = 0;
	
	while(i < S.length())
	{
		switch(state)
		{
			case 0:
				if(S[i] == '"')
				{
					state = 1;
				}
				else
				{
					state = -1;
				}
				break;
			case 1:
				if(S[i] == ' ')
				{
					state = -1;
				}
				else
				{
					state = 2;
				}
				break;
			case 2:
				if(S[i] == '"')
				{
					state = 3;
				}
				else if(S[i] == ' ')
				{
					state = -1;
				}
				else
				{
					state = 2;
				}
				break;
			case 3:
				state = -1;
				break;
			default:
				i = S.length();
				break;
		}
		i++;
	}
	if(i == S.length() && state == 3)
		isValid = true;
	else
		isValid = false;
	
	return isValid;
}

bool isIdent(string S) // Lexical Analyzer for Identifiers
{
	bool isValid;
	int state = 0;
	int i = 0;
	
	while(i < S.length())
	{
		switch(state)
		{
			case 0:
				if(isAlpha(S[i]))
				{
					state = 1;
				}
				else
				{
					state = -1;
				}
				break;
			case 1:
				if(isAlpha(S[i]))
				{
					state = 1;
				}
				else if(isDigit(S[i]))
				{
					state = 1;
				}
				else
				{
					state = -1;
				}
				break;
			default:
				i = S.length();
				break;
		}
		i++;
	}
	
	if(state == 1 && i == S.length() && (S != "or" && S!= "and" && S != "lt" 
		&& S != "gt" && S != "eq" && S != "print" && S != "inc" && S != "ret" 
		&& S != "if" && S != "fi" && S != "else" && S != "while" 
		&& S != "elihw" && S != "defprog" && S != "blip" && S != "blorp"))
	{
		isValid = true;
	}
	else
		isValid = false;
	
	return isValid;
}

bool Relation()
{
	bool isValid = false;
	
	if(token == "lt")
	{
		getToken();
		isValid = true;
	}
	else if(token == "gt")
	{
		getToken();
		isValid = true;
	}
	else if(token == "eq")
	{
		getToken();
		isValid = true;
	}
	
	return isValid;
}

bool AddOperator()
{
	bool isValid = false;
	
	if(token == "+")
	{
		getToken();
		isValid = true;
	}
	else if(token == "-")
	{
		getToken();
		isValid = true;
	}
	else if(token == "or")
	{
		getToken();
		isValid = true;
	}
	
	return isValid;
}

bool MulOperator()
{
	bool isValid = false;
	
	if(token == "*")
	{
		getToken();
		isValid = true;
	}
	else if(token == "/")
	{
		getToken();
		isValid = true;
	}
	else if(token == "and")
	{
		getToken();
		isValid = true;
	}
	
	return isValid;
}

bool Factor()
{
	bool isValid = false;
	
	if(isInteger(token))
	{
		getToken();
		isValid = true;
	}
	else if(isDecimal(token))
	{
		getToken();
		isValid = true;
	}
	else if(isString(token))
	{
		getToken();
		isValid = true;
	}
	else if(isIdent(token))
	{
		getToken();
		isValid = true;
	}
	else if(token == "(")
	{
		getToken();
		if(Expression())
		{
			if(token == ")")
			{
				getToken();
				isValid = true;
			}
		}
	}
	else if(token == "~")
	{
		getToken();
		if(Factor())
		{
			isValid = true;
		}
	}
		
	return isValid;
}

bool Term()
{
	bool isValid = false;
	
	if(Factor())
	{
		isValid = true;
		while(MulOperator() && isValid == true)
		{
			if(!Factor())
			{
				isValid = false;
			}
		}
	}
	
	return isValid;
}

bool SimpleExpression()
{
	bool isValid = false;
	
	if(Term())
	{
		isValid = true;
		while(AddOperator() && isValid == true)
		{
			if(!Term())
			{
				isValid = false;
			}
		}
	}
	
	return isValid;
}

bool Expression()
{
	bool isValid = false;
	
	if(SimpleExpression())
	{
		isValid = true;
		if(Relation())
		{
			if(SimpleExpression())
			{
				isValid = true;
			}
			else
			{
				isValid = false;
			}
		}
	}
	
	return isValid;
}

bool Assignment()
{
	bool isValid = false;
	
	if(isIdent(token))
	{
		getToken();
		if(token == "<=")
		{
			getToken();
			if(Expression())
			{
				if(token == "!")
				{
					getToken();
					isValid = true;
				}
			}
		}
	}
		
	return isValid;
}

bool IncStatement()
{
	bool isValid = false;
	
	if(token == "inc")
	{
		getToken();
		if(isIdent(token))
		{
			getToken();
			if(token == "!")
			{
				getToken();
				isValid = true;
			}
		}
	}
	
	return isValid;
}

bool IfStatement()
{
	bool isValid = false;
	
	if(token == "if")
	{
		getToken();
		if(token == "<")
		{
			getToken();
			if(Expression())
			{
				if(token == ">")
				{
					getToken();
					if(StatementSequence())
					{
						if(token == "else")
						{
							getToken();
							if(StatementSequence())
							{
								if(token == "fi")
								{
									getToken();
									isValid = true;
								}
								
							}
						}
						else if(token == "fi")
						{
							getToken();
							isValid = true;
						}
					}
				}
			}
		}
	}
	
	return isValid;
}

bool LoopStatement()
{
	bool isValid = false;
	
	if(token == "while")
	{
		getToken();
		if(token == "<")
		{
			getToken();
			if(Expression())
			{
				if(token == ">")
				{
					getToken();
					if(StatementSequence())
					{
						if(token == "elihw")
						{
							getToken();
							isValid = true;
						}
					}
				}
			}
		}
	}
	
	return isValid;
}

bool PrintStatement()
{
	bool isValid = false;
	
	if(token == "print")
	{
		getToken();
		if(isIdent(token))
		{
			getToken();
			if(token == "!")
			{
				getToken();
				isValid = true;
			}
		}
	}
		
	return isValid;		
}

bool Statement()
{
	bool isValid = false;
	
	if(Assignment())
	{
		isValid = true;
	}
	else if(IfStatement())
	{
		isValid = true;
	}
	else if(LoopStatement())
	{
		isValid = true;
	}
	else if(PrintStatement())
	{
		isValid = true;
	}
	else if(IncStatement())
	{
		isValid = true;
	}
		
	return isValid;
}

bool StatementSequence()
{
	bool isValid = false;
	
	if(Statement())
	{
		isValid = true;
		while(Statement())
		{
			//empty loop
		}
	}
	
	return isValid;
}

bool ParamSequence()
{
	bool isValid = false;
	
	if(isIdent(token))
	{
		getToken();
		isValid = true; // One identifier meets the rule
		while(token == "," && isValid == true)
		{
			getToken();
			if(isIdent(token)) 
			{
				getToken();
			}
			else
			{
				isValid = false; // The rule is broken by the missing identifier
			}
		}
	}

	return isValid;
}

bool RoutineDeclaration()
{
	bool isValid = false;
	
	if(token == "defprog")
	{
		getToken();
		if(isIdent(token))
		{
			getToken();
			if(token == "<")
			{
				getToken();
				if(token != ">") // Path for when there is a ParamSequence
				{
					if(ParamSequence())
					{
						if(token == ">")
						{
							getToken();
							if(token == "blip")
							{
								getToken();
								if(token != "blorp" )
								{
									if(StatementSequence())
									{
										if(token == "blorp")
										{
											isValid = true;
										}
									}
									if(token == "ret")
									{
										getToken();
										if(Expression())
										{
											if(token == "blorp")
											{
												isValid = true;
											}
										}
									}
								}
								else if(token == "blorp")
								{
									isValid = true;
								}
							}
						}
					}
				}				
				else if(token == ">") // No ParamSequence
				{
					getToken();
					if(token == "blip")
					{
						getToken();
						if(token != "blorp")
						{
							if(StatementSequence())
							{
								if(token == "blorp")
								{
									isValid = true;
								}
							}
							if(token == "ret")
							{
								getToken();
								if(Expression())
								{
									if(token == "blorp")
									{
										isValid = true;
									}
								}
							}
						}
						else if(token == "blorp")
						{
							isValid = true;
						}
					}
				}
			}
		}
	}

	return isValid;
}

int main()
{
	cin >> token;
	if(RoutineDeclaration())
	{
		cout<<"CORRECT"<<endl;
	}
	else
	{
		cout<<"INVALID!"<<endl;
	}
	
	return 0;
}
