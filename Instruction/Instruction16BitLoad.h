#pragma once

#include "Instruction.h"
#include "../CPU/CPU.h"

class Instruction16BitLoad : public Instruction
{
public:
	Instruction16BitLoad(std::string const& name, void (*pInstruction)(CPU & cpu), u8 clockCycles);
	virtual ~Instruction16BitLoad() = default;

	static void LD_BCcd16(CPU& cpu);	//0x01 LD BC,d16

};

