#include "RNK.h"

using namespace rnk;

NuclRef RNK::operator[](size_t index) {
	return NuclRef(index);
}

void RNK::push_back(const Nucl elem) {
	++size_vector;
	if (size_vector / 4 > size_baseArr) {
		Push();
	}
	baseArr[size_baseArr - 1] += elem << (3 - (size_vector - 1)) * 2;
}

size_t RNK::capacity(void) {
	return size_vector;
}

RNK RNK::operator+(RNK& r2) {
	RNK sum;
	for (size_t i = 0; i < this->capacity(); ++i) {
		sum.push_back();
	}
	for (size_t i = 0; i < r2.capacity(); ++i) {
		sum.push_back();
	}
	return sum;
}

int main() {

	return 0;
}