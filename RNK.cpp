#include "RNK.h"
#include <cassert>

using namespace rnk;

Nucl RNK::getNuclByIndex(const size_t index) const{
	assert(index < size_vector);
	return (Nucl)((baseArr[(index/4)] >> (3 - index % 4) * 2)&3);
}

void RNK::changeNuclByIndex(const size_t index, Nucl elem) {
	assert(index < this->capacity());
	baseArr[index / 4] &= ~((unsigned char)3 << (3 - index % 4) * 2);
	baseArr[index / 4] += elem << (3 - index % 4) * 2;
}

RNK::NuclRef::NuclRef(const size_t index, RNK& obj) {
	nucl_index = index;
	rnk_obj = &obj;
}

RNK::NuclRef& RNK::NuclRef::operator=(Nucl elem) {
	rnk_obj->changeNuclByIndex(nucl_index, elem);
	return *this;
}

RNK::NuclRef::operator Nucl(){
	return rnk_obj->getNuclByIndex(nucl_index);
}

RNK::NuclRef RNK::operator[](const size_t index) {
	return NuclRef(index, *this);
}

void RNK::push_back(const Nucl elem){
	++size_vector;
	if (size_vector / 4 > size_baseArr) {
		Push();
	}
	baseArr[(size_vector - 1)/4] += elem << (3 - (size_vector - 1)) * 2;
}

const size_t RNK::capacity(void) const{
	return size_vector;
}

RNK& RNK::operator=(const RNK& r2) {
	for (size_t i = 0; i < this->capacity(); ++i) {
		this->push_back(r2.getNuclByIndex(i));
	}
	return *this;
}

RNK::RNK(const RNK& r2) {
	(*this) = r2;
}

RNK RNK::operator+(RNK& r2) {
	RNK sum;
	for (size_t i = 0; i < this->capacity(); ++i) {
		sum.push_back((*this)[i]);
	}
	for (size_t i = 0; i < r2.capacity(); ++i) {
		sum.push_back(r2[i]);
	}
	return sum;
}



int main() {

	return 0;
}