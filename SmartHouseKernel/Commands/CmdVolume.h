#pragma once
#include "_Command.h"

class CCmdVolume : public ICommand
{
public:
    CCmdVolume(){}

    virtual const char* Name()
    {
        return "volume";
    }
    virtual const char* Hint() // ������� �������� �������� �������
    {
        return "������ ��� ������ ������� ��������� ���������������";
    }
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters)
    {
        if (!vParameters.size())
            return "�������������:\n"
                   "volume\n"
                   "volume <������� ��������� 0-128>\n";
        return ICommand::Help(pContext, vParameters); // ����������� ��������� �� ��������� �������� ��� ����������� ������ ����������
    }
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters);
};

