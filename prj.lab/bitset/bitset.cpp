#include <iostream>
#include <bitset/bitset.h>
#include <sstream>
void Bitset::resize(const int64_t size, const bool filler) {
	Bitset temp(size, filler);
	for (int i = 0; i < std::min(size, bitsize); i++) temp[i] = bool(filler);
	*this = temp;
}
void Bitset::set_masks() {
	masks.resize(type_size);
	container_type mask = 1;
	for (int i = 0; i < masks.size(); i++) {
		masks[i] = mask;
		mask <<= 1;
	}
}
Bitset::Bitset(const Bitset& copy) {
	bitsize = copy.bitsize;
	bitset = copy.bitset;
}
Bitset::Bitset(int64_t size, const bool filler) {
	if (size < 0) {
		throw std::invalid_argument("Size bitset can not be negative");
	}
	bitsize = size;
	bitset.resize(bitsize / type_size + 1);
	set_masks();
	if (filler) {
		for (int i = 0; i < bitsize; i++) (*this)[i] = bool(1);
	}
}
Bitset& Bitset::operator=(const Bitset& rhs) = default;
Bitset Bitset::operator~() const {
	Bitset copy = Bitset(*this);
	for (int i = 0; i < copy.bitsize; i++) {
		copy[i] = !copy[i];
	}
	return copy;
}
bool Bitset::operator==(const Bitset& rhs) const {
	if (bitsize != rhs.bitsize)
		return false;
	for (int i = 0; i < bitset.size(); i++)
		if (bitset[i] != rhs.bitset[i])
			return false;
	return true;
}
bool Bitset::operator!=(const Bitset& rhs) const {
	return !(operator==(rhs));
}
Bitset& Bitset::operator&=(const Bitset& rhs) {
	if ((*this).size() != rhs.size()) throw std::invalid_argument("Sizes of operands do not match");
	for (int i = 0; i < bitset.size(); i++) {
		bitset[i] &= rhs.bitset[i];
	}
	return *this;
}
Bitset& Bitset::operator|=(const Bitset& rhs) {
	if ((*this).size() != rhs.size()) throw std::invalid_argument("Sizes of operands do not match");
	for (int i = 0; i < bitset.size(); i++) {
		bitset[i] |= rhs.bitset[i];
	}
	return *this;
}
Bitset& Bitset::operator^=(const Bitset& rhs) {
	if ((*this).size() != rhs.size()) throw std::invalid_argument("Sizes of operands do not match");
	for (int i = 0; i < bitset.size(); i++) {
		bitset[i] ^= rhs.bitset[i];
	}
	return *this;
}
Bitset& Bitset::operator>>=(const int64_t rhs) {
	if (rhs < 0) {
		throw std::invalid_argument("Cannot be negative!");
	}
	for (int64_t i = 0; i < bitsize - rhs; i++) {
		(*this)[i] = bool((*this)[i + rhs]);
	}

	for (int64_t i = bitsize - rhs; i < bitsize; i++) {
		(*this)[i] = 0;
	}
	return *this;
}
Bitset& Bitset::operator<<=(const int64_t rhs) {
	if (rhs < 0) {
		throw std::invalid_argument("Cannot be negative!");
	}
	for (int64_t i = bitsize - 1; i >= rhs; i--) {
		(*this)[i] = bool((*this)[i - rhs]);
	}
	for (int64_t i = rhs - 1; i >= 0; i--) {
		(*this)[i] = false;
	}
	return *this;
}
Bitset const operator&(const Bitset& lhs, const Bitset& rhs) {
	return Bitset(lhs) &= rhs;
}
Bitset const operator|(const Bitset& lhs, const Bitset& rhs) {
	return Bitset(lhs) |= rhs;
}
Bitset const operator^(const Bitset& lhs, const Bitset& rhs) {
	return Bitset(lhs) ^= rhs;
}
Bitset const operator>>(const Bitset& lhs, const uint64_t rhs) {
	Bitset temp = Bitset(lhs);
	temp >>= rhs;
	return temp;
}
Bitset const operator<<(const Bitset& lhs, const uint64_t rhs) {
	Bitset temp = Bitset(lhs);
	temp <<= rhs;
	return temp;
}
std::istream& operator>>(std::istream& in, Bitset& copy) {
	std::string potok("");
	while (in.peek() == '0' || in.peek() == '1') {
		potok.push_back(in.get());
	}
	if (potok.size() > 0) {
		copy = Bitset(potok);
	}
	else {
		in.setstate(std::ios_base::failbit);
	}
	return in;
}
std::ostream& operator<<(std::ostream& out, const Bitset& copy) {
	for (int i = copy.size() - 1; i >= 0; i--)
		out << copy[i];
	return out;
}
bool Bitset::operator[](const int64_t pos) const {
	if (pos < 0 || pos >= bitsize) {
		throw std::invalid_argument("Bitset error: index out of range");
	}
	return bool(bitset[pos / type_size] & masks[pos % type_size]);
}
Bitset::Bitset(const std::string& convert){
	bitsize = convert.size();
	bitset.resize(bitsize / type_size + 1);
	set_masks();
	for (int64_t i = 0; i < convert.size(); i++) {
		if (convert[i] != '0' && convert[i] != '1') {
			throw std::invalid_argument("Bitset can get only '1' or '0'");
		}
		bitset[(bitsize - i - 1) / type_size] |= ((convert[i] - '0') << ((bitsize - i - 1) % type_size));
	}
}
Bitset::BitHolder::BitHolder(int position, Bitset& data) :
	number(data.bitset[position / type_size]),
	number_bit(position% type_size)
{}
Bitset::BitHolder Bitset::operator[](const int64_t position) {
	if (position < 0 || position >= (*this).size())
		throw std::logic_error("Index out of range");
	return BitHolder(position, (*this));
}
Bitset::BitHolder::operator bool() const {
	return number >> (number_bit % type_size) & 1;
}
Bitset::BitHolder& Bitset::BitHolder::operator=(const bool rhs) {
	int64_t x = (int64_t(1) << (*this).number_bit);
	if (rhs == true)
		(*this).number |= x;
	else
		(*this).number &= ~(x);
	return *this;
}