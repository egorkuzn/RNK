#include <gtest/gtest.h>

#include "../RNK.h" 
#include "../DNK.h" 

using namespace rnk;
using namespace dnk;

RNK func(size_t length) {
	RNK example_rnk;
	for (size_t i = 0; i < length; ++i) {
		example_rnk.push_back((Nucl)(rand() & 3));
	}
	return example_rnk;
}

TEST(getNuclByIndex, arr_elem_rnk) { 
	RNK example_rnk = func(1000);
	ASSERT_EQ((unsigned int)example_rnk.getNuclByIndex(5), (unsigned int)example_rnk[5]);
}

TEST(getNuclByIndex, arr_elem_dnk) { 
	RNK example_rnk = func(1000);
	DNK example_dnk(example_rnk, !example_rnk);
	ASSERT_EQ((unsigned int)example_dnk.getNuclByIndex(5), (unsigned int)example_dnk[5]);
}

TEST(getNuclByIndex, changed_nucl_rnk) { 
	RNK example_rnk = func(1000);
	example_rnk[5] = G;
	ASSERT_EQ((unsigned char)example_rnk.getNuclByIndex(5), (unsigned char)G);
}

TEST(getNuclByIndex, changed_nucl_dnk) {
	RNK example_rnk = func(1000);
	DNK example_dnk(example_rnk, !example_rnk);
	example_dnk[5] = G;
	ASSERT_EQ((unsigned char)example_dnk.getNuclByIndex(5), (unsigned char)G);
}

TEST(getNuclByIndex, negative_rnk) {
	RNK example_rnk = func(10);
	EXPECT_EXIT(example_rnk.getNuclByIndex(-5), testing::ExitedWithCode(1), "BAD INDEX");
}

TEST(getNuclByIndex, negative_dnk) {
	RNK example_rnk = func(10);
	DNK example_dnk(example_rnk, !example_rnk);
	EXPECT_EXIT(example_dnk.getNuclByIndex(-5), testing::ExitedWithCode(1), "BAD INDEX");
}

TEST(capacity, 1000000000_rnk) {
	RNK example_rnk = func(1000);
	size_t allocLength = example_rnk.capacity();
	ASSERT_TRUE(allocLength >= 1000 * 2 / 8 / sizeof(uint64_t));
	size_t count = 10000;
	while (count < 1000001) {
		example_rnk[count] = A;
		ASSERT_TRUE(example_rnk.capacity() == count + 1);
		std::cout << std::endl << count << std::endl;
		count *= 10;
	}
}

TEST(capacity, 1000000000_dnk) {
	RNK example_rnk = func(1000);
	DNK example_dnk(example_rnk, !example_rnk);
	size_t allocLength = example_dnk.capacity();
	ASSERT_TRUE(allocLength >= 1000 * 2 / 8 / sizeof(uint64_t));
	size_t count = 10000;
	while (count < 1000001) {
		example_dnk[count] = A;
		ASSERT_TRUE(example_dnk.capacity() == count + 1);
		std::cout << std::endl << count << std::endl;
		count *= 10;
	}
}

TEST(changeNuclByIndex, usual_rnk) {
	RNK example_rnk = func(1000);
	example_rnk.changeNuclByIndex(8, G);
	ASSERT_EQ((unsigned char)example_rnk[8], (unsigned char)G);
}

TEST(changeNuclByIndex, usual_dnk) {
	RNK example_rnk = func(1000);
	DNK example_dnk(example_rnk, !example_rnk);
	example_dnk.changeNuclByIndex(8, G);
	ASSERT_EQ((unsigned char)example_dnk[8], (unsigned char)G);
}


TEST(trim, rnk) {
	RNK example_rnk = func(5);
	example_rnk.trim(-1);
	EXPECT_EQ(example_rnk.capacity(), 5);
	example_rnk.trim(-1);
	EXPECT_EQ(example_rnk.capacity(), 5);
	example_rnk.trim(0);
	EXPECT_EQ(example_rnk.capacity(), 0);
	example_rnk.trim(0);
	EXPECT_EQ(example_rnk.capacity(), 0);
}

TEST(trim, dnk) {
	RNK example_rnk = func(5);
	DNK example_dnk(example_rnk, !example_rnk);
	example_dnk.trim(-1);
	EXPECT_EQ(example_dnk.capacity(), 5);
	example_dnk.trim(-1);
	EXPECT_EQ(example_dnk.capacity(), 5);
	example_dnk.trim(0);
	EXPECT_EQ(example_dnk.capacity(), 0);
	example_rnk.trim(0);
	EXPECT_EQ(example_dnk.capacity(), 0);
}


TEST(EqualOprtr_NotEqualOprtr, rnk) {
	RNK example_rnk_A = func(10);
	RNK example_rnk_B(A, 10);
	EXPECT_FALSE(example_rnk_A == example_rnk_B);
	EXPECT_TRUE(example_rnk_A != example_rnk_B);
	example_rnk_B[20] = G;
	EXPECT_FALSE(example_rnk_A == example_rnk_B);
	EXPECT_TRUE(example_rnk_A != example_rnk_B);
	example_rnk_A.trim(0);
	example_rnk_B.trim(0);
	EXPECT_FALSE(example_rnk_A != example_rnk_B);
	EXPECT_TRUE(example_rnk_A == example_rnk_B);
}

TEST(EqualOprtr_NotEqualOprtr, dnk) {
	RNK example_rnk_A = func(10);
	RNK example_rnk_B(A, 10);
	DNK example_dnk_A(example_rnk_A, !example_rnk_A);
	DNK example_dnk_B(example_rnk_B, !example_rnk_B);
	EXPECT_FALSE(example_dnk_A == example_dnk_B);
	EXPECT_TRUE(example_dnk_A != example_dnk_B);
	example_dnk_B[20] = G;
	EXPECT_FALSE(example_dnk_A == example_dnk_B);
	EXPECT_TRUE(example_dnk_A != example_dnk_B);
	example_dnk_A.trim(0);
	example_dnk_B.trim(0);
	EXPECT_FALSE(example_dnk_A != example_dnk_B);
	EXPECT_TRUE(example_dnk_A == example_dnk_B);
}

TEST(AddOprtr, rnk) {
	RNK example_rnk_A;
	RNK example_rnk_B(A, 100);
	EXPECT_EQ(example_rnk_B, example_rnk_B + example_rnk_A);
	EXPECT_EQ(example_rnk_A + example_rnk_A, example_rnk_A);
	example_rnk_A = func(50);
	EXPECT_EQ((example_rnk_B + example_rnk_B).capacity(), example_rnk_B.capacity() * 2);
}

TEST(AddOprtr, dnk) {
	RNK example_rnk_A;
	RNK example_rnk_B(A, 100);
	DNK example_dnk_A(example_rnk_A, !example_rnk_A);
	DNK example_dnk_B(example_rnk_B, !example_rnk_B);
	EXPECT_EQ(example_dnk_B, example_dnk_B + example_dnk_A);
	EXPECT_EQ(example_dnk_A + example_dnk_A, example_dnk_A);
	example_dnk_A = func(50);
	EXPECT_EQ((example_dnk_B + example_dnk_B).capacity(), example_dnk_B.capacity() * 2);
}

TEST(NegationANDisComplementary, rnk) {
	RNK example_rnk;
	EXPECT_EQ(example_rnk, !example_rnk);
	example_rnk = func(1000);
	EXPECT_TRUE(example_rnk.isComplementary(!example_rnk));
	EXPECT_TRUE((!example_rnk).isComplementary(example_rnk));
}

TEST(NegationANDisComplementary, dnk) {
	RNK example_rnk;
	DNK example_dnk(example_rnk, !example_rnk);
	EXPECT_EQ(example_dnk, !example_dnk);
	example_dnk = func(1000);
	EXPECT_TRUE(example_dnk.isComplementary(!example_dnk));
	EXPECT_TRUE((!example_dnk).isComplementary(example_dnk));
}

TEST(Split, rnk) {
	RNK example_rnk_A = func(100);
	RNK example_rnk_B = example_rnk_A.split(-1);
	EXPECT_EQ(example_rnk_A.capacity(), 100);
	EXPECT_EQ(example_rnk_B.capacity(), 0);
	example_rnk_B = example_rnk_A.split(0);
	EXPECT_EQ(example_rnk_A.capacity(), 0);
	EXPECT_EQ(example_rnk_B.capacity(), 100);
	RNK copy = example_rnk_B;
	example_rnk_A = example_rnk_B.split(50);
	for (size_t i = 0; i < 50; ++i) {
		EXPECT_TRUE((Nucl)copy[i] == (Nucl)example_rnk_B[i]);
	}
	for (size_t i = 50; i < 100; ++i) {
		EXPECT_TRUE((Nucl)copy[i] == (Nucl)example_rnk_A[i-50]);
	}
}

TEST(Split, dnk) {
	RNK example_rnk_A = func(100);
	RNK example_rnk_B;
	DNK example_dnk_A(example_rnk_A, !example_rnk_A);
	DNK example_dnk_B(example_rnk_B, !example_rnk_B);
	example_dnk_B = example_dnk_A.split(-1);
	EXPECT_EQ(example_dnk_A.capacity(), 100);
	EXPECT_EQ(example_dnk_B.capacity(), 0);
	example_dnk_B = example_dnk_A.split(0);
	EXPECT_EQ(example_dnk_A.capacity(), 0);
	EXPECT_EQ(example_dnk_B.capacity(), 100);
	RNK copy = example_dnk_B;
	example_dnk_A = example_dnk_B.split(50);
	for (size_t i = 0; i < 50; ++i) {
		EXPECT_TRUE((Nucl)copy[i] == (Nucl)example_dnk_B[i]);
	}
	for (size_t i = 50; i < 100; ++i) {
		EXPECT_TRUE((Nucl)copy[i] == (Nucl)example_dnk_A[i - 50]);
	}
}


TEST(Cardinality, rnk) {
	RNK example_rnk_A = func(1000);
	size_t count = 0;
	for (RNK_map::const_iterator it = \
		(example_rnk_A.cardinality).begin();
		it != example_rnk_A.cardinality.end(); ++it) {
		count += it->second;
	}
	EXPECT_EQ(count, example_rnk_A.capacity());
}

TEST(Cardinality, dnk) {
	RNK example_rnk_A = func(1000);
	DNK example_dnk_A(example_rnk_A, !example_rnk_A);
	size_t count = 0;
	for (RNK_map::const_iterator it = \
		(example_dnk_A.cardinality).begin();
		it != example_dnk_A.cardinality.end(); ++it) {
		count += it->second;
	}
	EXPECT_EQ(count, example_dnk_A.capacity());
}

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
