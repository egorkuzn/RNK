#pragma once
#include <iostream>

namespace rnk {
	typedef enum Nucl : unsigned char{
		A, G, C, T
	}Nucl;	

	class RNK {
	public:
		RNK() {};
		void push_back(const Nucl elem) ;//+
		class NuclRef {//+
		public:
			NuclRef(const size_t index, RNK& obj);
			NuclRef& operator=(Nucl elem);
			operator Nucl();
		private:
			size_t nucl_index;
			RNK* rnk_obj = nullptr;
		};
		Nucl getNuclByIndex(const size_t index) const; //+
		void changeNuclByIndex(const size_t index, Nucl elem);//+
		const size_t capacity(void) const;//+
		size_t cardinality(Nucl value);
		RNK& operator=(const RNK& r2);//+
		RNK(const RNK& r2);//+
		NuclRef operator[](const size_t index);//+
		RNK operator+(RNK& r2);//+
		
		// забыть содержимое от lastIndex и дальше
		void trim(size_t lastIndex);
		//для нуклеотида  - число значений
		
		

		//аналогично но сразу для всех типов тритов
		//std::unordered_map< Nucl, int, std::hash<int> > cardinality();
		
		opertator == ;
		operator!=;
		operator !;
		RNK(const& RNK);
		isComplementary(RNK&);
		split(size_t index);
	private:
		unsigned char* baseArr = nullptr;
		size_t size_baseArr = 0;
		size_t size_vector = 0;
		void Push(void) {
			if (size_baseArr == 0) {
				unsigned char* newArr = new unsigned char[1];
				++size_baseArr;
			}
			else {
				unsigned char* newArr = new unsigned char[size_baseArr * 2];
				for (size_t i = 0; i < size_baseArr; ++i) {
					newArr[i] = baseArr[i];
				}
				size_baseArr *= 2;
				delete[] baseArr;
				baseArr = newArr;
			}
		}
	};
}