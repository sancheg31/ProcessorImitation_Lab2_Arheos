#pragma once

#include <array>
#include <ostream>
#include <string>
#include <vector>

#include "CommandParser.h"
#include "Register.h"
#include "Enums.h"

template <size_t Bits, size_t N>
class Processor {
public:

	using iterator = typename std::array<Register<Bits>, N>::iterator;
	using const_iterator = typename std::array<Register<Bits>, N>::const_iterator;
	Processor(const CommandParser&);

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

	Register<Bits>& findRegister(const string& s);

	int tactNumber;
	int commandNumber;
	Sign signStatus;
	std::vector<string> operations;
	std::array<Register<Bits>, N> registers;
	CommandParser parser;

};

template <size_t Bits, size_t N>
Processor<Bits, N>::Processor(const CommandParser& p) : parser(p), signStatus(Sign::None), tactNumber(0), commandNumber(0) {
	int i = 0;
	for (auto& x : registers) {
		x.setName("R" + std::to_string(i+1));
		x.setNumber(i + 1);
		++i;
	}
}

template <size_t Bits, size_t N>
Register<Bits>& Processor<Bits, N>::findRegister(const string& s) {
	for (auto& x : registers)
		if (x.name() == s)
			return x;
}

template <size_t Bits, size_t N>
void Processor<Bits, N>::addCommand(const std::string& command) {
	tactNumber = 0;
	parser.parse(command);
	operations.push_back(command);
	++commandNumber; ++tactNumber;
	signStatus = (findRegister(parser.firstRegisterName())).test(Bits - 1) == 0 ? Sign::Plus : Sign::Minus;
}

template <size_t Bits, size_t N>
void Processor<Bits, N>::doCommand() {
	++tactNumber;
	auto reg1 = findRegister(parser.firstRegisterName());
	if (parser.type() == OperationType::BinaryOperation) {
		auto reg2 = findRegister(parser.secondRegisterName());
		reg1 = parser(reg1, reg2);
	}
	else if (parser.type() == OperationType::UnaryOperation) {
		reg1 = parser(reg1);
	}
	signStatus = reg1.test(Bits - 1) == 0 ? Sign::Plus : Sign::Minus;
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












