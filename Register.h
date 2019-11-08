#pragma once

#include <bitset>
#include <string>

using std::bitset;
using std::string;


template <size_t Bits>
class Register {
public:
	
	Register() = default;
	Register(int n, string str);

	Register(const Register&) = default;
	Register<Bits>& operator=(const Register<Bits>&) = default;
	~Register() = default;

	void setNumber(int n) { regNumber = intToBitSet(n); }
	void setName(const string& s) { regName = s; }

	string number() const { return regNumber.to_string(); }
	string name() const { return regName; }
	bool test(size_t pos) const { return regNumber.test(pos); }

	void invert(bitset<Bits>& bitSet) const {
		for (int i = 0; i < Bits; ++i)
			bitSet.flip(i);
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
		invert(regNumber);
	}

private:

	bitset<Bits> intToBitSet(int n) const {
		bitset<Bits> temp;
		bool isNegative = n < 0;
		for (int i = 0; i < Bits && n > 0; ++i, n /= 2) {
			temp.set(i, (bool)(n % 2));
		}
		if (isNegative) {
			invert(temp);
			int rem = 0, i = 0;
			do {
				rem = temp.test(i);
				temp[i].flip();
				++i;
			} while (i < Bits && rem);
		}
		return temp;
	}

	bitset<Bits> regNumber;
	string regName;

};

template <size_t Bits>
Register<Bits>::Register(int n, string str) : regNumber(intToBitSet(n)), regName(str) {

}


