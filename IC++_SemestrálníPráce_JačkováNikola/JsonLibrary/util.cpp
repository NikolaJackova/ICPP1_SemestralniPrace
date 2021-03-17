#include "api.h"
#include <string>

using namespace std;

void FuntionsUtil::replaceAll(std::string& str, const std::string& from, const std::string& to)
{
	if (from.empty())
		return;
	size_t start_pos = 0;
	while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}

void FuntionsUtil::deleteObj(ObjectValue* obj)
{
    DynamicArray<KeyValuePair>& pole = obj->getArray();
    for (int j = 0; j < pole.getSize(); j++)
    {
        if (dynamic_cast<ObjectValue*>(pole.getElementAt(j).getValue())) {
            ObjectValue* obj1 = dynamic_cast<ObjectValue*>(pole.getElementAt(j).getValue());
            deleteObj(obj1);
        }
        else if (dynamic_cast<ArrayValue*>(pole.getElementAt(j).getValue())) {
            ArrayValue* obj1 = dynamic_cast<ArrayValue*>(pole.getElementAt(j).getValue());
            deleteArr(obj1);
        }
        else {
            delete pole.getElementAt(j).getValue();
        }
    }
    delete obj;
}

void FuntionsUtil::deleteArr(ArrayValue* arr)
{
    DynamicArray<Value*>& pole = arr->getArray();
    for (int i = 0; i < pole.getSize(); i++)
    {
        if (dynamic_cast<ObjectValue*>(pole.getElementAt(i))) {
            ObjectValue* obj1 = dynamic_cast<ObjectValue*>(pole.getElementAt(i));
            deleteObj(obj1);
        }
        else if (dynamic_cast<ArrayValue*>(pole.getElementAt(i))) {
            ArrayValue* obj1 = dynamic_cast<ArrayValue*>(pole.getElementAt(i));
            deleteArr(obj1);
        }
        else {
            delete pole.getElementAt(i);
        }
    }
   delete arr;
}
