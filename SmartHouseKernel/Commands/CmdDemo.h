#pragma once
#include "_Command.h"

class CCmdDemo : public ICommand
{
public:
    CCmdDemo(){}

    virtual const char* Name()
    {
        return "demo";
    }
    virtual const char* Hint() // ������� �������� �������� �������
    {
        return "�������� ����� �������� �� ����������������";
    }
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters)
    {
        if (!vParameters.size())
            return "�������������:\n"
                   "demo\n";
        return ICommand::Help(pContext, vParameters); // ����������� ��������� �� ��������� �������� ��� ����������� ������ ����������
    }
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters);
};

