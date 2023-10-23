#pragma once
#include <iostream>
#include "Instruction.h"

class Instruction1BitOperation : public Instruction
{
	public:
		Instruction1BitOperation(std::string const& name, void (*pInstruction)(), u8 clockCycles);
		virtual ~Instruction1BitOperation() = default;
		
		static void instruction1();


	private:

};

