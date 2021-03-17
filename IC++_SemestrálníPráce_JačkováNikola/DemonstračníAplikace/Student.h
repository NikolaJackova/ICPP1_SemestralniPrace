#pragma once
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <iostream>
#include "Predmet.h"

class Student
{
private:
	int id;
	std::string jmeno;
	Predmet* oblibeny;
	bool studuje;
public:
	Student(int id, std::string jmeno, Predmet* oblibeny, bool studuje) : id(id), jmeno(jmeno), oblibeny(oblibeny), studuje(studuje) {};
	Student() { oblibeny = nullptr; };
	~Student() { /*delete oblibeny;*/ };
	std::string getJmeno() { return jmeno; };
	bool getStuduje() { return studuje; };
	int getId() { return id; };
	void setJmeno(std::string jmeno) { this->jmeno = jmeno; };
	void setId(int id) { this->id = id; };
	void setStuduje(bool studuje) { this->studuje = studuje; };
	void setPredmet(Predmet* oblibeny) { this->oblibeny = oblibeny; };
	Predmet* getPredmet() { return oblibeny; };
	std::string toString() { 
		std::string studujeStr = "nestuduje";
		if (studuje)
			studujeStr = "studuje";
		std::string predmet = "nema oblibeny";
		if (oblibeny != nullptr)
			predmet = oblibeny->getNazev();
		return std::to_string(id) + ", " + jmeno + ", " + predmet + ", " + studujeStr; };
};
#endif // !

