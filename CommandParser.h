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

	template <size_t N1, size_t N2, size_t N3 = max(N1, N2)>
	const Register<N3>& operator()(const Register<N1>&, const Register<N2>&) const;
	
	template <size_t Bits>
	const Register<Bits>& operator()(Register<Bits>&) const;
	
private:
	Sign sign;
	OperationType opType;
	int number;

};

template <size_t N1, size_t N2, size_t N3>
auto CommandParser::operator()(const Register<N1>&, const Register<N2>&) const -> const Register<N3>& {
	return Register<N3>();
}

template <size_t Bits>
const Register<Bits>& CommandParser::operator()(Register<Bits>& reg) const {
	return Register<Bits>();
}











