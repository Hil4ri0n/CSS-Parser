#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include "String.h"
#include "string.h"
#include "DL_List.h"
#include "Block_List.h"
#include "Attribute.h"
#include "Section.h"
#include "Iterator.h"
#include "Block_Iterator.h"
using namespace std;
String* cutName(String& text);
void parseCSS(String& text, Section* sekcja, bool& czyBlok, bool& nowaSekcja);
void commandController(Block_List<Section*>& css, String first, String second, String third);
void insertAttribute(DL_List <Attribute>& list, Attribute& attribute);
void insertSelector(DL_List <String>* list, String& selector);

void numOfSec(Block_List <Section*>& css) {
    int numberOfSections = css.getSize();
    cout << "? == " << numberOfSections << endl;
}

void numOfSelectors(Block_List <Section*>& css, int sectionNumber) {
    if (css.getElement(sectionNumber) == nullptr) return;
    else {
        cout << sectionNumber << ",S,? == " << (*css.getElement(sectionNumber))->selectors->getSize() << endl;
    }
}

void numOfAttributes(Block_List <Section*>& css, int sectionNumber) {
    if (css.getElement(sectionNumber) == nullptr) return;
    else {
        cout << sectionNumber << ",A,? == " << (*css.getElement(sectionNumber))->attributes->getSize() << endl;
    }
}

void getSelector(Block_List <Section*>& css, int sectionNumber, int selectorNumber) {
    if (css.getElement(sectionNumber) == nullptr) return;
    else {
        if ((*css.getElement(sectionNumber))->selectors->getSize() < selectorNumber) return;
        else {
            cout << sectionNumber << ",S," << selectorNumber << " == " << (*(*css.getElement(sectionNumber))->selectors->getElement(selectorNumber)) << endl;
        }
    }
}

void getAttributeValue(Block_List <Section*>& css, int sectionNumber, String& name) {
    if (css.getElement(sectionNumber) == nullptr) return;
    else {
        Iterator <Attribute> iterator((**css.getElement(sectionNumber)).attributes->begin());
        for (; iterator != (**css.getElement(sectionNumber)).attributes->end(); iterator++) {
            if ((*iterator).name == name) {
                cout << sectionNumber << ",A," << name << " == " << (*iterator).value << endl;
                break;
            }
        }
    }
}

void numOfOccursAttr(Block_List <Section*>& css, String& name) {
    int occurs = 0;
    Block_Iterator<Section*>BlockIterator(css.begin());
    for (; BlockIterator != css.end(); ++BlockIterator) {
        Iterator <Attribute> iterator = ((**BlockIterator).attributes)->begin();
        for (; iterator != ((**BlockIterator).attributes)->end(); iterator++) {
            if ((*iterator).name == name) occurs++;
        }
    }
    cout << name << ",A,? == " << occurs << endl;
}
void numOfOccursSel(Block_List <Section*>& css, String& name) {
    int occurs = 0;
    Block_Iterator<Section*>BlockIterator(css.begin());
    for (; BlockIterator != css.end(); ++BlockIterator) {
        Iterator <String> iterator = ((**BlockIterator).selectors)->begin();
        for (; iterator != ((**BlockIterator).selectors)->end(); iterator++) {
            if ((*iterator) == name) occurs++;
        }
    }
    cout << name << ",S,? == " << occurs << endl;
}

void getAttrValueSel(Block_List <Section*>& css, String& selector, String& attribute) {
    String attrValue = "";
    Block_Iterator<Section*>BlockIterator(css.begin());
    for (; BlockIterator != css.end(); ++BlockIterator) {
        Iterator <String> iterator = ((**BlockIterator).selectors)->begin();
        for (; iterator != ((**BlockIterator).selectors)->end(); iterator++) {
            if ((*iterator) == selector) {
                Iterator <Attribute> iterator_attr = ((**BlockIterator).attributes)->begin();
                for (; iterator_attr != ((**BlockIterator).attributes)->end(); iterator_attr++) {
                    if ((*iterator_attr).name == attribute) {
                        attrValue = (*iterator_attr).value;
                        break;
                    }
                }
                break;
            }
        }
    }
    if (attrValue != "") cout << selector << ",E," << attribute << " == " << attrValue << endl;
}

void deleteSection(Block_List <Section*>& css, int sectionNumber) {
    if (css.removeAt(sectionNumber)) {
        cout << sectionNumber << ",D,* == deleted" << endl;
    }
}

void deleteAttribute(Block_List <Section*>& css, int sectionNumber, String& name) {
    if (css.getElement(sectionNumber) == nullptr) return;
    Iterator <Attribute> iterator((**css.getElement(sectionNumber)).attributes->begin());
    for (; iterator != (**css.getElement(sectionNumber)).attributes->end(); iterator++) {
        if ((*iterator).name == name) {
            (**css.getElement(sectionNumber)).attributes->removeNode(iterator.getNode());
            if ((**css.getElement(sectionNumber)).attributes->getSize() == 0) {
                css.removeAt(sectionNumber);
            }
            cout << sectionNumber << ",D," << name << " == deleted" << endl;
            break;
        }
    }
}

int main()
{
    Block_List <Section*> css;
    bool czyBlok = false;
    bool nowaSekcja = false;
    String text;
    char input[100];

    int mode = 1;// 1 means reading input css/ 0 means reading commands and printing responces
    Section* sekcjaPtr = nullptr;
    while (fgets(input, 100, stdin)) {
        if (input[strlen(input) - 1] == '\n') {
            input[strcspn(input, "\n")] = '\0';
        }
        text = input;
        if (text == "****") {
            mode = 1;
            continue;
        }
        if (text == "????") {
            mode = 0;
            continue;
        }

        if (mode == 1) {
            if (sekcjaPtr == nullptr) {
                sekcjaPtr = new Section;
            }
            parseCSS(text, sekcjaPtr, czyBlok, nowaSekcja);
            if (nowaSekcja == true) {
                nowaSekcja = false;
                css.push_back(sekcjaPtr);
                sekcjaPtr = nullptr;
            }
        }

        if (mode == 0) {
            if (strlen(input) == 1) {
                if (input[0] == '?') numOfSec(css);
            }
            else {
                char* first = strtok(input, ",");
                char* second = strtok(NULL, ",");
                char* third = strtok(NULL, ",");
                if (first && second && third) {
                    String stringFirst(first);
                    String stringSecond(second);
                    String stringThird(third);
                    commandController(css, stringFirst, stringSecond, stringThird);
                }
            }
        }
    }

}
void cleanString(String& string) {
    int i = 0;
    while (string[i] <= ' ' || string[i] == '\t') {
        i++;
    }
    string = string.c_str() + i;
    i = string.size() - 1;
    while (i >= 0 && (string[i] <= ' ' || string[i] == '\t')) {
        string[i] = '\0';
        i--;
    }
}

void parseCSS(String& text, Section* sekcja, bool& czyBlok, bool& nowaSekcja) {
    if (text == "\t") return;
    if (text == "{") {
        czyBlok = true;
        return;
    }
    if (text == "}") {
        czyBlok = false;
        nowaSekcja = true;
        return;
    }
    char* napis = new char[strlen(text.c_str()) + 1];
    strcpy(napis, text.c_str());
    char* kopia = new char[strlen(napis) + 1];
    strcpy(kopia, napis);
    char* endBracketPtr = strchr(napis, '}');
    if (endBracketPtr != NULL) {
        nowaSekcja = true;
    }
    char* selectorPtr = strtok(napis, "{");
    char* attributePtr = strtok(NULL, "{");
    if (selectorPtr != NULL && czyBlok == false) {
        char* token;
        token = strtok(selectorPtr, ",");
        String string(token);
        cleanString(string);
        insertSelector(sekcja->selectors, string);
        while (token != NULL) {
            token = strtok(NULL, ",");
            if (token != NULL) {
                String string(token);
                cleanString(string);
                insertSelector(sekcja->selectors, string);
            }
        }
        if (strchr(kopia, '{') && (strchr(kopia, '}') == NULL)) {
            czyBlok = true;
            delete[] napis;
            delete[] kopia;
            return;
        }
    }
    if (czyBlok == true) attributePtr = selectorPtr;
    if (attributePtr != NULL) {
        char* token = strtok(attributePtr, ";");
        while (token != NULL) {
            char* name = strtok(attributePtr, ":");
            char* value = strtok(NULL, ":");
            if (name != NULL && value != NULL) {
                Attribute attribute;
                attribute.name = name;
                attribute.value = value;
                cleanString(attribute.name);
                cleanString(attribute.value);
                insertAttribute(*(*sekcja).attributes, attribute);
            }
            token = strtok(NULL, ";");
        }
    }
    if (strchr(kopia, '}')) {
        czyBlok = false;
        nowaSekcja = true;
    }
    delete[] napis;
    delete[] kopia;
}

void insertAttribute(DL_List <Attribute>& list, Attribute& attribute) {
    bool isAttribute = false;
    Iterator <Attribute> iterator(list.begin());
    for (; iterator != list.end(); iterator++) {
        if ((*iterator).name == attribute.name) {
            isAttribute = true;
            (*iterator).value = attribute.value;
            break;
        }
    }
    if (!isAttribute) {
        list.push_back(attribute);
    }
}

void insertSelector(DL_List <String>* list, String& selector) {
    bool isSelector = false;
    Iterator <String> iterator (list->begin());
    for (; iterator != list->end(); iterator++) {
        if ((*iterator) == selector) {
            isSelector = true;
            break;
        }
    }
    if (!isSelector) {
        list->push_back(selector);
    }
    if (list->getSize() >= 2) {
        int x;
        x = 1;
    }
}

String* cutName(String& text) {
    const char* firstComma = strchr(text.c_str(), ',');
    int difference = firstComma - text.c_str();
    char* buffer = new char[difference + 1];
    for (int i = 0; i < difference; i++) {
        buffer[i] = text.c_str()[i];
    }
    buffer[difference] = '\0';
    String* pointer = new String(buffer);
    return pointer;
}

void commandController(Block_List<Section*>& css, String first, String second, String third) {
    if (second == "S") {
        if (first[0] > '0' && first[0] <= '9') {
            if (third[0] > '0' && third[0] <= '9') {
                getSelector(css, first.to_int(), third.to_int());
            }
            else {
                if (third == "?") {
                    numOfSelectors(css, first.to_int());
                }
            }
        }
        else {
            if (third == "?") {
                numOfOccursSel(css, first);
            }
        }
    }
    else if (second == "A") {
        if (first[0] > '0' && first[0] <= '9') {
            if (third == "?") {
                numOfAttributes(css, first.to_int());
            }
            else {
                getAttributeValue(css, first.to_int(), third);
            }
        }
        else {
            if (third == "?") {
                numOfOccursAttr(css, first);
            }
        }
    }
    else if (second == "E") {
        getAttrValueSel(css, first, third);
    }
    else if (second == "D") {
        if (first[0] > '0' && first[0] <= '9') {
            if (third == "*") {
                deleteSection(css, first.to_int());
            }
            else {
                deleteAttribute(css, first.to_int(), third);
            }
        }
    }
}
