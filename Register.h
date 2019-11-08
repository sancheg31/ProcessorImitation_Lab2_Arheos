#pragma once

#include <bitset>
#include <string>

using std::bitset;
using std::string;


template <size_t Bits>
class Register {
public:
	Register() = default;
	Register(int n, string str) : number(n), name(str) {}

	Register(const Register&) = default;
	Register<Bits>& operator=(const Register<Bits>&) = default;

	template<size_t N1>
	Register<Bits>& Register<Bits>::operator=(const bitset<N1>&);

	template <size_t N1>
	Register<Bits>& operator=(const Register<N1>&);

	~Register() = default;

	void setNumber(int n) { number = intToBitSet(n); }
	void setName(const string& s) { name = s; }

	int getNumber() const { return number.to_string(); }
	string getName() const { return name; }

	void invert() {
		for (int i = 0; i < Bits; ++i)
			number.flip(i);
	}

	Register& operator<<(int bits);
	Register& operator>>(int bits);

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

	bitset<Bits> number;
	string name;

};




