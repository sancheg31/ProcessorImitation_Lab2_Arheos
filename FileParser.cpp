#include "FileParser.h"

FileParser::FileParser(): st(FileParserState::IllInformed) { }

FileParser::FileParser(const string& in, const string& out) {
	inFile.open(in, std::ios_base::in);
	outFile.open(out, std::ios_base::out);
	st = checkState();
}

FileParser::~FileParser() {
	if (inFile.is_open())
		inFile.close();
	if (outFile.is_open())
		outFile.close();
}