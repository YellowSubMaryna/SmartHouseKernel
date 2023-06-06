#pragma once
#include "string"
#include <filesystem>
using namespace std;

class ILoader
{
public:
    ILoader()
    {}
    virtual ~ILoader()
    {}
    virtual operator bool() = 0;
    virtual bool Load(OUT string& str) = 0;
    virtual bool Load(OUT int& value) = 0;
    virtual bool Load(OUT bool& value) = 0;
    virtual bool Load(OUT vector <filesystem::path>&) = 0;
};

