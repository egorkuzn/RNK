#include "DNK.h"

using namespace dnk;

DNK::DNK(const RNK& rnk1, const RNK& rnk2) {
	if (rnk1.isComplementary(rnk2)) {
		for (size_t i = 0; i < rnk1.capacity(); ++i) {
			this->push_back(rnk1.getNuclByIndex(i));
		}
	}
	else {
		std::cout << std::endl << "Aren't complementary, returns empty object!"\
			<< std::endl;
	}

}

DNK& DNK::operator=(const RNK& other) {
	if (this->capacity()) {
		this->trim(0);
		cardinality.clear();
	}
	for (size_t i = 0; i < other.capacity(); ++i) {
		this->push_back(other.getNuclByIndex(i));
	}
	return *this;
}
