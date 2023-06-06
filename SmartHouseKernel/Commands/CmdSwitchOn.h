#pragma once
#include "_Command.h"


class CCmdSwitchOn : public ICommand
{
public:
    CCmdSwitchOn(){}

    virtual const char* Name()
    {
        return "on";
    }
    virtual const char* Hint() // ������� �������� �������� �������
    {
        return "�������� ����������";
    }
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters)
    {
        if (!vParameters.size())
            return "�������������:\n"
				   "on <��� �����������> - �������� ��������� ����������\n"
		           "on all               - �������� ��� �����������\n";
        return ICommand::Help(pContext, vParameters); // ����������� ��������� �� ��������� �������� ��� ����������� ������ ����������
    }
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters);
};

