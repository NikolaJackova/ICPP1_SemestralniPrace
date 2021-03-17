#pragma once
#ifndef CONTAINER_H
#define CONTAINER_H
#include <iostream>

#define SIZE 25

template<typename DateType>
struct Array {
private:
	DateType* _array;
	unsigned _sizeOfArray;
	unsigned _numberOfElements;
	void growArray();
public:
	Array();
	~Array();
	bool isFreeSpace() const;
	void add(const DateType& o);
	DateType& operator[](int index);
	DateType operator[](int index) const;
	unsigned int count() const;
	void remove(int index);
	unsigned getSize() const { return _sizeOfArray; };
	unsigned getNumber() const { return _numberOfElements; };
	DateType* getArray() const { return _array; };
};

template<typename DateType>
Array<DateType>::Array() {
	_array = new DateType[SIZE];
	_sizeOfArray = SIZE;
	_numberOfElements = 0;
}

template<typename DateType>
Array<DateType>::~Array() {
	delete[] _array;
}

template<typename DateType>
bool Array<DateType>::isFreeSpace() const {
	return _numberOfElements < _sizeOfArray;
}

template<typename DateType>
void Array<DateType>::growArray()
{
	int size = _sizeOfArray*2;
	DateType* temp = new DateType[size];
	for (int i = 0; i < _sizeOfArray; i++)
	{
		temp[i] = _array[i];
	}
	delete[] _array;
	_array = temp;
	_sizeOfArray = size;
}

template<typename DateType>
void Array<DateType>::add(const DateType& o)
{
	if (&o == nullptr) {
		throw std::invalid_argument("Object is null!");
	}
	if (!isFreeSpace()) {
		growArray();
	}
	_array[_numberOfElements++] = o;
}

template<typename DateType>
DateType& Array<DateType>::operator[](int index)
{
	if (index >= _numberOfElements || index < 0) {
		throw std::out_of_range("Invalid index!");
	}
	return _array[index];
}

template<typename DateType>
DateType Array<DateType>::operator[](int index) const
{
	if (index >= _numberOfElements || index < 0) {
		throw std::invalid_argument("Invalid index!");
	}
	return _array[index];
}

template<typename DateType>
unsigned int Array<DateType>::count() const
{
	return _numberOfElements;
}

template<typename DateType>
void Array<DateType>::remove(int index)
{
	if (index >= _numberOfElements || index < 0) {
		throw std::invalid_argument("Invalid index!");
	}
	for (int i = index + 1; i < _numberOfElements; i++)
	{
		_array[i - 1] = _array[i];
	}
	_numberOfElements--;
}
#endif
