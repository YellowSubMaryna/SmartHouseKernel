#pragma once
#include "_Command.h"

class CCmdList : public ICommand
{
public:
    CCmdList(){}

    virtual const char* Name()
    {
        return "list";
    }
    virtual const char* Hint() // ������� �������� �������� �������
    {
        return "���������� ������ �������� ��� �������� �������";
    }
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters)
    {
        if (!vParameters.size())
            return "�������������:\n"
                   "list               - ������� ������ ������������� ��������\n"
                   "list <��� �������> - ������� �������� ���������� �������\n";
        return ICommand::Help(pContext, vParameters); // ����������� ��������� �� ��������� �������� ��� ����������� ������ ����������
    }
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters);
};

