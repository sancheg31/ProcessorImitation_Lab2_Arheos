
#include <iostream>

#include "Register.h"
#include "Processor.h"

#include "CommandParser.h"
#include "FileParser.h"

#include "BinaryOperations.h"
#include "UnaryOperations.h"

using std::cout;

int main() {

	BinaryOperations<Register<8>, Register<8>, Register<8>> bin;
	UnaryOperations<Register<8>, Register<8>> un;
	bin.insert("add", [](Register<8> ob1, Register<8> ob2) -> Register<8> { return ob1 + ob2; });
	bin.insert("substract", [](Register<8> ob1, Register<8> ob2) -> Register<8> { return ob1 - ob2; });
	un.insert("invert", [](Register<8> ob) { return ob.invert(); });

	FileParser parser("input.txt", "output.txt");
	Processor<8, 5> pros(CommandParser{}, un, bin);
	cout << parser.parse(pros) << '\n';

	return 0;
}