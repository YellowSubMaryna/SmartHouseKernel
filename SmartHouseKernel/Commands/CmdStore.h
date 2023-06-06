#pragma once
#include "_Command.h"

class CCmdStore : public ICommand
{
public:
    CCmdStore(){}

    virtual const char* Name()
    {
        return "store";
    }
    virtual const char* Hint() // ������� �������� �������� �������
    {
        return "��������� ������������ �������� � ��������� ����";
    }
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters)
    {
        if (!vParameters.size())
            return "�������������:\n"
                   "store txt <filename> - ��������� � ��������� ����\n"
                   "store bin <filename> - ��������� � �������� ����\n";
        return ICommand::Help(pContext, vParameters); // ����������� ��������� �� ��������� �������� ��� ����������� ������ ����������
    }
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters);
};
