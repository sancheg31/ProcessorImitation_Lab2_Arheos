#include "CommandParser.h"

#include <regex>
#include <cstring>

using std::stoi;
using std::regex;
using std::regex_match;
using std::smatch;

CommandParser::CommandParser() : firstReg("R1"), secondReg("R2"), sign(Sign::None), opType(OperationType::None), opValue(0) { }

void CommandParser::parse(const string& s) {

	regex regUnary(R"((\w{2,}) (R\d{1,}))", std::regex_constants::ECMAScript | std::regex_constants::icase);
	regex regUnaryWithNumber(R"((\w{2,}) (R\d{1,}), (-?[1-9][0-9]{0,}))", std::regex_constants::ECMAScript | std::regex_constants::icase);
	regex regBinary(R"((\w{2,}) (R\d{1,}), (R\d{1,}))", std::regex_constants::ECMAScript | std::regex_constants::icase);
	smatch results;

	if (regex_match(s, results, regUnary)) {
		opType = OperationType::UnaryOperation;
	}
	if (regex_match(s, results, regUnaryWithNumber)) {
		opType = OperationType::UnaryOperation;
		opValue = stoi(results[3]);
	}
	else if (regex_match(s, results, regBinary)) {
		opType = OperationType::BinaryOperation;
		secondReg = results[3];
	}
	else
		opType = OperationType::None;
	opNotation = results[1];
	firstReg = results[2];

}
