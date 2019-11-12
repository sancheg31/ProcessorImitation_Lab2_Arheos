#pragma once

#include <array>
#include <ostream>
#include <string>
#include <vector>

#include "CommandParser.h"
#include "Register.h"
#include "Enums.h"

class CommandParser;

template <size_t Bits, size_t N>
class Processor {
public:

	using iterator = typename std::array<Register<Bits>, N>::iterator;
	using const_iterator = typename std::array<Register<Bits>, N>::const_iterator;
	Processor(const CommandParser&);
	Processor(const CommandParser&, const BinaryOperations<Register<Bits>, Register<Bits>, Register<Bits>>&);
	Processor(const CommandParser&, const UnaryOperations<Register<Bits>, Register<Bits>>&);
	Processor(const CommandParser&, const UnaryOperations<Register<Bits>, Register<Bits>>&, 
				const BinaryOperations<Register<Bits>, Register<Bits>, Register<Bits>>&);

	void addCommand(const std::string& s);
	void doCommand();

	int getTactNumber() const { return tactNumber; }
	int getCommandNumber() const { return commandNumber; }
	std::string getLastOperation() const { return operations.size() > 0 ? operations[operations.size() - 1] : ""; }
	
	iterator begin() { return registers.begin(); }
	const_iterator begin() const { return registers.begin(); }
	const_iterator cbegin() const { return registers.cbegin(); }


	iterator end() { return registers.end(); }
	const_iterator end() const { return registers.end(); }
	const_iterator cend() const { return registers.cend(); }
	
	template <size_t Bits, size_t N>
	friend std::ostream& operator<<(std::ostream&, const Processor<Bits, N>&);

private:

	UnaryOperations<Register<Bits>, Register<Bits>> un;
	BinaryOperations<Register<Bits>, Register<Bits>, Register<Bits>> bin;

	int findRegister(const string& s);

	int tactNumber;
	int commandNumber;
	Sign signStatus;
	std::vector<string> operations;
	std::array<Register<Bits>, N> registers;
	CommandParser parser;

};

template <size_t Bits, size_t N>
Processor<Bits, N>::Processor(const CommandParser& p) : parser(p), signStatus(Sign::None), tactNumber(0), commandNumber(0), un(), bin() {
	int i = 0;
	for (auto& x : registers) {
		x.setName("R" + std::to_string(i+1));
		x.setNumber(i + 1);
		++i;
	}
}

template<size_t Bits, size_t N>
Processor<Bits, N>::Processor(const CommandParser& p, const BinaryOperations<Register<Bits>, Register<Bits>, Register<Bits>>& b)
	: parser(p), signStatus(Sign::None), tactNumber(0), commandNumber(0), bin(b)  {
	int i = 0;
	for (auto& x : registers) {
		x.setName("R" + std::to_string(i + 1));
		x.setNumber(i + 1);
		++i;
	}
}

template<size_t Bits, size_t N>
Processor<Bits, N>::Processor(const CommandParser& p, const UnaryOperations<Register<Bits>, Register<Bits>>& u)
	: parser(p), signStatus(Sign::None), tactNumber(0), commandNumber(0), un(u) {
	int i = 0;
	for (auto& x : registers) {
		x.setName("R" + std::to_string(i + 1));
		x.setNumber(i + 1);
		++i;
	}
}

template<size_t Bits, size_t N>
Processor<Bits, N>::Processor(const CommandParser& p, const UnaryOperations<Register<Bits>, Register<Bits>>& u, 
								const BinaryOperations<Register<Bits>, Register<Bits>, Register<Bits>>& b):
	parser(p), signStatus(Sign::None), tactNumber(0), commandNumber(0), un(u), bin(b) {
	int i = 0;
	for (auto& x : registers) {
		x.setName("R" + std::to_string(i + 1));
		x.setNumber(i + 1);
		++i;
	}
}



template <size_t Bits, size_t N>
int Processor<Bits, N>::findRegister(const string& s) {
	int i = 0;
	for (auto& x : registers) {
		if (x.name() == s)
			return i;
		++i;
	}
	return 0;
}

template <size_t Bits, size_t N>
void Processor<Bits, N>::addCommand(const std::string& command) {
	tactNumber = 0;
	parser.parse(command);
	operations.push_back(command);
	++commandNumber; ++tactNumber;
	int reg = findRegister(parser.firstRegisterName());
	signStatus = registers[reg].test(Bits - 1) == 0 ? Sign::Plus : Sign::Minus;
}

template <size_t Bits, size_t N>
void Processor<Bits, N>::doCommand() {
	++tactNumber;
	int reg1 = findRegister(parser.firstRegisterName());
	if (parser.type() == OperationType::BinaryOperation) {
		int reg2 = findRegister(parser.secondRegisterName());
		registers[reg1] = parser.evaluate(registers[reg1], registers[reg2], bin);
	}
	else if (parser.type() == OperationType::UnaryOperation) {
		registers[reg1] = parser.evaluate(registers[reg1], un);
	}
	signStatus = registers[reg1].test(Bits - 1) == 0 ? Sign::Plus : Sign::Minus;
}

template <size_t Bits, size_t N>
std::ostream& operator<<(std::ostream& out, const Processor<Bits, N>& pros) {
	if (pros.operations.empty())
		return out;
	out << "Command is: " << pros.operations[pros.operations.size() - 1] << '\n';
	int i = 1;
	for (auto it = pros.registers.begin(); it != pros.registers.end(); ++it, ++i)
		out << "R" << i << " " << (it->number()) << '\n';

	out << "PC " << pros.commandNumber << '\n';
	out << "TC " << pros.tactNumber << '\n';
	out << "PS " << (pros.signStatus == Sign::Plus ? 0 : 1) << '\n';
	return out;
}












