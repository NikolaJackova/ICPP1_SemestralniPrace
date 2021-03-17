#pragma once
#ifndef API_H
#define API_H

#include <string>
#include "platform.h"

// - šablona s parametrem datového typu uložených hodnot
// - není povoleno užití STL kontejnerù ani jiných knihoven pro ukládání dat
// - realizace musí využívat dynamicky alokované pole, spojový seznam nebo jinou vhodnou Vámi implementovanou ADS 
template<typename T>
class DLL_SPEC DynamicArray {
	T* _array;
	int size;
	int  numberOfElements;
	void growArray();
	bool isFreeSpace();
	int getSizeOfArray() const;
public:
	DynamicArray();
	~DynamicArray();

	// - pøidá element na konec pole
	void append(const T& element);

	// - výjimky pøi neplatném nebo nekorektním indexu
	const T& getElementAt(int index) const;

	// - vrací velikost (poèet prvkù) v poli
	int getSize() const;
};

///////////////////////////////////////////////////////////////////////////////

// JSON hodnota - reprezentuje abstraktního pøedka pro základní datové typy v JSON (string, number, object, array, bool, null)
class DLL_SPEC Value
{
public:
	// serializuje hodnotu do podoby JSON reprezentace
	virtual std::string serialize() const = 0;
	virtual ~Value();
};

///////////////////////////////////////////////////////////////////////////////

// - definuje pár klíè (øetìzec) a hodnota (JSON hodnota) pro reprezentaci hodnot JSON objektu
class DLL_SPEC KeyValuePair {
	std::string key;
	Value* value;
public:
	KeyValuePair();
	KeyValuePair(std::string key, Value* value);
	virtual ~KeyValuePair();
	// - vrátí klíè
	std::string getKey() const;
	// - vrátí hodnotu
	Value* getValue() const;
};

///////////////////////////////////////////////////////////////////////////////

// - reprezentuje hodnotu typu JSON null
class DLL_SPEC NullValue :
	public Value
{
public:
	virtual ~NullValue();
	virtual std::string serialize() const override;
};

///////////////////////////////////////////////////////////////////////////////

// - reprezentuje hodnotu typu JSON bool
class DLL_SPEC BoolValue :
	public Value
{
	bool value;
public:
	BoolValue(bool value);
	virtual ~BoolValue();
	// - vrací bool hodnotu
	bool get() const;
	void set(bool value);
	virtual std::string serialize() const override;
};

///////////////////////////////////////////////////////////////////////////////

// - reprezentuje hodnotu typu JSON èíslo
class DLL_SPEC NumberValue :
	public Value
{
	double value;
public:
	NumberValue(double value);
	virtual ~NumberValue();
	// - vrací èíselnou hodnotu 
	double get() const;
	void set(double value);
	virtual std::string serialize() const override;
};

///////////////////////////////////////////////////////////////////////////////

// - reprezentuje hodnotu typu JSON øetìzec (string)
class DLL_SPEC StringValue :
	public Value
{
	std::string value;
public:
	StringValue(std::string value);
	virtual ~StringValue();
	// - vrací øetìzcovou hodnotu
	std::string get() const;
	void set(std::string);
	virtual std::string serialize() const override;
};

///////////////////////////////////////////////////////////////////////////////

// - reprezentuje hodnotu typu JSON pole
class DLL_SPEC ArrayValue :
	public Value
{
	DynamicArray<Value*> _array;
public:
	virtual ~ArrayValue();
	// - pøidá element na konec pole
	void append(Value* element);
	virtual std::string serialize() const override;
	DynamicArray<Value*>& getArray();
};

///////////////////////////////////////////////////////////////////////////////

// - reprezentuje hodnotu typu JSON objekt
class DLL_SPEC ObjectValue :
	public Value
{
public:
	virtual ~ObjectValue();
	// - pøidá klíè-element do objektu
	void append(const KeyValuePair& pair);
	virtual std::string serialize() const override;
	DynamicArray<KeyValuePair>& getArray();
private:
	DynamicArray<KeyValuePair> objectArray;
};

///////////////////////////////////////////////////////////////////////////////

// - tøída pro práci s JSON
class DLL_SPEC JSON
{
public:
	// - provede deserializaci øetìzce na vytvoøené objekty
	// - pøeètu znak a rozhodnu se
	// -- '{' - zaèínám èíst objekt
	// -------- ètu znaky, pak musí být dvojteèka, potom volám rekurzivnì deserialize(); následuje èárka nebo '}', podle situace se ètení opakuje
	// -- '[' - zaèínám èíst pole
	// -------- volám rekurzivnì deserialize(); následuje èárka nebo ']', podle situace se ètení opakuje
	// -- '"' - zaèínám èíst øetìzec - pozor na escapované uvozovky
	// -- [-0123456789] - zaèínám èíst èíslo - naètu všechny èíslice (pozor na možnou desetinnou teèku)
	// -- 'n' - 'null'
	// -- 't' - 'true'
	// -- 'f' - 'false'
	// -- cokoliv jiného - vyvolávám výjimku
	// - není pøípustné vracet nullptr
	// - deserializace musí být rozumnì implementována - není pøípustné zde napsat jednu extrémnì dlouhou metodu
	static Value* deserialize(const std::string& string);
	
	// - provede serializaci do JSON øetìzce
	static std::string serialize(const Value* value);

	static std::string loadJSON(std::string nazevSouboru);
	static void saveJSON(std::string str);
private:
	static Value* deserialize(const std::string& str, int& pointer);
	static NullValue* makeNull(const std::string& str, int& pointer);
	static BoolValue* makeBool(const std::string& str, int& pointer, bool value);
	static NumberValue* makeNumber(const std::string& str, int& pointer);
	static StringValue* makeString(const std::string& str, int& pointer);
};
///////////////////////////////////////////////////////////////////////////////

class DLL_SPEC FuntionsUtil {
public:
	static void replaceAll(std::string& str, const std::string& from, const std::string& to);
	static void deleteObj(ObjectValue* obj);
	static void deleteArr(ArrayValue* arr);
};
#endif // !API_H
///////////////////////////////////////////////////////////////////////////////

