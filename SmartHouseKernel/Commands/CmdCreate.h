#pragma once
#include "_Command.h"

class CCmdCreate : public ICommand
{
public:
    CCmdCreate() {}
    virtual const char* Name()
    {
        return "create";
    }
    virtual const char* Hint() // ������� �������� �������� �������
    {
        return "������� ����� ������";
    }
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters);
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters);
};

