
#include <iostream>

#include "Register.h"
#include "Processor.h"

#include "CommandParser.h"
#include "FileStreamController.h"

#include "BinaryOperations.h"
#include "UnaryOperations.h"

using std::cout;

int main() {

	using cur_type = Processor<16, 4>;
	BinaryOperations<cur_type::value_type, cur_type::value_type, cur_type::value_type> bin;
	UnaryOperations<cur_type::value_type, cur_type::value_type> un;
	bin.insert("add", [](auto ob1, auto ob2) { return ob1 + ob2; });
	bin.insert("substract", [](auto ob1, auto ob2) { return ob1 - ob2; });
	bin.insert("or", [](auto ob1, auto ob2) { return ob1 | ob2; });
	bin.insert("and", [](auto ob1, auto ob2) { return ob1 & ob2; });
	bin.insert("xor", [](auto ob1, auto ob2) { return ob1 ^ ob2; });
	un.insert("invert", [](auto ob) { return ob.invert(); });
	
	FileStreamController controller("input.txt", "output.txt");	
	cur_type pros(CommandParser{}, un, bin);

	auto res = controller.read<std::vector<std::string>>();
	auto vec = res.value();
	auto f = [](auto pros, auto vec) {
		for (auto& x : vec) {
			char* c;
			std::cin.get();
			pros.addCommand(x);
			std::cout << pros;
			std::cin.get();
			pros.doCommand();
			std::cout << pros << '\n';
		}
	};

	f(pros, vec);
	return 0;

}