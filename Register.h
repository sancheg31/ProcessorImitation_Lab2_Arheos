#pragma once

#include <bitset>
#include <string>

using std::bitset;
using std::string;

template <size_t N>
class Register {
public:
	Register();
	Register(int n, string name);

	Register(const Register&) = default;
	Register<N>& operator=(const Register<N>&) = default;
	~Register() = default;

	void setNumber(int n) { number = intToSet(n); }
	void setName(const string& s) { name = s; }

	int getNumber() const { return setToInt(number); }
	string getName() const { return name; }

	void invert();
	Register& operator<<(int bits);
	Register& operator>>(int bits);

	template <size_t N1, size_t N2>
	friend Register operator+(const Register<N1>&, const Register<N2>&);
	template <size_t N1, size_t N2>
	friend Register operator-(const Register<N1>&, const Register<N2>&);
	
	template <size_t N1, size_t N2>
	friend bool operator&&(const Register<N1>&, const Register<N2>&);
	template <size_t N1, size_t N2>
	friend bool operator||(const Register<N1>&, const Register<N2>&);

private:

	bitset<N> intToSet(int) const {
		return nullptr;
	}
	int setToInt(bitset<N>) const {
		return nullptr;
	}

	bitset<N> number;
	string name;

};


