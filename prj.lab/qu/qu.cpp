#include <iostream>
#include <vector>
#include <algorithm>
class Set {
public:
	Set() {}
	Set(std::vector <int> a, size_t size_) {
		set = a;
		size = size_;
		unique();
		sort(set.begin(), set.end());
	}
	void unique() {
		for (int i = 0; i < size; i++) {
			for (int j = i + 1; j < set.size(); j++) {
				if (set[i] == set[j]) {
					set.erase(set.begin() + j);
					j--;
				}
			}
		}
	}
	int size_set() {
		return set.size();
	}
	void add(int data) {
		set.push_back(data);
		unique();
		sort(set.begin(), set.end());
	}
	int operator [](int idx) {
		return set[idx];
	}
private:
	size_t size = 0;
	std::vector <int> set;
};

int main() {
	int size = 10;
	int filler;
	std::vector <int> a(10);
	for (int i = 0; i < size; i++) {
		std::cin >> filler;
		a[i] = filler;
	}
	Set s(a, size);
	s.add(7);
	for (int i = 0; i < s.size_set(); i++) {
		std::cout << s[i] << " ";
	}
}