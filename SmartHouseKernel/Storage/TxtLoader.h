#pragma once
#include "_Loader.h"
#include <fstream>
using namespace std;

class CTxtLoader : public ILoader
{
private:
    ifstream m_File;
    bool m_prevValueIsInt; // ������� ��� ������� ��������� �������� ���� ������
                           // (���� false �� ������� ��������� �������� - ������ � ��� ������������� ������� ����� ������ �� ������ �����)
public:
    CTxtLoader(const char* sFileName);

    virtual operator bool();
    virtual bool Load(OUT string& str);
    virtual bool Load(OUT int& value);
    virtual bool Load(OUT bool& value);
};
