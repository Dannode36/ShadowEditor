#include <iostream>
#include <string>
#include <streambuf>
#include <fstream>
#include "rapidjson/reader.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include <windows.h>
#include <tchar.h>
#include "Application.h"

// Main code
int main(int, char**)
{
    Application app;
    return app.Run();
}
