#pragma once
#include <iostream>
#include <string>
#include <streambuf>
#include <fstream>
#include "rapidjson/reader.h"
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/error/en.h"
using namespace rapidjson;

bool readJson(rapidjson::Document& doc, std::string filepath);
bool writeJson(rapidjson::Document& doc, std::string filepath);
