#pragma once

#include <v16/architecture.hpp>

enum class ModeType
{
	M = 00,
	R = 01,
	H = 02,
	P = 03,
	T = 04,
	S = 05,
	F = 06,
};

struct Mode
{
	Mode(Nibble value);
	Mode(ModeType type, bool indirect);

	unsigned getSize() const;
	unsigned getCycleCost() const;

	Nibble assemble() const;

	ModeType type;
	bool indirect;
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
	SND = 0x50,
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
