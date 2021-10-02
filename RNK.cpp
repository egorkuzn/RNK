#include "RNK.h"
#include <cassert>

using namespace rnk;

Nucl RNK::getNuclByIndex(const size_t index) const{
	if (!(index < size_vector)) {
		exit(EXIT_FAILURE);
	}
	return (Nucl)((baseArr[index/4] >> (3 - index % 4) * 2) & 3);
}

void RNK::changeNuclByIndex( size_t index, Nucl elem) {
	if (!(index < size_vector)) {
		exit(EXIT_FAILURE);
	}
	--cardinality.at(getNuclByIndex(index));
	++cardinality.at(elem);
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
	while (index >= this->capacity()) {
		this->push_back(A);
	}
	return NuclRef(index, *this);
}

void RNK::push_back(const Nucl elem){
	++size_vector;
	if (size_vector > size_baseArr * 4) {
		Push();
	}
	if (cardinality.count(elem) == 0) {
		cardinality.insert(RNK_map::value_type(elem, 1));
	}
	else{
		++cardinality.at(elem);
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
		cardinality.clear();
	}
	if (other.capacity() > 0) {
		for (size_t i = 0; i < other.capacity(); ++i) {
			this->push_back(other.getNuclByIndex(i));
		}		
	}		
	size_vector = other.capacity();
	size_baseArr = other.capacity();
}

RNK& RNK::operator=(const RNK& r2) {
	if (this == &r2) {
		return *this;
	}
	if (size_vector != 0){
		size_vector = 0;
		size_baseArr = 0;
		cardinality.clear();
		delete[] baseArr;
	}
	for (size_t i = 0; i < r2.capacity(); ++i) {
		this->push_back(r2.getNuclByIndex(i));
	}
	return *this;
}

RNK RNK::operator+(const RNK& r2) {
	RNK sum;
	for (size_t i = 0; i < this->capacity(); ++i) {
		sum.push_back((*this)[i]);
	}
	for (size_t i = 0; i < r2.capacity(); ++i) {
		sum.push_back(r2.getNuclByIndex(i));
	}
	return sum;
}

void RNK::trim( size_t lastIndex){
	for (size_t i = size_vector - 1; i >= lastIndex; --i) {
		(*this)[i] = A;
		if (size_vector != 0) {
			--cardinality.at((*this)[i]);
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

bool RNK::operator==(const RNK& r2) const{	
	if (size_vector == r2.capacity()) {
		for (size_t i = 0; i < size_vector; ++i) {
			if ((Nucl)(this->getNuclByIndex(i)) != (Nucl)r2.getNuclByIndex(i)) {
				return false;
			}
		}
		return true;
	}
	return false;
}

RNK RNK::operator!(void) const{
	RNK copy;
	for (size_t i = 0; i < size_vector; ++i) {
		copy.push_back((Nucl)(((Nucl)3 - ((Nucl)(*this).getNuclByIndex(i)) & 3)));
	}
	return copy;
}

bool RNK::operator!=(RNK& r2) {
	return !((*this) == r2);
}

bool RNK::isComplementary(const RNK& r2) const{
	return *this == !r2;
}

RNK RNK::split(size_t index) {
	RNK copy;
	for (size_t i = index; i < size_vector; ++i) {
		copy.push_back((*this).getNuclByIndex(i));
	}
	this->trim(index);
	return copy;
}

DNK::DNK(const RNK& rnk1, const RNK& rnk2){
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

DNK& DNK::operator=(const RNK& rnk){
	if (this->capacity()) {
		this->trim(0);
		cardinality.clear();
	}
	for (size_t i = 0; i < rnk.capacity(); ++i) {
		this->push_back(rnk.getNuclByIndex(i));
	}
	return *this;
}

RNK func(size_t length) {
	RNK example;
	for (size_t i = 0; i < length; ++i) {
		example.push_back((Nucl)(rand() & 3));
	}
	return example;
}


int main() {
	RNK rnk = func(5);
	for (size_t i = 0; i < rnk.capacity(); ++i)
		std::cout << (short)rnk[i] << " ";
	DNK example(rnk, !rnk);
	std::cout << std::endl;
	example = example + example;
	example.trim(example.capacity()-1);
	for (size_t i = 0; i < example.capacity(); ++i)
		std::cout << (short)example[i] << " ";
	std::cout << "A: " << example.cardinality.at(A) <<" C:"<< example.cardinality.at(C)<<" G:"<< example.cardinality.at(G)<<" T: "<< example.cardinality.at(T);
	return 0;
}
