#pragma once
#include <iostream>

namespace rnk {
	typedef enum Nucl : unsigned char{
		A, G, C, T
	}Nucl;	

	class RNK {
	public:
		RNK() {};		
		~RNK() {
			delete[] baseArr;
		}
		void push_back(const Nucl elem);//+
		RNK(Nucl elem, size_t count);//+
		class NuclRef {//+
		public:
			NuclRef(const size_t index, RNK& obj);
			~NuclRef() {}
			NuclRef& operator=(Nucl elem);
			operator Nucl();
		private:
			size_t nucl_index;
			RNK* rnk_obj = nullptr;
		};
		Nucl getNuclByIndex(const size_t index) const; //+
		void changeNuclByIndex(const size_t index, Nucl elem);//+
		const size_t capacity(void) const;//+		
		RNK& operator=(RNK& r2);//+
		RNK(const RNK& other);//+
		NuclRef operator[]( size_t index);//+
		RNK operator+(RNK& r2);//+
		size_t cardinality(const Nucl value);//+
		void trim( size_t lastIndex);//+		
		//std::unordered_map< Nucl, int, std::hash<int> > cardinality();		
		bool operator==(RNK& r2);//+
		bool operator!=(RNK& r2);//+
		RNK& operator!(void);//+
		bool isComplementary(RNK& r2);//
		RNK& split(size_t index);
	private:
		unsigned char* baseArr = nullptr;
		size_t size_baseArr = 0;
		size_t size_vector = 0;
		void Push(void) {
			if (size_baseArr == 0) {
				baseArr = new unsigned char[1];	
				baseArr[0] = 0;
				++size_baseArr;
			}
			else {
				unsigned char* newArr = new unsigned char[size_baseArr * 2];
				for (size_t i = 0; i < size_baseArr; ++i) {
					newArr[i] = baseArr[i];
				}
				for (size_t i = size_baseArr; i < size_baseArr * 2; ++i) {
					newArr[i] = 0;
				}
				size_baseArr *= 2;
				delete[] baseArr;
				baseArr = newArr;
			}
		}
		void Pop(void) {
			if (size_baseArr > 1) {
				unsigned char* newArr = new unsigned char[--size_baseArr];
				for (size_t i = 0; i < size_baseArr; ++i) {
					newArr[i] = baseArr[i];
				}				
				delete[] baseArr;
				baseArr = newArr;
			}
			if (size_baseArr == 1) {
				delete[] baseArr;
				--size_baseArr;
			}
		}
	};
}