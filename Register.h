#pragma once

#include <algorithm>
#include <bitset>
#include <string>

using std::bitset;
using std::string;

template <size_t Bits>
class Register {
public:
	
	Register() = default;
	Register(int n, string str);
	Register(const Register& ob) = default;

	Register<Bits>& operator=(const Register<Bits>& ob) = default;
	~Register() = default;

	void setNumber(int n) { regNumber = intToBitSet(n); }
	void setName(const string& s) { regName = s; }

	string number() const { return regNumber.to_string(); }
	string name() const { return regName; }
	bool test(size_t pos) const { return regNumber.test(pos); }

	operator int() const { return regNumber.to_ulong(); }
	operator long() const { return regNumber.to_ullong(); }

	Register& invert();
	Register& invert(size_t n);
	Register& swap(size_t n1, size_t n2);

	Register& operator<<=(int bits) { return regNumber <<= bits; }
	Register& operator>>=(int bits) { return regNumber >>= bits; }

	template <size_t Bits>
	friend Register<Bits> operator+(const Register<Bits>& reg1, const Register<Bits>& reg2);
	template <size_t Bits>
	friend Register<Bits> operator-(const Register<Bits>& reg1, const Register<Bits>& reg2);
	
	template <size_t Bits>
	friend Register<Bits> operator&(const Register<Bits>& ob1, const Register<Bits>& ob2);

	template <size_t Bits>
	friend Register<Bits> operator|(const Register<Bits>& ob1, const Register<Bits>& ob2);

	template <size_t Bits>
	friend Register<Bits> operator^(const Register<Bits>& ob1, const Register<Bits>& ob2);
	
	const Register<Bits>& operator~() {
		invert(regNumber);
		return *this;
	}

private:

	bitset<Bits> intToBitSet(int n) const;
	bitset<Bits> regNumber;
	string regName;

};

template <size_t Bits>
Register<Bits>::Register(int n, string str): regNumber(intToBitSet(n)), regName(str) { }

template <size_t Bits>
bitset<Bits> Register<Bits>::intToBitSet(int n) const {
	bitset<Bits> temp;
	bool isNegative = n < 0;
	n = std::abs(n);
	for (int i = 0; i < Bits && n > 0; ++i, n /= 2) {
		temp.set(i, (bool)(n % 2));
	}
	if (isNegative) {
		temp.flip();
		int rem = 0, i = 0;
		do {
			rem = temp.test(i);
			temp[i].flip();
			++i;
		} while (i < Bits && rem);
	}
	return temp;
}

template <size_t Bits>
Register<Bits>& Register<Bits>::invert() {
	regNumber.flip();
	return *this;
}

template <size_t Bits>
Register<Bits>& Register<Bits>::invert(size_t n) {
	if (n < Bits)
		regNumber.flip();
	return *this;
}

template <size_t Bits>
Register<Bits>& Register<Bits>::swap(size_t n1, size_t n2) {
	if (n1 < Bits && n2 < Bits) {
		bool b = regNumber[n1];
		regNumber[n1] = regNumber[n2];
		regNumber[n2] = b;
	}
	return *this;
}

//-----------operators--------------

template <size_t Bits>
Register<Bits> operator&(const Register<Bits>& ob1, const Register<Bits>& ob2) {
	bitset<Bits> s;
	for (int i = 0; i < Bits; ++i)
		s.set(i, ob1.regNumber.test(i) & ob2.regNumber.test(i));
	return Register<Bits>(s.to_ulong(), ob1.name());
}

template <size_t Bits>
Register<Bits> operator|(const Register<Bits>& ob1, const Register<Bits>& ob2) { 
	bitset<Bits> s;
	for (int i = 0; i < Bits; ++i)
		s.set(i, ob1.regNumber.test(i) | ob2.regNumber.test(i));
	return Register<Bits>(s.to_ulong(), ob1.name());
}

template <size_t Bits>
Register<Bits> operator^(const Register<Bits>& ob1, const Register<Bits>& ob2) { 
	bitset<Bits> s;
	for (int i = 0; i < Bits; ++i)
		s.set(i, ob1.regNumber.test(i) ^ ob2.regNumber.test(i));
	return Register<Bits>(s.to_ulong(), ob1.name());
}

template <size_t Bits>
Register<Bits> operator+(const Register<Bits>& ob1, const Register<Bits>& ob2) {	
	bitset<Bits> s; 
	int rem = 0;
	for (int i = 0; i < Bits; ++i) {
		s.set(i, (ob1.regNumber.test(i) + ob2.regNumber.test(i) + rem) % 2);
		rem = ob2.regNumber.test(i) & ob2.regNumber.test(i);
	}
	return Register<Bits>(s.to_ulong(), ob1.name());
}

template <size_t Bits>
Register<Bits> operator-(const Register<Bits>& ob1, const Register<Bits>& ob2) {
	Register<Bits> tempOb(ob2.regNumber.to_ulong() * (-1), "");
	return ob1 + tempOb;
}

