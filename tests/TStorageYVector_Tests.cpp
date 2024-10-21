//
// Created by VISANI Marco on 17.10.2024.
//

#include "TStorageYVector.h"
#include "gtest/gtest.h"

TEST(YStorageVector_Tests, test_constructor) {
	const TStorageYVector y(1000);
	EXPECT_EQ(y.is_one(1458), false);
}

TEST(YStorageVector_Tests, set_to_one) {
	TStorageYVector y(1000);
	y.set_to_one(1458);
	EXPECT_EQ(y.is_one(1458), true);
}

TEST(YStorageVector_Tests, set_to_zero) {
	TStorageYVector y(1000);
	y.set_to_zero(1458);
	EXPECT_EQ(y.is_one(1458), false);
}

TEST(YStorageVector_Tests, set_to_one_and_zero) {
	TStorageYVector y(1000);
	y.set_to_one(1458);
	EXPECT_EQ(y.is_one(1458), true);
	y.set_to_zero(1458);
	EXPECT_EQ(y.is_one(1458), false);
}

TEST(YStorageVector_Tests, get_size_of_vector) {
	TStorageYVector y(100000);
	EXPECT_EQ(y.size(), 0);
	y.set_to_one(1458);
	EXPECT_EQ(y.size(), 1);
	y.set_to_one(1459);
	EXPECT_EQ(y.size(), 2);
	y.set_to_one(1460);
	EXPECT_EQ(y.size(), 3);
	y.set_to_zero(1458);
	EXPECT_EQ(y.size(), 3);
}

TEST(YStorageVector_Tests, get_fraction_of_ones) {
	TStorageYVector y(100000);
	y.set_to_one(1458);
	y.set_to_one(16);
	y.set_to_one(17);
	y.set_to_one(4587);

	// since we haven't updated the counter, the fraction of ones should be 0
	EXPECT_EQ(y.get_fraction_of_ones(1458), 0.0);

	y.add_to_counter(100);
	EXPECT_EQ(y.get_fraction_of_ones(1458), 0.00002);

	y.add_to_counter(1000);
	EXPECT_EQ(y.get_fraction_of_ones(1458), 0.00004);

	y.add_to_counter(3);
	EXPECT_EQ(y.get_fraction_of_ones(1458), 0.00004);

	EXPECT_EQ(y.get_fraction_of_ones(16), 0.00004);

	y.set_to_zero(16);
	EXPECT_EQ(y.get_fraction_of_ones(16), 0.00004);
}

TEST(YStorageVector_Tests, reset_counter) {
	TStorageYVector y(100000);
	y.set_to_one(1458);
	y.set_to_one(16);
	y.set_to_one(17);
	y.set_to_one(4587);

	y.add_to_counter(100);
	y.add_to_counter(1000);
	y.add_to_counter(3);

	y.reset_counts();

	EXPECT_EQ(y.get_fraction_of_ones(1458), 0.0);
	EXPECT_EQ(y.get_fraction_of_ones(16), 0.0);
}

TEST(YStorageVector_Tests, remove_zeros_from_vector) {
	TStorageYVector y(100000);
	y.set_to_one(1458);
	y.set_to_one(16);
	y.set_to_one(17);
	y.set_to_one(4587);

	y.add_to_counter(100);
	y.add_to_counter(1000);
	y.add_to_counter(3);

	y.remove_zeros();

	EXPECT_EQ(y.size(), 4);
}

TEST(YStorageVector_Tests, remove_zeros_from_vector_2) {
	TStorageYVector y(100000);
	y.set_to_one(1458);
	y.set_to_zero(16);
	y.set_to_one(17);
	y.set_to_one(4587);

	y.add_to_counter(100);
	y.add_to_counter(1000);
	y.add_to_counter(3);

	y.remove_zeros();

	EXPECT_EQ(y.size(), 3);
}
