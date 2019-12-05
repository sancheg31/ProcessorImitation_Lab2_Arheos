#pragma once

#include <iostream>
#include <fstream>
#include <sstream>

#include <optional>
#include <vector>

#include <string>

using std::optional;
using std::string_view;
using std::vector;

using std::ifstream;
using std::ofstream;

using std::istringstream;
using std::ostringstream;

using std::istream;
using std::ostream;


class FileStreamController {
public:

	using in_file_type = ifstream;
	using out_file_type = ofstream;

	FileStreamController() noexcept = default;
	FileStreamController(const string& in, const string& out) : inFileName(in), outFileName(out) { }
	FileStreamController(const FileStreamController&)  = default;
	FileStreamController& operator=(const FileStreamController&) = default;
	~FileStreamController() noexcept = default;

	const string& getInFileName() const { return inFileName; }
	const string& getOutFileName() const { return outFileName; }

	void setInFileName(const string& s) { inFileName = s; }
	void setOutFileName(const string& s) { outFileName = s; }


	template <typename Cont>
	optional<Cont> read() const;

	template <typename Cont>
	bool write(const Cont&) const;

private:

	string inFileName;
	string outFileName;

	bool stateIsValid(in_file_type&) const;
	bool stateIsValid(out_file_type&) const;

};

template <typename Cont>
auto FileStreamController::read() const -> optional<Cont> {
	in_file_type inFile(inFileName);
	if (!stateIsValid(inFile)) {
		return optional<Cont>{};
	}
	Cont v;
	char str[256];
	while (inFile.good()) {
		inFile.getline(str, 256, '\n');
		v.push_back(typename Cont::value_type{ str });
	}
	return std::make_optional(v);
}

template <typename Cont>
bool FileStreamController::write(const Cont& cont) const {
	out_file_type outFile(outFileName);
	if (!stateIsValid(outFile)) {
		return false;
	}
	for (auto& x : cont)
		outFile << x << '\n';
	return true;
}

bool FileStreamController::stateIsValid(in_file_type& file) const {
	return (file.is_open() && file.good());
}

bool FileStreamController::stateIsValid(out_file_type & file) const {
	return (file.is_open() && file.good());
}

















