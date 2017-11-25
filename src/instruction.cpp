#include <stdexcept>
//
#include <v16/instruction.hpp>

Mode::Mode(Nibble value) :
	type(static_cast<Type>(value & 0b0111)),
	indirect(value & 0b1000)
{

}

Mode::Mode(Mode::Type type, bool indirect) :
	type(type),
	indirect(indirect)
{

}

unsigned Mode::getSize() const
{
	switch(type)
	{
		case Type::M:
		case Type::R:
		case Type::H: return 1;
		//
		case Type::P:
		case Type::T:
		case Type::S:
		case Type::F: return 0;
		//
		default: throw std::runtime_error("illegal mode");
	}
}

unsigned Mode::getCycleCost() const
{
	unsigned cycle = 0;
	if(indirect)
	{
		cycle += 2;
	}
	switch(type)
	{
		case Type::P:
		case Type::T:
		case Type::S: cycle += 1; break;
		//
		case Type::M: cycle += 2; break;
		//
		case Type::H: cycle += 4; break;
		//
		case Type::F:
		case Type::R: break;
		//
		default: throw std::runtime_error("illegal mode");
	}
	return cycle;
}

Nibble Mode::assemble() const
{
	return static_cast<Nibble>(type) | static_cast<Nibble>(indirect << 3);
}

Instruction::Instruction(Word value) :
	opcode(static_cast<Opcode>(value >> 8)),
	A((value & 0x00F0) >> 4),
	B((value & 0x00F))
{

}

Instruction::Instruction(Opcode opcode, Mode A, Mode B) :
	opcode(opcode),
	A(A),
	B(B)
{

}

unsigned Instruction::getSize() const
{
	unsigned size = 1;
	if(usesA()) size += A.getSize();
	if(usesB())
	{
		unsigned Bsize = B.getSize();
		if(size == 1 && Bsize == 1) size += 2;
		else size += Bsize;
	}
	return size;
}

unsigned Instruction::getCycleCost() const
{
	unsigned cycle = 0;
	switch(opcode)
	{
		case NOP:
		case JMP:
		case RET:
		case PNC:
		case MOV:
		case NOT:
		case OR :
		case AND:
		case XOR:
		case RSF:
		case SDP:
		case LSF: cycle += 1; break;
		//
		case CLL:
		case CPY:
		case SWP:
		case IEQ:
		case INQ:
		case IGT:
		case ILT:
		case IGQ:
		case API:
		case APO:
		case ILQ: cycle += 2; break;
		//
		case ADD:
		case SUB: cycle += 3; break;
		//
		case MUL:
		case DIV:
		case MOD: cycle += 8; break;
		//
		default: throw std::runtime_error("illegal mode");
	}
	if(usesA())
	{
		cycle += A.getCycleCost();
	}
	if(usesB())
	{
		cycle += B.getCycleCost();
	}
	return cycle;
}

bool Instruction::usesA() const
{
	switch(opcode)
	{
		case NOP:
		case RET:
		case PNC: return false;
		//
		case JMP:
		case CLL:
		case MOV:
		case NOT:
		case OR :
		case AND:
		case XOR:
		case RSF:
		case LSF:
		case CPY:
		case SWP:
		case IEQ:
		case INQ:
		case IGT:
		case ILT:
		case IGQ:
		case ILQ:
		case ADD:
		case SUB:
		case API:
		case APO:
		case SDP:
		case MUL:
		case DIV:
		case MOD: return true;
		//
		default: throw std::runtime_error("illegal instruction");
	}
}

bool Instruction::usesB() const
{
	switch(opcode)
	{
		case NOP:
		case RET:
		case PNC:
		case JMP:
		case CLL: return false;
		//
		case MOV:
		case NOT:
		case OR :
		case AND:
		case XOR:
		case RSF:
		case LSF:
		case CPY:
		case SWP:
		case IEQ:
		case INQ:
		case IGT:
		case ILT:
		case IGQ:
		case ILQ:
		case ADD:
		case SUB:
		case API:
		case APO:
		case SDP:
		case MUL:
		case DIV:
		case MOD: return true;
		//
		default: throw std::runtime_error("illegal instruction");
	}
}

Word Instruction::assemble() const
{
	return static_cast<Word>(opcode << 8) | static_cast<Nibble>(A.assemble() << 4) | B.assemble();
}
