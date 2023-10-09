#include "jsonHelpers.h"
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

bool readJson(rapidjson::Document& doc, std::string filepath) {
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
        std::cout << "Type of member " << m.name.GetString() << " is " << kTypeNames[m.value.GetType()];
        if (m.value.IsArray()) {
            std::cout << " of size " << m.value.Size();
        }
        std::cout << "\n";
    }

    return true;
}
bool writeJson(rapidjson::Document& doc, std::string filepath) {
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);

    std::ofstream myfile(filepath);
    myfile << buffer.GetString();
    return true;
}
