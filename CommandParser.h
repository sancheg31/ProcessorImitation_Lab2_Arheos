#pragma once

#include <algorithm>
#include <string>

#include "Enums.h"
#include "Register.h"

using std::string;
using std::max;

class CommandParser {
public:

	CommandParser();
	
	void parse(const string& s);

	string firstRegisterName() const { return firstReg; }
	string secondRegisterName() const { return secondReg; }
	OperationType type() const { return opType; }

	template <size_t N1, size_t N2, size_t N3 = max(N1, N2)>
	Register<N3> operator()(const Register<N1>&, const Register<N2>&) const;
	
	template <size_t Bits>
	const Register<Bits>& operator()(Register<Bits>&) const;
	
private:

	string firstReg;
	string secondReg;
	string opNotation;
	Sign sign;
	OperationType opType;
	int opValue;

};

template <size_t N1, size_t N2, size_t N3>
Register<N3> CommandParser::operator()(const Register<N1>& reg1, const Register<N2>& reg2) const {
	if (opType != OperationType::BinaryOperation)
		return Register<N3>();
	else if (opNotation == string("add"))
		return reg1 + reg2;
	else if (opNotation == string("substract"))
		return reg1 - reg2;
	else if (opNotation == string("or"))
		return reg1 | reg2;
	else if (opNotation == string("and"))
		return reg1 & reg2;
	else if (opNotation == string("xor"))
		return reg1 ^ reg2;
}

template <size_t Bits>
const Register<Bits>& CommandParser::operator()(Register<Bits>& reg) const {
	if (opType != OperationType::UnaryOperation)
		return Register<Bits>();
	else if (opNotation == string("mov"))
		reg.setNumber(opValue);
	else if (opNotation == string("invert"))
		~reg;
	return reg;
}











