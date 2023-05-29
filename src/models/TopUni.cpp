#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <iomanip>
#include <typeinfo>

using namespace std;

struct TopTenUniNode {
	string UniId;
	string UniName;
	int Count = 1;

	TopTenUniNode* NextAddress;
	TopTenUniNode* PrevAddress;

} *TopTenUniHead, *TopTenUniTail;

