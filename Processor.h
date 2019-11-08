#pragma once

#include <array>
#include <vector>

#include "Register.h"

enum class Sign { Plus = 0, Minus = 1};

template <size_t Bits, size_t N>
class Processor {
public:

	using iterator = typename std::array<Register<Bits>, N>::iterator;
	using const_iterator = typename std::array<Register<Bits>, N>::const_iterator;
	Processor();

	void addCommand(const std::string& s);

	int getTactNumber() const { return tactNumber; }
	int getCommandNumber() const { return commandNumber; }
	std::string getLastOperation() const { return operations.size() > 0 ? operations[operations.size() - 1] : ""; }
	
	iterator begin() { return registers.begin(); }
	const_iterator begin() const { return registers.begin(); }
	const_iterator cbegin() const { return registers.cbegin(); }


	iterator end() { return registers.end(); }
	const_iterator end() const { return registers.end(); }
	const_iterator cend() const { return registers.cend(); }

	friend std::ostream& operator<<(std::ostream&, const Processor&);
private:

	int tactNumber;
	int commandNumber;
	Sign signStatus;
	std::vector<std::string> operations;
	std::array<Register<Bits>, N> registers;

};

