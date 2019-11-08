#pragma once

#include <bitset>
#include <string>

template <size_t N>
class Register {
public:
	Register();
	Register(int n, std::string name);

	Register(const Register&) = default;
	Register& operator=(const Register&) = default;
	~Register() = default;

	void setNumber(int n) { number = intToSet(n); }
	void setName(const std::string& s) { name = s; }

	int getNumber() const { return setToInt(number); }
	std::string getName() const { return name; }

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

	bitset<N> intToSet(int) const;
	int setToInt(bitset<N>) const;

	std::bitset<N> number;
	std::string name;

};


