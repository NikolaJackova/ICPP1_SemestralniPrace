// DemonstračníAplikace.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "api.h"
#include "Student.h"
#include "Predmet.h"
#include "CRUDUtil.h"
#include "Container.h"

using namespace std;

int main(){
    CRUD::zobrazMenu();
    int volba = 0;
    Array<Student>* poleS = new Array<Student>;
    Array<Predmet>* poleP = new Array<Predmet>;
    ArrayValue* poleSt = nullptr;
    do
    {
        cout << "Volba: ";
        cin >> volba;
        switch (volba)
        {
        case 1: 
        {
            Student* st = CRUD::vytvorStudenta(poleP);
            poleS->add(*st);
            delete st;
        }
            break;
        case 2:
            CRUD::upravStudenta(*poleS, *poleP);
            break;
        case 3:
            CRUD::smazStudenta(*poleS);
            break;
        case 4:
        {Predmet* p = CRUD::vytvorPredmet();
        poleP->add(*p);
        delete p; }
            break;
        case 5:
            CRUD::upravPredmet(*poleP);
            break;
        case 6:
            CRUD::smazPredmet(*poleP, *poleS);
            break;
        case 7:
            CRUD::zobrazStudenty(poleS);
            break;
        case 8:
            CRUD::zobrazPredmety(poleP);
            break;
        case 9:
            poleSt = dynamic_cast<ArrayValue*>(CRUD::nactiZeSouboru());
            CRUD::nacti(poleP, poleS, poleSt);
            break;
        case 10:
            CRUD::ulozDoSouboru(*poleS);
            break;
        case 11:
            CRUD::zobrazMenu();
            break;
        case 0:
            break;
        default:
            cerr << "Spatna volba!";
        }
    } while (volba != 0);
    FuntionsUtil::deleteArr(poleSt);
    delete poleP;
    delete poleS;
    return 0;
    /*try
    {
        cout << "Nacteny testovaci souboor json-bez-bilych-znaku-02.json:" << endl;
        string s = JSON::nactiJSON("json-bez-bilych-znaku-02.json");
        cout << s << endl << endl;
        Value* test = JSON::deserialize(s);
        cout << "Serializace testovaneho souboru: json-bez-bilych-znaku-02.json:" << endl;
        cout << test->serialize() << endl << endl;
        ObjectValue* obj = dynamic_cast<ObjectValue*>(test);
        FuntionsUtil::smazObj(obj);
    }
    catch (const std::exception& e)
    {
        cout << e.what() << endl << endl;
    }
    try
    {
        Predmet* pr1 = new Predmet("IT");
        Predmet* pr2 = new Predmet("C++");
        Student* st1 = new Student(1, "Karel", pr1);
        Student* st2 = new Student(2, "Josef", pr2);

        //pole studentu
        ArrayValue* poleSt = new ArrayValue{};

        //objekt student c. 1
        ObjectValue* student1 = new ObjectValue{};
        student1->append(KeyValuePair("id", new NumberValue(st1->getId())));
        student1->append(KeyValuePair("jmeno", new StringValue(st1->getJmeno())));
        ObjectValue* predmetSt1 = new ObjectValue();
        predmetSt1->append(KeyValuePair("nazev predmetu", new StringValue(st1->getPredmet()->getNazev())));
        student1->append(KeyValuePair("predmet", predmetSt1));

        //objekt student c. 2
        ObjectValue* student2 = new ObjectValue{};
        student2->append(KeyValuePair("id", new NumberValue(st2->getId())));
        student2->append(KeyValuePair("jmeno", new StringValue(st2->getJmeno())));
        ObjectValue* predmetSt2 = new ObjectValue{};
        predmetSt2->append(KeyValuePair("nazev predmetu", new StringValue(st2->getPredmet()->getNazev())));
        student2->append(KeyValuePair("predmet", predmetSt2));

        poleSt->append(student1);
        poleSt->append(student2);

        cout << "Serializace pole studentu a ulozeni do serialized.json:" << endl;
        cout << JSON::serialize(poleSt) << endl << endl;
        string s = JSON::nactiJSON("serialized.json");
        cout << "Deserializace pole studentu ze souboru serialized.json:" << endl;
        Value* serialized = JSON::deserialize(s);
        cout << serialized->serialize() << endl << endl;

        ArrayValue* smaz = dynamic_cast<ArrayValue*>(serialized);
        FuntionsUtil::smazArr(smaz);
        FuntionsUtil::smazArr(poleSt);
        delete st1;
        delete st2;
    }
    catch (const std::exception& e)
    {
        cout << e.what() << endl << endl;
    }*/
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
