#pragma once

#include <v16/architecture.hpp>

struct Mode
{
	enum Type
	{
		M = 0b00,
		R = 0b01,
		O = 0b10,
		C = 0011,
	};
	
	enum Modifier
	{
		NONE = 0b00,
		NEGATIVE_OFFSET = 0b01,
		POSTINCREMENT = 0b10,
		PREINCREMENT = 0b11,
	};

	explicit Mode(Byte value);
	Mode(Type type, bool indirect);

	unsigned getSize() const;
	unsigned getCycleCost() const;

	Nibble assemble() const;

	Type type : 4;
	bool indirect : 1;
	Modifier mod : 4;
};

enum Opcode
{
	// SIMPLE
	NOP = 0x00,
	JMP = 0x01,
	CLL = 0x02,
	RET = 0x03,
	// ..
	PNC = 0x0F,
	// IO
	MOV = 0x10,
	CPY = 0x11,
	SWP = 0x12,
	// CONDITIONAL
	IEQ = 0x20,
	INQ = 0x21,
	IGT = 0x22,
	ILT = 0x23,
	IGQ = 0x24,
	ILQ = 0x25,
	// BINARY
	NOT = 0x30,
	OR  = 0x31,
	AND = 0x32,
	XOR = 0x33,
	RSF = 0x34,
	LSF = 0x35,
	// ARITHMETIC
	ADD = 0x40,
	SUB = 0x41,
	MUL = 0x42,
	DIV = 0x43,
	MOD = 0x44,
	// HARDWARE
	API = 0x50,
	APO = 0x51,
	SDP = 0x52,
};

struct Instruction
{
	Instruction(Word value);
	Instruction(Opcode opcode, Mode A, Mode B);

	unsigned getSize() const;
	unsigned getCycleCost() const;

	bool usesA() const;
	bool usesB() const;

	Word assemble() const;

	Opcode opcode;
	Mode A;
	Mode B;
};

