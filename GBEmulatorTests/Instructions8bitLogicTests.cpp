#include "pch.h"
#include "CppUnitTest.h"

#include "..\Bus\Bus.h"
#include "..\CPU\CPU.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Instructions_tests
{

	TEST_CLASS(I8BitLogicTests)
	{
	private:
		static Bus* bus;
		static CPU* cpu;

	public:

		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			bus = new Bus();
			cpu = new CPU(bus);
		}

		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			delete cpu;
			delete bus;
		}

		TEST_METHOD(INC_R)
		{
			u8* B_reg = cpu->getRegistries("B");
			flags* flags = cpu->getFlagRegistry();

			*B_reg = 0x03;
			cpu->executeOpcode(0x04);

			Assert::AreEqual(static_cast<u8>(0x04), *B_reg);
			Assert::AreEqual(static_cast < u8>(0x00), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.N);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.H);

			*B_reg = 0x1F;
			cpu->executeOpcode(0x04);
			Assert::AreEqual(static_cast<u8>(0x20), *B_reg);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.H);

			*B_reg = 0xFF;
			cpu->executeOpcode(0x04);
			Assert::AreEqual(static_cast<u8>(0x00), *B_reg);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.Z);

		}

		TEST_METHOD(DEC_R)
		{
			u8* B_reg = cpu->getRegistries("B");
			flags* flags = cpu->getFlagRegistry();

			*B_reg = 0x03;
			cpu->executeOpcode(0x05);

			Assert::AreEqual(static_cast<u8>(0x02), *B_reg);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.N);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.H);

			*B_reg = 0x10;
			cpu->executeOpcode(0x05);
			Assert::AreEqual(static_cast<u8>(0x0F), *B_reg);
			u8 a = 0x00;
			a--;
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.H);

			*B_reg = 0x01;
			cpu->executeOpcode(0x05);
			Assert::AreEqual(static_cast<u8>(0x00), *B_reg);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.Z);

		}

		TEST_METHOD(ADD_RcR)
		{
			u8* A_reg = cpu->getRegistries("A");
			u8* B_reg = cpu->getRegistries("B");
			flags* flags = cpu->getFlagRegistry();
			
			*A_reg = 0x05;
			*B_reg = 0xD3;
			cpu->executeOpcode(0x80);
			Assert::AreEqual(static_cast<u8>(0xD8), *A_reg);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.N);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.C);

			*A_reg = 0xE5;
			*B_reg = 0x1F;
			cpu->executeOpcode(0x80);
			Assert::AreEqual(static_cast<u8>(0x04), *A_reg);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.C);

			*A_reg = 0xE5;
			*B_reg = 0x1B;
			cpu->executeOpcode(0x80);
			Assert::AreEqual(static_cast<u8>(0x00), *A_reg);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.C);

		}

		TEST_METHOD(ADD_AcpHLq)
		{
			u8* A_reg = cpu->getRegistries("A");
			combinedRegistries* HL_reg = cpu->getCombinedRegistries("HL");

			*A_reg = 0x05;
			HL_reg->setValue(0xC005);
			cpu->writeMemory(0xC005, 0x05);

			cpu->executeOpcode(0x86);
			Assert::AreEqual(static_cast<u8>(0x0A), *A_reg);

		}

		TEST_METHOD(ADC_RcR)
		{
			u8* A_reg = cpu->getRegistries("A");
			u8* B_reg = cpu->getRegistries("B");
			flags* flags = cpu->getFlagRegistry();
			flags->flags.C = 0x00;

			*A_reg = 0x05;
			*B_reg = 0xD3;
			cpu->executeOpcode(0x88);
			Assert::AreEqual(static_cast<u8>(0xD8), *A_reg);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.N);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.C);

			*A_reg = 0xE5;
			*B_reg = 0x1F;
			cpu->executeOpcode(0x88);
			Assert::AreEqual(static_cast<u8>(0x04), *A_reg);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.C);

			*A_reg = 0xE5;
			*B_reg = 0x1A;
			cpu->executeOpcode(0x88);
			Assert::AreEqual(static_cast<u8>(0x00), *A_reg);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.C);

		}

		TEST_METHOD(ADC_AcpHLq)
		{
			u8* A_reg = cpu->getRegistries("A");
			combinedRegistries* HL_reg = cpu->getCombinedRegistries("HL");

			flags* flags = cpu->getFlagRegistry();
			flags->flags.C = 0x01;

			*A_reg = 0x05;
			HL_reg->setValue(0xC005);
			cpu->writeMemory(0xC005, 0x05);


			cpu->executeOpcode(0x8E);
			Assert::AreEqual(static_cast<u8>(0x0B), *A_reg);

		}

		TEST_METHOD(SUB_R)
		{
			u8* A_reg = cpu->getRegistries("A");
			u8* B_reg = cpu->getRegistries("B");
			flags* flags = cpu->getFlagRegistry();

			*A_reg = 0xFE;
			*B_reg = 0x0E;
			cpu->executeOpcode(0x90);
			Assert::AreEqual(static_cast<u8>(0xF0), *A_reg);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.N);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.C);

			*A_reg = 0x08;
			*B_reg = 0x08;
			cpu->executeOpcode(0x90);
			Assert::AreEqual(static_cast<u8>(0x00), *A_reg);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.C);

			*A_reg = 0x25;
			*B_reg = 0x06;
			cpu->executeOpcode(0x90);
			Assert::AreEqual(static_cast<u8>(0x1F), *A_reg);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.C);

			*A_reg = 0x20;
			*B_reg = 0x30;
			cpu->executeOpcode(0x90);
			Assert::AreEqual(static_cast<u8>(0xF0), *A_reg);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.Z);
			//Check this flag
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.C);

		}

		TEST_METHOD(SUB_AcpHLq)
		{
			u8* A_reg = cpu->getRegistries("A");
			combinedRegistries* HL_reg = cpu->getCombinedRegistries("HL");

			flags* flags = cpu->getFlagRegistry();

			*A_reg = 0x08;
			HL_reg->setValue(0xC005);
			cpu->writeMemory(0xC005, 0x05);


			cpu->executeOpcode(0x96);
			Assert::AreEqual(static_cast<u8>(0x03), *A_reg);

		}

		TEST_METHOD(SBC_RcR)
		{
			u8* A_reg = cpu->getRegistries("A");
			u8* B_reg = cpu->getRegistries("B");
			flags* flags = cpu->getFlagRegistry();
			flags->flags.C = 0x00;

			*A_reg = 0xFE;
			*B_reg = 0x0E;
			cpu->executeOpcode(0x98);
			Assert::AreEqual(static_cast<u8>(0xF0), *A_reg);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.N);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.C);

			flags->flags.C = 0x01;
			*A_reg = 0x09;
			*B_reg = 0x08;
			cpu->executeOpcode(0x98);
			Assert::AreEqual(static_cast<u8>(0x00), *A_reg);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.C);

			flags->flags.C = 0x01;
			*A_reg = 0x25;
			*B_reg = 0x06;
			cpu->executeOpcode(0x98);
			Assert::AreEqual(static_cast<u8>(0x1E), *A_reg);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.C);

			flags->flags.C = 0x01;
			*A_reg = 0x20;
			*B_reg = 0x30;
			cpu->executeOpcode(0x98);
			Assert::AreEqual(static_cast<u8>(0xEF), *A_reg);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.C);
		}

		TEST_METHOD(SBC_AcpHLq)
		{
			u8* A_reg = cpu->getRegistries("A");
			combinedRegistries* HL_reg = cpu->getCombinedRegistries("HL");

			flags* flags = cpu->getFlagRegistry();
			flags->flags.C = 0x01;

			*A_reg = 0x08;
			HL_reg->setValue(0xC005);
			cpu->writeMemory(0xC005, 0x05);


			cpu->executeOpcode(0x9E);
			Assert::AreEqual(static_cast<u8>(0x02), *A_reg);

		}

		TEST_METHOD(AND_R)
		{
			u8* A_reg = cpu->getRegistries("A");
			u8* B_reg = cpu->getRegistries("B");
			flags* flags = cpu->getFlagRegistry();

			*A_reg = 0x05;
			*B_reg = 0x0B;
			cpu->executeOpcode(0xA0);
			Assert::AreEqual(static_cast<u8>(0x01), *A_reg);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.N);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.C);

			*A_reg = 0x0A;
			*B_reg = 0x05;
			cpu->executeOpcode(0xA0);
			Assert::AreEqual(static_cast<u8>(0x00), *A_reg);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.Z);

		}

		TEST_METHOD(AND_pHLq)
		{
			u8* A_reg = cpu->getRegistries("A");
			combinedRegistries* HL_reg = cpu->getCombinedRegistries("HL");

			flags* flags = cpu->getFlagRegistry();


			*A_reg = 0xA2;
			HL_reg->setValue(0xC005);
			cpu->writeMemory(0xC005, 0x5F);


			cpu->executeOpcode(0xA6);
			Assert::AreEqual(static_cast<u8>(0x02), *A_reg);

		}

		TEST_METHOD(XOR_R)
		{
			u8* A_reg = cpu->getRegistries("A");
			u8* B_reg = cpu->getRegistries("B");
			flags* flags = cpu->getFlagRegistry();

			*A_reg = 0x05;
			*B_reg = 0x0B;
			cpu->executeOpcode(0xA8);
			Assert::AreEqual(static_cast<u8>(0x0E), *A_reg);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.N);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.C);

			*A_reg = 0x0A;
			*B_reg = 0x0A;
			cpu->executeOpcode(0xA8);
			Assert::AreEqual(static_cast<u8>(0x00), *A_reg);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.Z);

		}

		TEST_METHOD(XOR_pHLq)
		{
			u8* A_reg = cpu->getRegistries("A");
			combinedRegistries* HL_reg = cpu->getCombinedRegistries("HL");

			flags* flags = cpu->getFlagRegistry();


			*A_reg = 0xAE;
			HL_reg->setValue(0xC005);
			cpu->writeMemory(0xC005, 0x5F);


			cpu->executeOpcode(0xAE);
			Assert::AreEqual(static_cast<u8>(0xF1), *A_reg);

		}

		TEST_METHOD(OR_R)
		{
			u8* A_reg = cpu->getRegistries("A");
			u8* B_reg = cpu->getRegistries("B");
			flags* flags = cpu->getFlagRegistry();

			*A_reg = 0x15;
			*B_reg = 0x5B;
			cpu->executeOpcode(0xB0);
			Assert::AreEqual(static_cast<u8>(0x5F), *A_reg);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.N);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.C);

			*A_reg = 0x00;
			*B_reg = 0x00;
			cpu->executeOpcode(0xB0);
			Assert::AreEqual(static_cast<u8>(0x00), *A_reg);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.Z);

		}

		TEST_METHOD(OR_pHLq)
		{
			u8* A_reg = cpu->getRegistries("A");
			combinedRegistries* HL_reg = cpu->getCombinedRegistries("HL");

			flags* flags = cpu->getFlagRegistry();


			*A_reg = 0xAE;
			HL_reg->setValue(0xC005);
			cpu->writeMemory(0xC005, 0x2C);


			cpu->executeOpcode(0xB6);
			Assert::AreEqual(static_cast<u8>(0xAE), *A_reg);

		}

		TEST_METHOD(CP_R)
		{
			u8* A_reg = cpu->getRegistries("A");
			u8* B_reg = cpu->getRegistries("B");
			flags* flags = cpu->getFlagRegistry();

			*A_reg = 0xFE;
			*B_reg = 0x0E;
			cpu->executeOpcode(0xB8);
			Assert::AreEqual(static_cast<u8>(0xFE), *A_reg);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.N);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.C);

			*A_reg = 0x08;
			*B_reg = 0x08;
			cpu->executeOpcode(0xB8);
			Assert::AreEqual(static_cast<u8>(0x08), *A_reg);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.C);

			*A_reg = 0x25;
			*B_reg = 0x06;
			cpu->executeOpcode(0xB8);
			Assert::AreEqual(static_cast<u8>(0x25), *A_reg);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.C);

			*A_reg = 0x20;
			*B_reg = 0x30;
			cpu->executeOpcode(0xB8);
			Assert::AreEqual(static_cast<u8>(0x20), *A_reg);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.Z);
			//Check this flag
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.C);

		}

		TEST_METHOD(CP_pHLq)
		{
			u8* A_reg = cpu->getRegistries("A");
			combinedRegistries* HL_reg = cpu->getCombinedRegistries("HL");

			flags* flags = cpu->getFlagRegistry();

			*A_reg = 0x25;
			HL_reg->setValue(0xC005);
			cpu->writeMemory(0xC005, 0x06);


			cpu->executeOpcode(0xBE);
			Assert::AreEqual(static_cast<u8>(0x25), *A_reg);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.Z);
			Assert::AreEqual(static_cast <u8>(0x01), flags->flags.H);
			Assert::AreEqual(static_cast <u8>(0x00), flags->flags.C);

		}
	};

	Bus* I8BitLogicTests::bus = nullptr;
	CPU* I8BitLogicTests::cpu = nullptr;
}