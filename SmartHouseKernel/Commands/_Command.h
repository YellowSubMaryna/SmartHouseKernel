#pragma once

#include "../Utils/StringEx.h"
using namespace std;

class CContext;

class ICommand
{
public:
    ICommand(){}
    virtual ~ICommand(){}

    virtual const char* Name() = 0;
    virtual const char* Hint() = 0; // ������� �������� �������� �������
    // ������� ������ �������� ������� ��� ���������� ������ ���������
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters)
    {
        return "��� �������������� ���������� �� �������� �������\n";
    }
    // ��������� ������� � ���������� ������� ����������
    // ����� �� ����������� ������ ��� ������ ���������� - ��� ����� ������
    // �� ����� ����� ���������� ������� �� �� ������������
    // returns ��������� ������� ��� ���� ����� ���� ������ � ������ ����������
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters) = 0;
};

