#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include <optional>


using std::optional;
using std::string_view;
using std::vector;

using std::ifstream;
using std::ofstream;

using std::istringstream;
using std::ostringstream;

using std::istream;
using std::ostream;


enum class StreamType { IOStream, FStream, IStringStream };

template <typename Cont>
class StreamController {
public:


	using container_type = Cont;
	using in_file_type = ifstream;
	using out_file_type = ofstream;
	using value_type = typename container_type::value_type;

	StreamController() = default;
	StreamController(const string& in, const string& out) : inFileName(in), outFileName(out) { }
	StreamController(const StreamController&) = default;
	StreamController& operator=(const StreamController&) = default;
	~StreamController() = default;

	const string& getInFileName() const { return inFileName; }
	const string& getOutFileName() const { return outFileName; }

	void setInFileName(const string& s) { inFileName = s; }
	void setOutFileName(const string& s) { outFileName = s; }

	optional<container_type> read() const;
	bool write(const container_type&) const;

private:

	string inFileName;
	string outFileName;

	bool stateIsValid(in_file_type&) const;
	bool stateIsValid(out_file_type&) const;


};

template <typename Cont>
auto StreamController<Cont>::read() const -> optional<container_type> {
	in_file_type inFile(inFileName);
	if (!stateIsValid(inFile)) {
		return optional<vector<string>>{};
	}
	container_type v;
	char str[256];
	while (inFile.good()) {
		inFile.getline(str, 256, '\n');
		v.push_back(string{ str });
	}
	return std::make_optional(v);
}

template <typename Cont>
bool StreamController<Cont>::write(const container_type& cont) const {
	out_file_type outFile(outFileName);
	if (!stateIsValid(outFile)) {
		return false;
	}
	for (auto& x : cont)
		outFile << x << '\n';
	return true;
}

template <typename Cont>
bool StreamController<Cont>::stateIsValid(in_file_type& file) const {
	return (file.is_open() && file.good());
}

template <typename Cont>
bool StreamController<Cont>::stateIsValid(out_file_type & file) const {
	return (file.is_open() && file.good());
}

















