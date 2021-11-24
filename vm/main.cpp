#include <includes.hpp>

std::vector<simplevm::instruction> registers;
std::map<simplevm::registers, std::uint64_t> memory;

simplevm::registers string_to_register(std::string data)
{
	std::for_each(data.begin(), data.end(), [&](char c) {
		c = tolower(c);
		});

	if (data == "r0") return simplevm::R0;
	if (data == "r1") return simplevm::R1;
	if (data == "r2") return simplevm::R2;
	if (data == "r3") return simplevm::R3;
	if (data == "r4") return simplevm::R4;
	if (data == "r5") return simplevm::R5;
	if (data == "r6") return simplevm::R6;
	if (data == "r7") return simplevm::R7;
	if (data == "r8") return simplevm::R8;

	return simplevm::R0;
}

std::string register_to_string(simplevm::registers data)
{
	if (data == simplevm::R0) return "R0";
	if (data == simplevm::R1) return "R1";
	if (data == simplevm::R2) return "R2";
	if (data == simplevm::R3) return "R3";
	if (data == simplevm::R4) return "R4";
	if (data == simplevm::R5) return "R5";
	if (data == simplevm::R6) return "R6";
	if (data == simplevm::R7) return "R7";
	if (data == simplevm::R8) return "R8";

	return "R0";
}


std::uint32_t main(std::uint32_t argc, char** argv)
{
	argc++;
	if (argc < 2)
	{
		std::printf("SimpleVM: not enough arguments..");
		return -1;
	}

	std::ifstream code(argv[1]);
	for (std::string line; std::getline(code, line); )
	{
		std::string opcode, data1, data2 = "";
		char* copyBuffer = (char*)line.c_str();

		while (!isspace(*copyBuffer))
		{
			opcode += *copyBuffer;
			copyBuffer++;
		}

		copyBuffer++;

		while (!isspace(*copyBuffer))
		{
			if (*copyBuffer == '\0')
				break;

			data1 += *copyBuffer;
			copyBuffer++;
		}

		copyBuffer++;

		while (!isspace(*copyBuffer))
		{
			if (*copyBuffer == '\0')
				break;

			data2 += *copyBuffer;
			copyBuffer++;
		}

		if (!strcmp(opcode.c_str(), "nop"))
		{
			registers.push_back(simplevm::instruction(
				simplevm::OP_NOP
			));
		}

		if (!strcmp(opcode.c_str(), "add"))
		{
			registers.push_back(simplevm::instruction(
				simplevm::OP_ADD, string_to_register(data1)
			));
		}

		if (!strcmp(opcode.c_str(), "outi"))
		{
			registers.push_back(simplevm::instruction(
				simplevm::OP_OUTI, string_to_register(data1)
			));
		}

		if (!strcmp(opcode.c_str(), "mov"))
		{
			registers.push_back(simplevm::instruction(
				simplevm::OP_MOV, string_to_register(data1), string_to_register(data2)
			));
		}

		if (!strcmp(opcode.c_str(), "movi"))
		{
			registers.push_back(simplevm::instruction(
				simplevm::OP_MOVI, string_to_register(data1), atoi(data2.c_str())
			));
		}

		if (!strcmp(opcode.c_str(), "out"))
		{
			registers.push_back(simplevm::instruction(
				simplevm::OP_OUT, string_to_register(data1)
			));
		}

		if (!strcmp(opcode.c_str(), "halt"))
		{
			registers.push_back(simplevm::instruction(
				simplevm::OP_HALT
			));
		}

		if (!strcmp(opcode.c_str(), "int"))
		{
			registers.push_back(simplevm::instruction(
				simplevm::OP_INT, atoi(data1.c_str())
			));
		}

		if (!strcmp(opcode.c_str(), "je"))
		{
			registers.push_back(simplevm::instruction(
				simplevm::OP_JE, string_to_register(data1), string_to_register(data2)
			));
		}

		if (!strcmp(opcode.c_str(), "jne"))
		{
			registers.push_back(simplevm::instruction(
				simplevm::OP_JE, string_to_register(data1), string_to_register(data2)
			));
		}

		if (!strcmp(opcode.c_str(), "jmp"))
		{
			registers.push_back(simplevm::instruction(
				simplevm::OP_JMP, atoi(data1.c_str())
			));
		}

		if (!strcmp(opcode.c_str(), "pause"))
		{
			registers.push_back(simplevm::instruction(
				simplevm::OP_PAUSE
			));
		}
	}
	
	for (std::uint32_t index = 0; index < registers.size(); index++)
	{
		auto instruction = registers.at(index);

		switch (instruction.m_opcode)
		{
		case simplevm::OP_ADD:
			memory[instruction.m_register] += 1;
			break;
		case simplevm::OP_NOP:
			break;
		case simplevm::OP_HALT:
			puts("SYSTEM HALT");
			index = registers.size(); 
			break;
		case simplevm::OP_INT:
			Sleep(instruction.m_data);
			break;
		case simplevm::OP_MOV:
			memory[instruction.m_register] = memory[instruction.m_register2];
			break;
		case simplevm::OP_MOVI:
			memory[instruction.m_register] = instruction.m_data;
			break;
		case simplevm::OP_JMP:
			index = instruction.m_data;
			break;
		case simplevm::OP_JE:
			if (memory[instruction.m_register] != memory[instruction.m_register2])
				index += 1;
			break;
		case simplevm::OP_JNE:
			if (memory[instruction.m_register] == memory[instruction.m_register2])
				index += 1;
			break;
		case simplevm::OP_PAUSE:
			getchar();
			break;
		case simplevm::OP_OUT:
			printf("%s = %x\n", register_to_string(instruction.m_register).c_str(), memory[instruction.m_register]);
			break;
		case simplevm::OP_OUTI:
			printf("%s = %i\n", register_to_string(instruction.m_register).c_str(), memory[instruction.m_register]);
			break;
		}
	}
}