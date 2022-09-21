#include <iostream>
#include<vector>
#pragma once
#ifndef BITSETT_BITSETT_H_20220309
#define BITSETT_BITSETT_H_20220309
template <typename T>
class BitsetT {
public:
	typedef T container_type;
	class BitHolder {
	public:
		friend class BitsetT<T>;
		BitHolder() = default;
		BitHolder& operator=(const bool rhs);
		operator bool() const;
		explicit BitHolder(int position, BitsetT<T>& data);
		~BitHolder() = default;
	private:
		T& number;
		T number_bit;
	};
	BitsetT(int64_t size = 0, const bool filler = false);
	BitsetT(const BitsetT& copy);
	BitsetT(const std::string& copy);
	BitsetT& operator=(const BitsetT<T>& rhs);
	bool operator==(const BitsetT<T>& rhs) const;
	bool operator!=(const BitsetT<T>& rhs) const;
	bool operator [] (const T position) const;
	BitsetT<T>& operator&=(const BitsetT<T>& rhs);
	BitsetT<T>& operator|=(const BitsetT<T>& rhs);
	BitsetT<T>& operator^=(const BitsetT<T>& rhs);
	BitsetT<T> operator~() const;
	BitsetT<T>& operator<<=(const int64_t rhs);
	BitsetT<T>& operator>>=(const int64_t rhs);
	BitHolder operator[](const T position);
	void resize(const int64_t size, const bool filler = false);
	T size() const {
		return (*this).bitsize;
	}
	~BitsetT() = default;
private:
	int64_t bitsize = 0;
	static const int type_size = sizeof(T) * 8;
	std::vector<T> masks;
	std::vector<T> bitset;
	void set_masks();
};

template <typename T>
BitsetT<T> const operator^(const BitsetT<T>& left, const BitsetT<T>& right);
template <typename T>
BitsetT<T> const operator<<(const BitsetT<T>& left, const uint64_t shift);
template <typename T>
BitsetT<T> const operator>>(const BitsetT<T>& left, const uint64_t shift);
template <typename T>
BitsetT<T> const operator&(const BitsetT<T>& left, const BitsetT<T>& right);
template <typename T>
BitsetT<T> const operator|(const BitsetT<T>& left, const BitsetT<T>& right);
template <typename T>
std::istream& operator>>(std::istream& istrm, BitsetT<T>& right);
template <typename T>
std::ostream& operator<<(std::ostream& ostrm, const BitsetT<T>& right);

template <typename T>
void BitsetT<T>::resize(const int64_t size, const bool filler) {
	BitsetT temp(size, filler);
	for (int i = 0; i < std::min(size, bitsize); i++) temp[i] = bool(filler);
	*this = temp;
}
template <typename T>
void BitsetT<T>::set_masks() {
	masks.resize(type_size);
	T mask = 1;
	for (int i = 0; i < masks.size(); i++) {
		masks[i] = mask;
		mask <<= 1;
	}
}
template <typename T>
BitsetT<T>::BitsetT(const BitsetT<T>& copy) {
	bitsize = copy.bitsize;
	bitset = copy.bitset;
}
template <typename T>
BitsetT<T>::BitsetT(int64_t size, const bool filler) {
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
template <typename T>
BitsetT<T>& BitsetT<T>::operator=(const BitsetT<T>& rhs) = default;
template <typename T>
BitsetT<T> BitsetT<T>::operator~() const {
	BitsetT copy = BitsetT(*this);
	for (int i = 0; i < copy.bitsize; i++) {
		copy[i] = !copy[i];
	}
	return copy;
}
template <typename T>
bool BitsetT<T>::operator==(const BitsetT<T>& rhs) const {
	if (bitsize != rhs.bitsize)
		return false;
	for (int i = 0; i < bitset.size(); i++)
		if (bitset[i] != rhs.bitset[i])
			return false;
	return true;
}
template <typename T>
bool BitsetT<T>::operator!=(const BitsetT & rhs) const {
	return !(operator==(rhs));
}
template <typename T>
BitsetT<T>& BitsetT<T>::operator&=(const BitsetT<T>& rhs) {
	if ((*this).size() != rhs.size()) throw std::invalid_argument("Sizes of operands do not match");
	for (int i = 0; i < bitset.size(); i++) {
		bitset[i] &= rhs.bitset[i];
	}
	return *this;
}
template <typename T>
BitsetT<T>& BitsetT<T>::operator|=(const BitsetT<T>& rhs) {
	if ((*this).size() != rhs.size()) throw std::invalid_argument("Sizes of operands do not match");
	for (int i = 0; i < bitset.size(); i++) {
		bitset[i] |= rhs.bitset[i];
	}
	return *this;
}
template <typename T>
BitsetT<T>& BitsetT<T>::operator^=(const BitsetT<T>& rhs) {
	if ((*this).size() != rhs.size()) throw std::invalid_argument("Sizes of operands do not match");
	for (int i = 0; i < bitset.size(); i++) {
		bitset[i] ^= rhs.bitset[i];
	}
	return *this;
}
template <typename T>
BitsetT<T>& BitsetT<T>::operator>>=(const int64_t rhs) {
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
template <typename T>
BitsetT<T>& BitsetT<T>::operator<<=(const int64_t rhs) {
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
template <typename T>
BitsetT<T> const operator&(const BitsetT<T> & lhs, const BitsetT<T> & rhs) {
	return BitsetT<T>(lhs) &= rhs;
}
template <typename T>
BitsetT<T> const operator|(const BitsetT<T>& lhs, const BitsetT<T>& rhs) {
	return BitsetT<T>(lhs) |= rhs;
}
template <typename T>
BitsetT<T> const operator^(const BitsetT<T>& lhs, const BitsetT<T>& rhs) {
	return BitsetT<T>(lhs) ^= rhs;
}
template <typename T>
BitsetT<T> const operator>>(const BitsetT<T>& lhs, const uint64_t rhs) {
	BitsetT<T> temp = BitsetT<T>(lhs);
	temp >>= rhs;
	return temp;
}
template <typename T>
BitsetT<T> const operator<<(const BitsetT<T>& lhs, const uint64_t rhs) {
	BitsetT<T> temp = BitsetT<T>(lhs);
	temp <<= rhs;
	return temp;
}
template <typename T>
std::istream& operator>>(std::istream & in, BitsetT<T> & copy) {
	std::string potok("");
	while (in.peek() == '0' || in.peek() == '1') {
		potok.push_back(in.get());
	}
	if (potok.size() > 0) {
		copy = BitsetT<T>(potok);
	}
	else {
		in.setstate(std::ios_base::failbit);
	}
	return in;
}
template <typename T>
std::ostream& operator<<(std::ostream & out, const BitsetT<T> & copy) {
	for (int i = copy.size() - 1; i >= 0; i--)
		out << copy[i];
	return out;
}
template <typename T>
bool BitsetT<T>::operator[](const T pos) const {
	if (pos < 0 || pos >= bitsize) {
		throw std::invalid_argument("BitsetT error: index out of range");
	}
	return bool(bitset[pos / type_size] & masks[pos % type_size]);
}
template <typename T>
BitsetT<T>::BitsetT(const std::string & convert) {
	bitsize = convert.size();
	bitset.resize(bitsize / type_size + 1);
	set_masks();
	for (int64_t i = 0; i < convert.size(); i++) {
		if (convert[i] != '0' && convert[i] != '1') {
			throw std::invalid_argument("BitsetT can get only '1' or '0'");
		}
		bitset[(bitsize - i - 1) / type_size] |= ((convert[i] - '0') << ((bitsize - i - 1) % type_size));
	}
}
template <typename T>
BitsetT<T>::BitHolder::BitHolder(int position, BitsetT<T> & data) :
	number(data.bitset[position / type_size]),
	number_bit(position % type_size)
{}
template <typename T>
typename BitsetT<T>::BitHolder BitsetT<T>::operator[](const T position) {
	if (position < 0 || position >= (*this).size())
		throw std::logic_error("Index out of range");
	return BitHolder(position, (*this));
}
template <typename T>
BitsetT<T>::BitHolder::operator bool() const {
	return number >> (number_bit % type_size) & 1;
}
template <class T>
typename BitsetT<T>::BitHolder& BitsetT<T>::BitHolder::operator=(const bool rhs) {
	T x = (T(1) << (*this).number_bit);
	if (rhs == true)
		(*this).number |= x;
	else
		(*this).number &= ~(x);
	return *this;
}
#endif