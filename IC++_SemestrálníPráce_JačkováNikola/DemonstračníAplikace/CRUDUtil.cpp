#include "CRUDUtil.h"
#include <iostream>

using namespace std;
void CRUD::zobrazMenu()
{
    cout << "--------------MENU---------------" << endl;
    cout << "1) Vytvor studenta\n";
    cout << "2) Uprav studenta\n";
    cout << "3) Smaz studenta\n";
    cout << "4) Vytvor predmet\n";
    cout << "5) Uprav predmet\n";
    cout << "6) Smaz predmet\n";
    cout << "7) Zobraz studenty\n";
    cout << "8) Zobraz predmety\n";
    cout << "9) Nacist JSON\n";
    cout << "10) Ulozit JSON\n";
    cout << "11) Zobraz menu\n";
    cout << "0) Ukoncit\n";
}

void CRUD::upravStudenta(Student& student, Array<Predmet>& predmety)
{
    cout << "Chcete upravit id? (1/0): ";
    int volba;
    cin >> volba;
    if (volba != 0) {
        cout << "Zadej id: ";
        int id = 0;
        cin >> id;
        student.setId(id);
    }
    cout << "Chcete upravit jmeno? (1/0): ";
    cin >> volba;
    if (volba != 0) {
        cout << "Zadej jmeno: ";
        string jmeno = "";
        cin >> jmeno;
        student.setJmeno(jmeno);
    }
    cout << "Chcete upravit stav studovani? (1/0): ";
    cin >> volba;
    if (volba != 0) {
        bool st;
        cout << "Studuje? (1/0): ";
        cin >> st;
    }
    cout << "Chcete upravit predmet? (1/0): ";
    cin >> volba;
    if (volba != 0) {
        zobrazPredmety(&predmety);
        int index = 0;
        cout << "Predmet na indexu: ";
        cin >> index;
        student.setPredmet(&predmety[index]);
    }
}

void CRUD::upravStudenta(Array<Student>& studenti, Array<Predmet>& predmety)
{
    zobrazStudenty(&studenti);
    cout << "Zadej index studenta (max " << studenti.count() - 1 << "): ";
    int index;
    cin >> index;
    upravStudenta(studenti[index], predmety);
}

void CRUD::upravPredmet(Array<Predmet>& predmety)
{
    zobrazPredmety(&predmety);
    cout << "Zadej index predmetu (max " << predmety.count() - 1 << "): ";
    int index;
    cin >> index;
    upravPredmet(predmety[index]);
}

void CRUD::upravPredmet(Predmet& predmet)
{
    cout << "Pro nezmìnìní atributu zvolte 0" << endl;
    cout << "Zadej jmeno: ";
    string jmeno = "";
    cin >> jmeno;
    if (jmeno != "0") {
        predmet.setNazev(jmeno);
    }
}

Student* CRUD::vytvorStudenta(Array<Predmet>* predmety)
{
    cout << "Zadej id: ";
    int id = 0;
    cin >> id;
    cout << "Zadej jmeno: ";
    string jmeno = "";
    cin >> jmeno;
    bool st;
    cout << "Studuje? (1/0): ";
    cin >> st;
    int index = 0;
    cout << "Predmet na indexu: ";
    cin >> index;
    try
    {
        Student* student = new Student(id,jmeno,&predmety->operator[](index), st );
        return student;
    }
    catch (const std::exception& e)
    {
        cerr << e.what();
    }
}

Predmet* CRUD::vytvorPredmet()
{
    cout << "Zadej nazev: ";
    string nazev = "";
    cin >> nazev;
    Predmet* predmet = new Predmet(nazev);
    return predmet;
}

void CRUD::zobrazStudenty(Array<Student>* studenti)
{
    if (studenti->count() == 0) {
        cout << "Zadni studenti" << endl;
        return;
    }
    for (size_t i = 0; i < studenti->count(); i++)
    {
        cout << i << ": " << studenti->operator[](i).toString() << endl;
    }
}

void CRUD::zobrazPredmety(Array<Predmet>* predmety)
{
    if (predmety->count() == 0) {
        cout << "Zadne predmety" << endl;
        return;
    }
    for (size_t i = 0; i < predmety->count(); i++)
    {
        cout << i << ": " << predmety->operator[](i).toString() << endl;
    }
}

Value* CRUD::nactiZeSouboru()
{
    string nazev = "";
    cout << "Nazev (serialized.json): ";
    cin >> nazev;
    try
    {
        string file = JSON::loadJSON(nazev);
        Value* serialized = JSON::deserialize(file);
        cout << serialized->serialize() << endl << endl;
        return serialized;
    }
    catch (const std::exception& e)
    {
        cerr << e.what();
    }
}

void CRUD::nacti(Array<Predmet>* predmety, Array<Student>* studenti, ArrayValue* poleSt) {
    DynamicArray<Value*>& pole = poleSt->getArray();
    for (size_t i = 0; i < pole.getSize(); i++)
    {
        ObjectValue* student = (ObjectValue*)pole.getElementAt(i);
        DynamicArray<KeyValuePair>& poleStudenta = student->getArray();
        Student* st = new Student();
        st->setId(dynamic_cast<NumberValue*>(poleStudenta.getElementAt(0).getValue())->get());
        st->setJmeno(dynamic_cast<StringValue*>(poleStudenta.getElementAt(1).getValue())->get());
        st->setStuduje(dynamic_cast<BoolValue*>(poleStudenta.getElementAt(3).getValue())->get());

        string nazevPredmetu = "";
        if (dynamic_cast<StringValue*>(dynamic_cast<ObjectValue*>(poleStudenta.getElementAt(2).getValue())->getArray().getElementAt(0).getValue()) != nullptr) {
            nazevPredmetu = (dynamic_cast<StringValue*>(dynamic_cast<ObjectValue*>(poleStudenta.getElementAt(2).getValue())->getArray().getElementAt(0).getValue())->get());
        }
        else {
            st->setPredmet(nullptr);
        }
        if (nazevPredmetu != "") {
            bool existuje = false;
            for (size_t i = 0; i < predmety->count(); i++)
            {
                if (predmety->operator[](i).getNazev() == nazevPredmetu) {
                    existuje = true;
                    break;
                }
            }
            if (!existuje) {
                Predmet* pr = new Predmet(nazevPredmetu);
                predmety->add(*pr);
                delete pr;
            }
                for (size_t i = 0; i < predmety->count(); i++)
                {
                    if (predmety->operator[](i).getNazev() == nazevPredmetu) {
                        st->setPredmet(&predmety->operator[](i));
                    }
                }
        }
        studenti->add(*st);
        delete st;
    }
}

void CRUD::ulozDoSouboru(Array<Student>& poleS)
{
    ArrayValue* poleSt = new ArrayValue();
    for (size_t i = 0; i < poleS.count(); i++)
    {
        ObjectValue* student1 = new ObjectValue{};
        student1->append(KeyValuePair("id", new NumberValue(poleS[i].getId())));
        student1->append(KeyValuePair("jmeno", new StringValue(poleS[i].getJmeno())));
        ObjectValue* predmetSt1 = new ObjectValue();
        if (poleS[i].getPredmet() == nullptr) {
            predmetSt1->append(KeyValuePair("nazev predmetu", new NullValue()));
        }
        else {
            predmetSt1->append(KeyValuePair("nazev predmetu", new StringValue(poleS[i].getPredmet()->getNazev())));
        }
        student1->append(KeyValuePair("predmet", predmetSt1));
        student1->append(KeyValuePair("studuje", new BoolValue(poleS[i].getStuduje())));
        poleSt->append(student1);
    }
    cout << JSON::serialize(poleSt) << endl;
    JSON::saveJSON(JSON::serialize(poleSt));
    cout << "Ulozeno do serialized.json" << endl;
    FuntionsUtil::deleteArr(poleSt);
}

void CRUD::smazStudenta(Array<Student>& studenti)
{
    int index = 0;
    cout << "Zadej index max (" << studenti.count() - 1 << "): ";
    cin >> index;
    try
    {
        studenti.remove(index);
    }
    catch (const std::exception& e)
    {
        cout << e.what();
    }
}

void CRUD::smazPredmet(Array<Predmet>& predmety, Array<Student>& studenti)
{
    int index = 0;
    cout << "Zadej index max (" << predmety.count() - 1 << "): ";
    cin >> index;
    try
    {
        for (size_t i = 0; i < studenti.count(); i++)
        {
            if (studenti.operator[](i).getPredmet() == &predmety.operator[](index)) {
                studenti.operator[](i).setPredmet(nullptr);
            }
        }
        predmety.remove(index);
    }
    catch (const std::exception& e)
    {
        cout << e.what();
    }
}
