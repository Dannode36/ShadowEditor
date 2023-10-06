#include <iostream>
#include <string>
#include <streambuf>
#include <fstream>
#include "rapidjson/reader.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"

using namespace rapidjson;
using namespace std;

struct MyHandler {
    bool Null() { cout << "Null()" << endl; return true; }
    bool Bool(bool b) { cout << "Bool(" << boolalpha << b << ")" << endl; return true; }
    bool Int(int i) { cout << "Int(" << i << ")" << endl; return true; }
    bool Uint(unsigned u) { cout << "Uint(" << u << ")" << endl; return true; }
    bool Int64(int64_t i) { cout << "Int64(" << i << ")" << endl; return true; }
    bool Uint64(uint64_t u) { cout << "Uint64(" << u << ")" << endl; return true; }
    bool Double(double d) { cout << "Double(" << d << ")" << endl; return true; }
    bool RawNumber(const char* str, SizeType length, bool copy) {
        cout << "Number(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
        return true;
    }
    bool String(const char* str, SizeType length, bool copy) {
        cout << "String(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
        return true;
    }
    bool StartObject() { cout << "StartObject()" << endl; return true; }
    bool Key(const char* str, SizeType length, bool copy) {
        cout << "Key(" << str << ", " << length << ", " << boolalpha << copy << ")" << endl;
        return true;
    }
    bool EndObject(SizeType memberCount) { cout << "EndObject(" << memberCount << ")" << endl; return true; }
    bool StartArray() { cout << "StartArray()" << endl; return true; }
    bool EndArray(SizeType elementCount) { cout << "EndArray(" << elementCount << ")" << endl; return true; }
};

int main() {
    static const char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };

    ifstream file("example.cit");
    string json((istreambuf_iterator<char>(file)),
        istreambuf_iterator<char>());

    Document doc;
    doc.Parse(json.c_str());

    for (auto& m : doc.GetObject()) {
        cout << "Type of member" << m.name.GetString() << "is" << kTypeNames[m.value.GetType()];
        if (m.value.IsArray()) {
            cout << " of size " << m.value.Size();
        }
        cout << "\n";

        if (m.name == "streets") {
            const Value& streets = m.value;
            for (SizeType i = 0; i < streets.Size(); i++) {// Uses SizeType instead of size_t
                cout << "\t" << streets[i]["name"].GetString() << "\n";
            }
        }
        else if (m.name == "citizens") {
            const Value& citizens = m.value;
            for (SizeType i = 0; i < citizens.Size(); i++) {// Uses SizeType instead of size_t
                cout << "\t" << citizens[i]["citizenName"].GetString() << "\n";
            }
        }
    }
        
    return 0;
}
