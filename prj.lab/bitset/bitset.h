#include <iostream>
#include<vector>
#pragma once
#ifndef BITSET_BITSET_H_20220309
#define BITSET_BITSET_H_20220309
class Bitset {
public:
	typedef int64_t container_type;
	class BitHolder {
	public:
		friend class Bitset;
		BitHolder() = default;
		BitHolder& operator=(const bool rhs);
		operator bool() const;
		explicit BitHolder(int position, Bitset& data);
		~BitHolder() = default;
	private:
		int64_t& number;
		int64_t number_bit;
	};
	Bitset(int64_t size = 0, const bool filler = false);
	Bitset(const Bitset& copy);
	Bitset(const std::string& copy);
	Bitset& operator=(const Bitset& rhs);
	bool operator==(const Bitset& rhs) const;
	bool operator!=(const Bitset& rhs) const;
	bool operator [] (const int64_t position) const;
	Bitset& operator&=(const Bitset& rhs);
	Bitset& operator|=(const Bitset& rhs);
	Bitset& operator^=(const Bitset& rhs);
	Bitset operator~() const;
	Bitset& operator<<=(const int64_t rhs);
	Bitset& operator>>=(const int64_t rhs);
	BitHolder operator[](const int64_t position);
	void resize(const int64_t size, const bool filler = false);
	int64_t size() const {
		return (*this).bitsize;
	}
	~Bitset() = default;
private:
	int64_t bitsize = 0;
	static const int type_size = sizeof(int64_t) * 8;
	std::vector<container_type> masks;
	std::vector<container_type> bitset;
	void set_masks();
};
Bitset const operator&(const Bitset& lhs, const Bitset& rhs);
Bitset const operator|(const Bitset& lhs, const Bitset& rhs);
Bitset const operator^(const Bitset& lhs, const Bitset& rhs);
Bitset const operator<<(const Bitset& lhs, const uint64_t rhs);
Bitset const operator>>(const Bitset& lhs, const uint64_t rhs);
std::ostream& operator<<(std::ostream& ostream, const Bitset& data);
std::istream& operator>>(std::istream& istream, Bitset& data);
#endif