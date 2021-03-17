#pragma once

#ifndef CRUD_H
#define CRUD_H

#include <string>
#include "Student.h"
#include "Predmet.h"
#include "api.h"
#include "Container.h"

class CRUD {
public:
	static void zobrazMenu();
	static void upravStudenta(Array<Student>& studenti, Array<Predmet>& predmety);
	static void upravPredmet(Array<Predmet>& predmety);
	static Student* vytvorStudenta(Array<Predmet>* predmety);
	static Predmet* vytvorPredmet();
	static void zobrazStudenty(Array<Student>* studenti);
	static void zobrazPredmety(Array<Predmet>* predmety);
	static Value* nactiZeSouboru();
	static void nacti(Array<Predmet>* predmety, Array<Student>* studenti, ArrayValue* poleSt);
	static void ulozDoSouboru(Array<Student>& poleS);
	static void smazStudenta(Array<Student>& studenti);
	static void smazPredmet(Array<Predmet>& predmety, Array<Student>& studenti);
private:
	static void upravPredmet(Predmet& predmet);
	static void upravStudenta(Student& student, Array<Predmet>& predmety);
};
#endif // !CRUD_H
