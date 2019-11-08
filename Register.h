#pragma once

#include <bitset>
#include <string>

using std::bitset;
using std::string;


template <size_t Bits>
class Register {
public:
	
	Register() = default;
	Register(int n, string str) : regNumber(n), regName(str) {}

	Register(const Register&) = default;
	Register<Bits>& operator=(const Register<Bits>&) = default;
	~Register() = default;

	void setNumber(int n) { regNumber = intToBitSet(n); }
	void setName(const string& s) { regName = s; }

	int number() const { return regNumber.to_string(); }
	string name() const { return regName; }
	bool test(size_t pos) const { return regNumber.test(pos); }

	void invert() {
		for (int i = 0; i < Bits; ++i)
			regNumber.flip(i);
	}

	Register& operator<<=(int bits) { return regNumber >>= bits; }
	Register& operator>>=(int bits) { return regNumber <<= bits; }

	template <size_t N1, size_t N2>
	friend Register operator+(const Register<N1>&, const Register<N2>&);
	template <size_t N1, size_t N2>
	friend Register operator-(const Register<N1>&, const Register<N2>&);
	
	template <size_t N1, size_t N2>
	friend bool operator&(const Register<N1>& ob1, const Register<N2>& ob2) { return ob1 & ob2; }
	template <size_t N1, size_t N2>
	friend bool operator|(const Register<N1>& ob1, const Register<N2>& ob2) { return ob1 | ob2; }
	template <size_t N1, size_t N2>
	friend bool operator^(const Register<N1>& ob1, const Register<N2>& ob2) { return ob1 ^ ob2; }
	
	const Register<Bits>& operator~() {
		invert();
	}

private:

	bitset<Bits> intToBitSet(int) const {
		return bitset<Bits>;
	}

	bitset<Bits> regNumber;
	string regName;

};




