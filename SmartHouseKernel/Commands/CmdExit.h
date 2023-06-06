#pragma once
#include "_Command.h"

class CCmdExit : public ICommand
{
public:
    CCmdExit(){}

    virtual const char* Name()
    {
        return "exit";
    }
    virtual const char* Hint() // ������� �������� �������� �������
    {
        return "���������� ������ ���������";
    }
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters)
    {
        if (!vParameters.size())
            return "�������������:\n"
                   "exit\n";
        return ICommand::Help(pContext, vParameters); // ����������� ��������� �� ��������� �������� ��� ����������� ������ ����������
    }
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters);
};

