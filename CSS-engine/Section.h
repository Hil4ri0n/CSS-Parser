#pragma once
#include "String.h"
#include "Attribute.h"
#include "DL_List.h"
using namespace std;

class Section {
public:
	DL_List <String>* selectors;
	DL_List <Attribute>* attributes;

	Section();
	~Section();
};