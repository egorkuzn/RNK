#include "RNK.h"
#include <cassert>

using namespace rnk;

Nucl RNK::getNuclByIndex(const size_t index) const{
	assert(index < size_vector);
	return (Nucl)((baseArr[index/4] >> (3 - index % 4) * 2) & 3);
}

void RNK::changeNuclByIndex( size_t index, Nucl elem) {
	assert(index < this->capacity());
	baseArr[index / 4] -= ((baseArr[index / 4] >> (3 - index % 4) * 2) & 3) << ((3 - index % 4) * 2);
	baseArr[index / 4] += elem << (3 - index % 4) * 2;
}

RNK::NuclRef::NuclRef( size_t index, RNK& obj) {
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
	if (size_vector > size_baseArr * 4) {
		Push();
	}
	baseArr[(size_vector - 1)/4] += (unsigned char)elem << (3 - (size_vector - 1) % 4) * 2;
}

RNK::RNK(Nucl elem, size_t count)
{
	for (size_t i = 0; i < count; ++i) {
		this->push_back(elem);
	}
}

const size_t RNK::capacity(void) const{
	return size_vector;
}

RNK::RNK(const RNK& other) {
	if (this->capacity() > 0) {
		delete baseArr;
		size_vector = 0;
		size_baseArr = 0;
	}
	if (other.capacity() > 0) {
		for (size_t i = 0; i < other.capacity(); ++i) {
			this->push_back(other.getNuclByIndex(i));
		}		
	}		
	size_vector = other.capacity();
	size_baseArr = other.capacity();
}

RNK& RNK::operator=(RNK& r2) {
	if (this == &r2) {
		return *this;
	}
	if (size_vector != 0){
		size_vector = 0;
		size_baseArr = 0;
		delete[] baseArr;
	}
	for (size_t i = 0; i < r2.capacity(); ++i) {
		this->push_back(r2.getNuclByIndex(i));
	}
	return *this;
}

RNK& RNK::operator+(RNK& r2) {
	RNK sum;
	for (size_t i = 0; i < this->capacity(); ++i) {
		sum.push_back((*this)[i]);
	}
	for (size_t i = 0; i < r2.capacity(); ++i) {
		sum.push_back(r2[i]);
	}
	return sum;
}

size_t RNK::cardinality(const Nucl value){
	size_t inc = 0;
	for (size_t i = 0; i < this->capacity(); ++i) {
		if ((*this)[i] == value) {
			++inc;
		}
	}
	return inc;
}

void RNK::trim( size_t lastIndex){
	for (size_t i = size_vector - 1; i >= lastIndex; --i) {
		(*this)[i] = A;
		if (size_vector != 0) {
			--size_vector;
		}
		else {
			return;
		}
		if (i % 4 == 0) {
			Pop();
		}
		if (size_vector == 0) {
			return;
		}
	}
}

bool RNK::operator==(RNK& r2) {	
	if (size_vector == r2.capacity()) {
		for (size_t i = 0; i < size_vector; ++i) {
			if ((Nucl)(*this)[i] != (Nucl)r2[i]) {
				return false;
			}
		}
		return true;
	}
	return false;
}

RNK& RNK::operator!(void){
	RNK copy;
	for (size_t i = 0; i < size_vector; ++i) {
		copy.push_back((Nucl)(((Nucl)3 - ((Nucl)(*this)[i]) & 3)));
	}
	return copy;
}

bool RNK::operator!=(RNK& r2) {
	return !((*this) == r2);
}

bool RNK::isComplementary(RNK& r2){
	return *this == !r2;
}

RNK& RNK::split(size_t index) {
	RNK copy;
	for (size_t i = index; i < size_vector; ++i) {
		copy.push_back((*this).getNuclByIndex(i));
	}
	this->trim(index);
	return copy;
}

int main() {
	RNK my_rnk;
	unsigned short nucl;
	for (size_t i = 0; i < 10; ++i) {
		std::cin >> nucl;
		my_rnk.push_back((Nucl)nucl);
	}
	my_rnk = !my_rnk;
	return 0;
}