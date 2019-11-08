#pragma once

#include <fstream>

#include "Processor.h"

using std::ifstream;
using std::ofstream;
using std::string;


class FileParser {
public:

	enum class ClassState { Normal = 0, IllInformed = 1 };
	FileParser() = default;
	FileParser(const FileParser&) = default;
	FileParser& operator=(const FileParser&) = default;
	FileParser(const string&, const string&);

	template <size_t Bits, size_t Size>
	bool parse(const Processor<Bits, Size>&);
	
	void setInputFile(const string& s) { inFile.open(s, std::ios_base::in); st = checkState(); }
	void setOutputFile(const string& s) { outFile.open(s, std::ios_base::out); st = checkState(); }

private:
	ClassState checkState() const { return (inFile.is_open() && outFile.is_open()) ? ClassState::Normal : ClassState::IllInformed; }
	ClassState st;
	ifstream inFile;
	ofstream outFile;
};

FileParser::FileParser(const string& in, const string& out) {
	inFile.open(in, std::ios_base::in);
	outFile.open(out, std::ios_base::out);
	st = checkState();
}

template<size_t Bits, size_t Size>
bool FileParser::parse(const Processor<Bits, Size>& pros) {
	if (st == ClassState::IllInformed)
		return false;
	string str;
	while (inFile.good()) {
		inFile >> str;
		pros.addCommand(str);
		outFile << pros;
	}
	return true;
}
















