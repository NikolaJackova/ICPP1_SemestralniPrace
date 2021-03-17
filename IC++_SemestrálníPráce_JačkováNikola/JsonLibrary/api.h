#pragma once
#ifndef API_H
#define API_H

#include <string>
#include "platform.h"

// - �ablona s parametrem datov�ho typu ulo�en�ch hodnot
// - nen� povoleno u�it� STL kontejner� ani jin�ch knihoven pro ukl�d�n� dat
// - realizace mus� vyu��vat dynamicky alokovan� pole, spojov� seznam nebo jinou vhodnou V�mi implementovanou ADS 
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

	// - p�id� element na konec pole
	void append(const T& element);

	// - v�jimky p�i neplatn�m nebo nekorektn�m indexu
	const T& getElementAt(int index) const;

	// - vrac� velikost (po�et prvk�) v poli
	int getSize() const;
};

///////////////////////////////////////////////////////////////////////////////

// JSON hodnota - reprezentuje abstraktn�ho p�edka pro z�kladn� datov� typy v JSON (string, number, object, array, bool, null)
class DLL_SPEC Value
{
public:
	// serializuje hodnotu do podoby JSON reprezentace
	virtual std::string serialize() const = 0;
	virtual ~Value();
};

///////////////////////////////////////////////////////////////////////////////

// - definuje p�r kl�� (�et�zec) a hodnota (JSON hodnota) pro reprezentaci hodnot JSON objektu
class DLL_SPEC KeyValuePair {
	std::string key;
	Value* value;
public:
	KeyValuePair();
	KeyValuePair(std::string key, Value* value);
	virtual ~KeyValuePair();
	// - vr�t� kl��
	std::string getKey() const;
	// - vr�t� hodnotu
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
	// - vrac� bool hodnotu
	bool get() const;
	void set(bool value);
	virtual std::string serialize() const override;
};

///////////////////////////////////////////////////////////////////////////////

// - reprezentuje hodnotu typu JSON ��slo
class DLL_SPEC NumberValue :
	public Value
{
	double value;
public:
	NumberValue(double value);
	virtual ~NumberValue();
	// - vrac� ��selnou hodnotu 
	double get() const;
	void set(double value);
	virtual std::string serialize() const override;
};

///////////////////////////////////////////////////////////////////////////////

// - reprezentuje hodnotu typu JSON �et�zec (string)
class DLL_SPEC StringValue :
	public Value
{
	std::string value;
public:
	StringValue(std::string value);
	virtual ~StringValue();
	// - vrac� �et�zcovou hodnotu
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
	// - p�id� element na konec pole
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
	// - p�id� kl��-element do objektu
	void append(const KeyValuePair& pair);
	virtual std::string serialize() const override;
	DynamicArray<KeyValuePair>& getArray();
private:
	DynamicArray<KeyValuePair> objectArray;
};

///////////////////////////////////////////////////////////////////////////////

// - t��da pro pr�ci s JSON
class DLL_SPEC JSON
{
public:
	// - provede deserializaci �et�zce na vytvo�en� objekty
	// - p�e�tu znak a rozhodnu se
	// -- '{' - za��n�m ��st objekt
	// -------- �tu znaky, pak mus� b�t dvojte�ka, potom vol�m rekurzivn� deserialize(); n�sleduje ��rka nebo '}', podle situace se �ten� opakuje
	// -- '[' - za��n�m ��st pole
	// -------- vol�m rekurzivn� deserialize(); n�sleduje ��rka nebo ']', podle situace se �ten� opakuje
	// -- '"' - za��n�m ��st �et�zec - pozor na escapovan� uvozovky
	// -- [-0123456789] - za��n�m ��st ��slo - na�tu v�echny ��slice (pozor na mo�nou desetinnou te�ku)
	// -- 'n' - 'null'
	// -- 't' - 'true'
	// -- 'f' - 'false'
	// -- cokoliv jin�ho - vyvol�v�m v�jimku
	// - nen� p��pustn� vracet nullptr
	// - deserializace mus� b�t rozumn� implementov�na - nen� p��pustn� zde napsat jednu extr�mn� dlouhou metodu
	static Value* deserialize(const std::string& string);
	
	// - provede serializaci do JSON �et�zce
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

