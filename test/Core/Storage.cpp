#include "BlasBooster/Core/Storage.h"
#include "gtest/gtest.h"

using namespace std;
using namespace BlasBooster;

TEST(Storage, DISABLED_FlexibleSizeMoveAssignment)
{
	typedef Storage<int,false,false,0> StorageType;
	StorageType A(3);
	StorageType B = A;
	StorageType C = std::move(B);

	EXPECT_TRUE(B.equal(StorageType()));
	EXPECT_TRUE(C.equal(A));
}

TEST(Storage, DISABLED_FixedSizeMoveAssignment)
{
	typedef Storage<int,false,true,3> StorageType;
	StorageType A;
	StorageType B = A;
	StorageType C = std::move(B);

	// No move assignment operator available for fixed size storage,
	// therefore the copy assignment operator will be called.
	EXPECT_TRUE(B.equal(A));
	EXPECT_TRUE(C.equal(A));
}

TEST(Storage, FlexibleSizeSwap)
{
	Storage<int,false,false,0> A1 {2,-3};
	Storage<int,false,false,0> A2 {-4,0,1};
	Storage<int,false,false,0> B1 = A1;
	Storage<int,false,false,0> B2 = A2;

    swap(B1,B2);

    EXPECT_TRUE(B1.equal(A2));
    EXPECT_TRUE(B2.equal(A1));
}

TEST(Storage, CompareFixedWithFlexibleSize)
{
	Storage<double,false,true,2> fixed2{2,3};
	Storage<double,false,true,3> fixed3 = {1,2,3};
	Storage<double,false,false,0> flexible2{2,3};
	Storage<double,false,false,0> flexible3 = {1,2,3};

	EXPECT_FALSE(fixed2.equal(fixed3));
	EXPECT_FALSE(fixed2.notEqual(flexible2));
	EXPECT_FALSE(fixed2.equal(flexible3));
}

TEST(Storage, FlexibleSizeStriped)
{
	vector<int> a1 {0,1,2,3,4,5,6,7,8,9};

	Storage<int,false,false,0,true> storage(&(a1[0]),2,3,2);

	vector<int> c1 = {0,1,4,5,8,9};
	vector<int> c2 = {9,8,5,4,1,0};

	{
		vector<int> c3;
		for (Storage<int,false,false,0,true>::iterator iterCur(storage.begin()), iterEnd(storage.end());
			iterCur != iterEnd; ++iterCur)
		{
			c3.push_back(*iterCur);
		}
		EXPECT_EQ(c3,c1);
	}
	{
		vector<int> c3;
		for (Storage<int,false,false,0,true>::const_iterator iterCur(storage.begin()), iterEnd(storage.end());
			iterCur != iterEnd; ++iterCur)
		{
			c3.push_back(*iterCur);
		}
		EXPECT_EQ(c3,c1);
	}
	{
		vector<int> c3;
		for (Storage<int,false,false,0,true>::iterator iterCur(storage.rbegin()), iterEnd(storage.rend());
			iterCur != iterEnd; --iterCur)
		{
			c3.push_back(*iterCur);
		}
		EXPECT_EQ(c3,c2);
	}
	{
		vector<int> c3;
		for (Storage<int,false,false,0,true>::const_iterator iterCur(storage.rbegin()), iterEnd(storage.rend());
			iterCur != iterEnd; --iterCur)
		{
			c3.push_back(*iterCur);
		}
		EXPECT_EQ(c3,c2);
	}

	const int* a2 = &(a1[0]);
	Storage<const int,false,false,0,true> s3(a2,2,3,2);

	{
		vector<int> c3;
		for (Storage<const int,false,false,0,true>::const_iterator iterCur(s3.begin()), iterEnd(s3.end());
			iterCur != iterEnd; ++iterCur)
		{
			c3.push_back(*iterCur);
		}
		EXPECT_EQ(c3,c1);
	}
}
