#pragma once

enum class InstructionEnum
{
	I1BITOPERATION = 0,
	I8BITLOAD = 1,
	I8BITLOGIC,
	I16BITLOAD,
	I16BITLOGIC,
	ICPUCONTROL,
	IJUMP,
	IROTATESHIFT
};