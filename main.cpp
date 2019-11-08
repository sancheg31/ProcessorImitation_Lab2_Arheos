
#include <iostream>

#include "Register.h"
#include "Processor.h"

#include "CommandParser.h"
#include "FileParser.h"

using std::cout;

int main() {

	FileParser parser("input.txt", "output.txt");
	Processor<8, 5> pros(CommandParser{});
	cout << parser.parse(pros) << '\n';

	return 0;
}