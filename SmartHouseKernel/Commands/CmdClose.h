#pragma once
#include "_Command.h"

class CCmdClose : public ICommand
{
public:
    CCmdClose(){}

    virtual const char* Name()
    {
        return "close";
    }
    virtual const char* Hint() // ������� �������� �������� �������
    {
        return "������� �����";
    }
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters)
    {
        if (!vParameters.size())
            return "�������������:\n"
                   "close <��� �����> - ������� ��������� �����\n"
                   "close all         - ������� ��� �����\n";
        return ICommand::Help(pContext, vParameters); // ����������� ��������� �� ��������� �������� ��� ����������� ������ ����������
    }
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters);
};

