#pragma once

#include <fstream>
#include <vector>
#include <list>
#include <optional>

#include "Processor.h"

using std::optional;
using std::string_view;
using std::vector;

template <typename Cont, typename In, typename Out>
class StreamController {
public:

	using container_type = Cont;
	using in_file_type = In;
	using out_file_type = Out;
	using value_type = typename container_type::value_type;

	StreamController() = default;
	StreamController(const string& in, const string& out) : inFileName(in), outFileName(out) { }
	StreamController(const StreamController&) = default;
	StreamController& operator=(const StreamController&) = default;
	~StreamController() = default;

	optional<container_type> read() const;
	bool write(const container_type&) const;
private:

	string inFileName;
	string outFileName;
	bool stateIsValid(in_file_type&) const;
	bool stateIsValid(out_file_type&) const;

};

template <typename Cont, typename In, typename Out>
auto StreamController<Cont, In, Out>::read() const -> optional<container_type> {
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

template <typename Cont, typename In, typename Out>
bool StreamController<Cont, In, Out>::write(const container_type& cont) const {
	out_file_type outFile(outFileName);
	if (!stateIsValid(outFile)) {
		return false;
	}
	for (auto& x : cont)
		outFile << x << '\n';
	return true;
}

template <typename Cont, typename In, typename Out>
bool StreamController<Cont, In, Out>::stateIsValid(in_file_type & file) const {
	return (file.is_open() && file.good());
}

template <typename Cont, typename In, typename Out>
bool StreamController<Cont, In, Out>::stateIsValid(out_file_type & file) const {
	return (file.is_open() && file.good());
}

















