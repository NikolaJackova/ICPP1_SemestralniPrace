#include "api.h"
#include <iostream>
#include <fstream>
#include <ostream>

using namespace std;
///////////////////////////////////////////////////////////////////////////////
//funkce pro JSON tridu
///////////////////////////////////////////////////////////////////////////////

//public
Value* JSON::deserialize(const string& str)
{
	int pointer = 0;
	return JSON::deserialize(str, pointer);
}

string JSON::serialize(const Value* value)
{
	return value->serialize();
}

string JSON::loadJSON(string nazevSouboru)
{
	ifstream is{};
	is.open(nazevSouboru);
	string line;
	if (is.is_open()) {
		getline(is, line);
	}
	else {
		throw exception("Soubor nebyl otevøen!");
	}
	is.close();
	return line;
}
///////////////////////////////////////////////////////////////////////////////

//private
Value* JSON::deserialize(const string& str, int& pointer)
{
	if (pointer > str.length()) {
		throw out_of_range("Pointer je vyssi cislo nez delka stringu!");
	}
	char x = str.at(pointer);
	if (x == '{') {
		ObjectValue* ov = new ObjectValue{};
		if (str.at(pointer+1) == '}') {
			//presun ukazatele na oddelovac
			pointer++;
			return ov;
		}
		while (str.at(pointer) != '}')
		{
			string key = "";
			StringValue* strKey = makeString(str, ++pointer);
			key = strKey->get();
			delete strKey;
			//presun ukazatele pres uvozovku a dvojtecku
			pointer++;
			pointer++;
			ov->append(KeyValuePair(key, deserialize(str, pointer)));
			//po pridani prvku do objektu, presun ukazatele na oddelovac
			pointer++;
		}
		return ov;
	}
	else if (x == '[') {
		ArrayValue* av = new ArrayValue{};
		if (str.at(pointer + 1) == ']') {
			//presun ukazatele na oddelovac
			pointer++;
			return av;
		}
		while (str.at(pointer) != ']') {
			//po overeni oddelovace, presun na nasledujici paltny znak
			pointer++;
			av->append(deserialize(str, pointer));
			//po pridani prvku do pole, presun ukazatele na oddelovac
			pointer++;
		}
		return av;
	}
	else if (x == '"') {
		return makeString(str, pointer);
	}
	else if (x == 't') {
		return makeBool(str, pointer, true);
	}
	else if (x == 'f') {
		return makeBool(str, pointer, false);
	}
	else if (x == 'n') {
		return makeNull(str, pointer);
	}
	else if (isdigit(x) || x == '-') {
		return makeNumber(str, pointer);
	}
	else {
		throw exception("Neplatny znak!");
	}
}

NullValue* JSON::makeNull(const string& str, int& pointer) {
	string nullStr = "";
	nullStr += str.at(pointer);
	char nextChar = str.at(pointer + 1);
	while (nextChar != ',' && nextChar != ']' && nextChar != '}' && pointer + 1 < str.size()) {
		nullStr += str.at(++pointer);
		nextChar = str.at(pointer + 1);
	}
	if (nullStr == "null" || nullStr == "n") {
		return new NullValue{};
	}
	else {
		throw exception("Neplatna hodnota null!");
	}
}

BoolValue* JSON::makeBool(const string& str, int& pointer, bool value)
{
	string boolStr = "";
	boolStr += str.at(pointer);
	char nextChar = str.at(pointer + 1);
	while (nextChar != ',' && nextChar != ']' && nextChar != '}' && pointer + 1 < str.size()) {
		boolStr += str.at(++pointer);
		nextChar = str.at(pointer + 1);
	}
	if (boolStr == "true" || boolStr == "t" || boolStr == "false" || boolStr == "f") {
		return new BoolValue{ value };
	}
	else {
		throw exception("Neplatna hodnota bool!");
	}
}

NumberValue* JSON::makeNumber(const string& str, int& pointer)
{
	string numberStr = "";
	numberStr += str.at(pointer);
	char nextChar = str.at(pointer + 1);
	while (nextChar != ',' && nextChar != ']' && nextChar != '}' && pointer + 1 < str.size()) {
		if (!isdigit(str.at(pointer)) && !(str.at(pointer) == '.') && !(str.at(pointer) == '-')) {
			throw exception("Retezec neobsahuje pouze cisla!");
		}
		numberStr += str.at(++pointer);
		nextChar = str.at(pointer + 1);
	}
	return new NumberValue{ stod(numberStr) };
}

StringValue* JSON::makeString(const string& str, int& pointer)
{
	string stringStr = "";
	stringStr += str.at(++pointer);
	char nextChar = str.at(pointer + 1);
	char nextNextChar = str.at(pointer + 2);
	while (!(nextChar == '\"' && str.at(pointer) != '\\' && (nextNextChar == ':' || nextNextChar == ',' || nextNextChar == ']' || nextNextChar == '}' || pointer + 1 < str.size())) && pointer + 1 < str.size()) {
		stringStr += str.at(++pointer);
		nextChar = str.at(pointer + 1);
		if (pointer + 2 < str.size()) {
			nextNextChar = str.at(pointer + 2);
		}
	}
	//presun ukazatele na zaviraci uvozovku
	pointer++;
	FuntionsUtil::replaceAll(stringStr, "\\\"", "\"");
	return new StringValue{stringStr};
}

void JSON::saveJSON(string str)
{
	ofstream file{};
	file.open("serialized.json");
	file << str << endl;
	file.close();
}
