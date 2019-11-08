
#include <iostream>

#include "Register.h"
#include "Processor.h"
#include "FileParser.h"

using std::cout;

int main() {

	FileParser parser;
	parser.setInputFile("input.txt");
	parser.setOutputFile("output.txt");
	cout << parser.parse(Processor<32, 5>{}) << '\n';

	return 0;
}