#include <iostream>
#include "Section.h"
using namespace std;

Section::Section() {
	selectors = new DL_List <String>;
	attributes = new DL_List <Attribute>;
}

Section::~Section() {
	delete selectors;
	selectors = nullptr;
	delete attributes;
	attributes = nullptr;
}