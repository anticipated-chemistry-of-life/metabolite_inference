//
// Created by VISANI Marco on 17.10.2024.
//

#include "TStorageZ.h"
#include "gtest/gtest.h"

TEST(TStorageZ_Tests, test_constructor) {
	const TStorageZ z(1000);
	EXPECT_EQ(z.is_one(), true);
	EXPECT_EQ(z.get_coordinate(), 1000);
}