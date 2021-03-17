#include "api.h"
#include <iostream>
#include <fstream>
#include <ostream>

using namespace std;
///////////////////////////////////////////////////////////////////////////////

//Dynamic Array methods
template<typename T>
void DynamicArray<T>::growArray()
{
	int newSize = size * 2;
	T* temp = new T[newSize];
	for (int i = 0; i < size; i++)
	{
		temp[i] = _array[i];
	}
	delete[] _array;
	_array = temp;
	size = newSize;
}

template<typename T>
bool DynamicArray<T>::isFreeSpace()
{
	return numberOfElements < size;
}

template<typename T>
int DynamicArray<T>::getSizeOfArray() const
{
	return size;
}

template<typename T>
DynamicArray<T>::DynamicArray() {
	_array = new T[10];
	size = 10;
	numberOfElements = 0;
}

template<typename T>
DynamicArray<T>::~DynamicArray() {
	delete[] _array;
}

template<typename T>
void DynamicArray<T>::append(const T& element)
{
	if (&element == nullptr) {
		throw invalid_argument("Element is null!");
	}
	if (!isFreeSpace()) {
		growArray();
	}
	_array[numberOfElements++] = element;
}

template<typename T>
const T& DynamicArray<T>::getElementAt(int index) const
{
	if (index < 0 || index >= numberOfElements) {
		throw out_of_range("Invalid index!");
	}
	return _array[index];
}

template<typename T>
int DynamicArray<T>::getSize() const
{
	return numberOfElements;
}

///////////////////////////////////////////////////////////////////////////////
//BoolValue methods

BoolValue::BoolValue(bool value) :value(value) {}

BoolValue::~BoolValue()
{
}

bool BoolValue::get() const
{
	return value;
}

void BoolValue::set(bool value)
{
	this->value = value;
}

string BoolValue::serialize() const
{
	if (value == true) {
		return "true";
	}
	return "false";
}
///////////////////////////////////////////////////////////////////////////////
//NullValue methods

NullValue::~NullValue()
{
}

string NullValue::serialize() const
{
	return "null";
}
///////////////////////////////////////////////////////////////////////////////
//NumberValue methods

NumberValue::NumberValue(double value) :value(value) {}

NumberValue::~NumberValue()
{
}

double NumberValue::get() const
{
	return value;
}

void NumberValue::set(double value)
{
	this->value = value;
}

string NumberValue::serialize() const
{
	if (floor(value) == value)
		return to_string(static_cast<int>(value));
	else
		return to_string(value);
}
///////////////////////////////////////////////////////////////////////////////
//StringValue methods

StringValue::StringValue(std::string value) :value(value) {}

StringValue::~StringValue()
{
}

std::string StringValue::get() const
{
	return value;
}

void StringValue::set(std::string)
{
	this->value = value;
}

string StringValue::serialize() const
{
	string s = value;
	FuntionsUtil::replaceAll(s, "\"", "\\\"");
	return "\"" + s + "\"";
}
///////////////////////////////////////////////////////////////////////////////
//ArrayValue methods

ArrayValue::~ArrayValue()
{
}

void ArrayValue::append(Value* element)
{
	if (element == nullptr) {
		throw invalid_argument("Element is null!");
	}
	_array.append(element);
}

string ArrayValue::serialize() const
{
	string s = "[";
	for (int i = 0; i < _array.getSize(); i++)
	{
		s += _array.getElementAt(i)->serialize() + ",";
		if (i + 1 == _array.getSize()) {
			s.erase(s.size() - 1);
		}
	}
	s += "]";
	return s;
}
DynamicArray<Value*>& ArrayValue::getArray()
{
	return _array;
}
///////////////////////////////////////////////////////////////////////////////
//ObjectValue methods

ObjectValue::~ObjectValue()
{
}

void ObjectValue::append(const KeyValuePair& pair)
{
	objectArray.append(pair);
}

string ObjectValue::serialize() const
{
	string s = "{";
	for (int i = 0; i < objectArray.getSize(); i++)
	{
		s += "\"" + objectArray.getElementAt(i).getKey() + "\"" + ":" + objectArray.getElementAt(i).getValue()->serialize() + ",";
		if (i + 1 == objectArray.getSize()) {
			s.erase(prev(s.end()));
		}
	}
	s += "}";
	return s;
}

DynamicArray<KeyValuePair>& ObjectValue::getArray()
{
	return objectArray;
}

Value::~Value()
{
}

KeyValuePair::KeyValuePair()
{
	value = nullptr;
}

KeyValuePair::KeyValuePair(std::string key, Value* value)
{
	this->key = key; this->value = value;
}

KeyValuePair::~KeyValuePair()
{
}

std::string KeyValuePair::getKey() const
{
	return key;
}

Value* KeyValuePair::getValue() const
{
	return value;
}
