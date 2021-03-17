#pragma once
#ifndef PREDMET_H
#define PREDMET_H

#include <string>
#include <iostream>
class Predmet
{
private:
	std::string nazev;
public:
	Predmet(std::string nazev) { this->nazev = nazev; };
	Predmet() { nazev = "Nema nazev"; };
	std::string getNazev() { return nazev; };
	void setNazev(std::string nazev) { this->nazev = nazev; };
	std::string toString() { return nazev; };
};
#endif // !

