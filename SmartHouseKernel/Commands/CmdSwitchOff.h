#pragma once
#include "_Command.h"
class CCmdSwitchOff : public ICommand
{
public:
    CCmdSwitchOff(){}

    virtual const char* Name()
    {
        return "off";
    }
    virtual const char* Hint() // ������� �������� �������� �������
    {
        return "��������� ����������";
    }
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters)
    {
        if (!vParameters.size())
            return "�������������:\n"
		           "off <��� �����������> - ��������� ��������� ����������\n"
		           "off all               - ��������� ��� �����������\n";
        return ICommand::Help(pContext, vParameters); // ����������� ��������� �� ��������� �������� ��� ����������� ������ ����������
    }
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters);
};

