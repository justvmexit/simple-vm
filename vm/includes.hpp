#pragma once

#include <Windows.h>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include <algorithm>
#include <vector>
#include <map>

namespace simplevm
{
    enum registers : std::uint32_t
    {
        R0 = 0,
        R1,
        R2,
        R3,
        R4,
        R5,
        R6,
        R7,
        R8
    };

    enum opcodes : std::uint32_t
    {
        OP_ADD,
        OP_NOP,
        OP_MOV,
        OP_MOVI,
        OP_JMP,
        OP_OUT, // out hexadecimal
        OP_OUTI, // out decimal
        OP_SET,
        OP_PAUSE,
        OP_HALT,
        OP_JE,
        OP_JNE,
        OP_INT
    };

    class instruction
    {
    public:
        simplevm::registers m_register;
        simplevm::registers m_register2;
        simplevm::opcodes m_opcode;
        std::uint64_t m_data;
        std::uint64_t m_data2;

        instruction(simplevm::opcodes opcodes, simplevm::registers registers, std::uint64_t datas) : m_opcode(opcodes), m_register(registers), m_data(datas) {}
        instruction(simplevm::opcodes opcodes, simplevm::registers registers) : m_register(registers), m_opcode(opcodes) {}
        instruction(simplevm::opcodes opcodes, simplevm::registers registers, simplevm::registers registers2) : m_register(registers), m_register2(registers2), m_opcode(opcodes) {}
        instruction(simplevm::opcodes opcodes, std::uint64_t datas) : m_opcode(opcodes), m_data(datas) {}
        instruction(simplevm::opcodes opcodes, std::uint64_t datas, std::uint64_t datas2) : m_opcode(opcodes), m_data(datas), m_data2(datas2) {}
        instruction(simplevm::opcodes opcodes) : m_opcode(opcodes) {}
    };

}