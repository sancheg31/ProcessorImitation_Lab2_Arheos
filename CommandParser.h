#pragma once

#include <algorithm>
#include <string>
#include <regex>

#include "Enums.h"
#include "Register.h"

#include "BinaryOperations.h"
#include "UnaryOperations.h"

using std::string;
using std::max;
using std::regex;
using std::smatch;
using std::regex_match;


template <typename T, typename P>
class UnaryOperations;

template <typename T, typename P1, typename P2>
class BinaryOperations;

class CommandParser {
public:

	CommandParser();

	void parse(const string& s);

	string firstRegisterName() const { return firstReg; }
	string secondRegisterName() const { return secondReg; }
	OperationType type() const { return opType; }

	template <size_t Bits>
	Register<Bits> evaluate(const Register<Bits>&, const Register<Bits>&, const BinaryOperations<Register<Bits>, Register<Bits>, Register<Bits>>&) const;
	
	template <size_t Bits>
	Register<Bits> evaluate(Register<Bits>&, const UnaryOperations<Register<Bits>, Register<Bits>>&) const;
	
private:

	string firstReg;
	string secondReg;
	string opNotation;

	Sign sign;
	OperationType opType;
	int opValue;

};

template <size_t Bits>
Register<Bits> CommandParser::evaluate(const Register<Bits>& reg1, const Register<Bits>& reg2,
										const BinaryOperations<Register<Bits>, Register<Bits>, Register<Bits>>& bin) const {
	if (opType != OperationType::BinaryOperation)
		return Register<Bits>();
	auto op = bin.find(opNotation);
	(*op)(reg1, reg2);
	
}

template <size_t Bits>
Register<Bits> CommandParser::evaluate(Register<Bits>& reg, const UnaryOperations<Register<Bits>, Register<Bits>>& un) const {
	if (opType != OperationType::UnaryOperation)
		return Register<Bits>{};
	
	if (opNotation == string("mov"))
		reg.setNumber(opValue);
	else {
		auto op = un.find(opNotation);
		(*op)(reg);
	}
	return reg;
}








