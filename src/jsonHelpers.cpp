#include "jsonHelpers.h"

bool readJson(rapidjson::Document& doc, std::string filepath) {
#undef GetObject
    static const char* kTypeNames[] = { "Null", "False", "True", "Object", "Array", "String", "Number" };

    std::ifstream file(filepath);
    std::string json((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());

    doc.Parse(json.c_str());
    if (doc.HasParseError()) {
        fprintf(stderr, "\nError(offset %u): %s\n",
            (unsigned)doc.GetErrorOffset(),
            GetParseError_En(doc.GetParseError()));
        return false;
    }
    std::cout << sizeof(doc) << "\n";
    for (auto& m : doc.GetObject()) {
        std::cout << "Type of member" << m.name.GetString() << "is" << kTypeNames[m.value.GetType()];
        if (m.value.IsArray()) {
            std::cout << " of size " << m.value.Size();
        }
        std::cout << "\n";

        //if (m.name == "streets") {
        //    const Value& streets = m.value;
        //    for (SizeType i = 0; i < streets.Size(); i++) {// Uses SizeType instead of size_t
        //        cout << "\t" << streets[i]["name"].GetString() << "\n";
        //    }
        //}
        //else if (m.name == "citizens") {
        //    const Value& citizens = m.value;
        //    for (SizeType i = 0; i < citizens.Size(); i++) {// Uses SizeType instead of size_t
        //        cout << "\t" << citizens[i]["citizenName"].GetString() << "\n";
        //    }
        //}
    }

    return true;
}