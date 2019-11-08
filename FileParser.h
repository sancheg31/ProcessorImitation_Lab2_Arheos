#pragma once

#include <fstream>

#include "Processor.h"

using std::ifstream;
using std::ofstream;
using std::string;

template <size_t Bits, size_t N>
class Processor;

class FileParser {
public:

	enum class FileParserState { Normal = 0, IllInformed = 1 };

	FileParser();
	FileParser(const string&, const string&);
	FileParser(const FileParser&) = default;
	FileParser& operator=(const FileParser&) = default;
	~FileParser();

	template <size_t Bits, size_t Size>
	bool parse(Processor<Bits, Size>);
	
	void setInputFile(const string& s) { inFile.open(s, std::ios_base::in); st = checkState(); }
	void setOutputFile(const string& s) { outFile.open(s, std::ios_base::out); st = checkState(); }

private:
	FileParserState checkState() const { return (inFile.is_open() && outFile.is_open()) ? FileParserState::Normal : FileParserState::IllInformed; }
	FileParserState st;
	ifstream inFile;
	ofstream outFile;
};

#include <iostream>

template<size_t Bits, size_t Size>
bool FileParser::parse(Processor<Bits, Size> pros) {
	if (st == FileParserState::IllInformed) {
		std::cout << "Incorrect input or output file name";
		return false;
	}
	char str[256];
	while (inFile.good()) {
		inFile.getline(str, 256, '\n');
		pros.addCommand(string(str));
		std::cout << pros;
		pros.doCommand();
		std::cout << pros;
	}
	return true;
}
















