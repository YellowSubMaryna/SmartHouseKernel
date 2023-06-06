#pragma once
#include "_Command.h"

class CCmdHelp : public ICommand
{
public:
    CCmdHelp(){}

    virtual const char* Name()
    {
        return "help";
    }
    virtual const char* Hint() // ������� �������� �������� �������
    {
        return "���������� ������ ��������� ������ ��� �������� ��������� �������";
    }
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters)
    {
        if (!vParameters.size())
            return "�������������:\n"
                   "help                    - ���������� ������ ��������� ������\n"
                   "help <�������� �������> - ���������� �������� �������\n";
        return ICommand::Help(pContext, vParameters); // ����������� ��������� �� ��������� �������� ��� ����������� ������ ����������
    }
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters);
};

