#include "node.h"
#include <sstream>

void NBlock::AddStatement(NStatement* statement)
{
	m_Statements.push_back(statement);
}

void NBlock::CodeGen(CodeContext& context)
{
	for (NStatement* x : m_Statements)
	{
		x->CodeGen;
	}
	if (m_bMainBlock)
	{
		context.m_Ops.push_back("goto,1");
	}
	// TODO: Loop through statements in list and code gen them
}

NNumeric::NNumeric(std::string& value)
{
	m_value = std::atoi(value.c_str());
}

NRotate::NRotate(NNumeric* dir)
	: m_Dir(dir)
{
}

NMemoryInc::NMemoryInc(NNumeric* loc)
: m_Dir(loc)
{
}

NMemoryDec::NMemoryDec(NNumeric* loc)
: m_Dir(loc)
{
}

void NRotate::CodeGen(CodeContext& context)
{
	if (m_Dir->m_value == 0)
	{
		context.m_Ops.push_back("rotate,0");
	}
	else if (m_Dir->m_value == 1)
	{
		context.m_Ops.push_back("rotate,1");
	}
}

void NAttack::CodeGen(CodeContext& context)
{
	context.m_Ops.push_back("attack");
}

void NRangedAttack::CodeGen(CodeContext& context)
{
	context.m_Ops.push_back("ranged_attack");
}

void NSaveLoc::CodeGen(CodeContext& context)
{
	context.m_Ops.push_back("save_loc");
}

void NMemoryInc::CodeGen(CodeContext& context)
{
	std::stringstream memorystring;
	memorystring << "memory," << m_Dir;

	context.m_Ops.push_back(memorystring.str());
}
