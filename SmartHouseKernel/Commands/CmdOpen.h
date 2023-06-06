#pragma once
#include "_Command.h"

class CCmdOpen : public ICommand
{
public:
    CCmdOpen(){}
    virtual const char* Name()
    {
        return "open";
    }
    virtual const char* Hint() // ������� �������� �������� �������
    {
        return "������� �����";
    }
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters)
    {
        if (!vParameters.size())
            return "�������������:\n"
                   "open <��� �����> - ������� ��������� �����\n"
                   "open all         - ������� ��� �����\n";
        return ICommand::Help(pContext, vParameters); // ����������� ��������� �� ��������� �������� ��� ����������� ������ ����������
    }
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters);
};

