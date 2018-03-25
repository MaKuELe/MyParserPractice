#include <iostream>
#include <string.h>
//#include <gtest\gtest.h>
//#include <TokenItem.h>
#include <list>
#include <LineStringParser.h>
#include <string>
/*TEST(TEST, One) {

	EXPECT_EQ(0x22, '\"');
}*/

int main(int argc, char *argv[]) {
	using namespace std;
	argc = 2;
	string instr =
		"Name:Alfa\n\
List:{\n\
	A:1\n\
	sub:{\n\
		B: ABC\n\
		C:\"ADASg\"\n\
	}\n\
	beta:(1,2,3,4) \
}";
	LineStringParser parser(instr.c_str());
/*
	ListElement li;
	li.listname = "List";
	li.listmenber.emplace_back();
	li.listmenber.at(0) = new nomaltoken("A", "1");

	li.listmenber.emplace_back();
	li.listmenber.at(1) = new ListElement("sub");

	dynamic_cast<ListElement *>(li.listmenber.at(1))->listmenber.emplace_back();
	dynamic_cast<ListElement *>(li.listmenber.at(1))->listmenber.at(0)= new nomaltoken("B", "ABC");

	dynamic_cast<ListElement *>(li.listmenber.at(1))->listmenber.emplace_back();
	dynamic_cast<ListElement *>(li.listmenber.at(1))->listmenber.at(1) = new nomaltoken("C", "ADASG");

	li.listmenber.emplace_back();
	li.listmenber.at(2) = new ArrayElement("Arr");
	dynamic_cast<ArrayElement *>(li.listmenber.at(2))->arraymenber.emplace_back("1");
	dynamic_cast<ArrayElement *>(li.listmenber.at(2))->arraymenber.emplace_back("2");
	dynamic_cast<ArrayElement *>(li.listmenber.at(2))->arraymenber.emplace_back("3");
	dynamic_cast<ArrayElement *>(li.listmenber.at(2))->pushParam("4");


	*/

	
	return 0;

//	::testing::InitGoogleTest(&argc, argv);

//	return RUN_ALL_TESTS();

}
