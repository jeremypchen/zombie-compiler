// zompiler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "node.h"
#include "parser.hpp"
#include <fstream>
#include <conio.h>

extern int g_LineNumber;
extern NBlock* g_MainBlock;

int _tmain(int argc, _TCHAR* argv[])
{
	zompilerparse();
	
	CodeContext myContext;
	if (g_MainBlock != nullptr)
	{
		// TODO: CodeGen from g_MainBlock
		g_MainBlock->CodeGen(myContext);
	}

	// output into out.zom file
	std::ofstream output;
	output.open("out.zom");

	for (std::string s : myContext.m_Ops)
	{
		output << s << std::endl;
		output.close;
	}

	_getch();
	return 0;
}

void zompilererror(const char* s)
{
	std::cout << s << " on line " << g_LineNumber << std::endl;
}
