#pragma once
#include "_Command.h"

class CCmdLoad : public ICommand
{
public:
    CCmdLoad(){}

    virtual const char* Name()
    {
        return "load";
    }
    virtual const char* Hint() // ������� �������� �������� �������
    {
        return "��������� �� ���������� ����� ������������ ��������";
    }
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters)
    {
        if (!vParameters.size())
            return "�������������:\n"
                   "load txt <filename> - ��������� ��������� ����\n"
                   "load bin <filename> - ��������� �������� ����\n";
        return ICommand::Help(pContext, vParameters); // ����������� ��������� �� ��������� �������� ��� ����������� ������ ����������
    }
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters);
};

