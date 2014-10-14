#pragma once

#include <list>
#include <vector>
#include <string>
#include <map>

struct CodeContext
{
	std::vector<std::string> m_Ops;
};

class Node
{
public:
	virtual void CodeGen(CodeContext& context) = 0;
};

class NNumeric : public Node
{
public:
	NNumeric(std::string& value);
	int m_value;
	virtual void CodeGen(CodeContext& context) { }
};

class NStatement : public Node
{
public:
	virtual void CodeGen(CodeContext& context) = 0;
};

class NRotate : public NStatement
{
public:
	NRotate(NNumeric* dir);
	virtual void CodeGen(CodeContext& context);
private:
	NNumeric* m_Dir;
};

class NForward : public NStatement
{
public:
	NForward();
	virtual void CodeGen(CodeContext& context);
};

class NAttack : public NStatement
{
public:
	NAttack();
	virtual void CodeGen(CodeContext& context);
};

class NRangedAttack : public NStatement
{
public:
	NRangedAttack();
	virtual void CodeGen(CodeContext& context);
};

class NSaveLoc : public NStatement
{
public:
	NSaveLoc();
	virtual void CodeGen(CodeContext& context);
};

class NMemoryInc : public NStatement
{
public:
	NMemoryInc(NNumeric* loc);
	virtual void CodeGen(CodeContext& context);
private:
	NNumeric* m_Dir;
};

class NMemoryDec : public NStatement
{
public:
	NMemoryDec(NNumeric* loc);
	virtual void CodeGen(CodeContext& context);
private:
	NNumeric* m_Dir;
};

class NIf : public NStatement
{

};

class NElse : public NStatement
{

};

class NBoolean : public Node
{
public:
	virtual void CodeGen(CodeContext& context) = 0;
};

class NBlock : public Node
{
public:
	NBlock() { m_bMainBlock = false; }
	virtual void CodeGen(CodeContext& context);
	void AddStatement(NStatement* statement);
	void SetMainBlock() { m_bMainBlock = true; }
private:
	std::list<NStatement*> m_Statements;
	bool m_bMainBlock;
};
