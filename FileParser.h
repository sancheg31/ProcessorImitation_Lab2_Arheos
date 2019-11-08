#pragma once

#include <fstream>

#include "Processor.h"

class FileParser {
public:
	template <size_t Bits, size_t Size>
	FileParser(std::ifstream&, const Processor<Bits, Size>&);
	
private:
};