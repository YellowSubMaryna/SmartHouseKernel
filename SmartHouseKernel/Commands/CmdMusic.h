#pragma once
#include "_Command.h"

class CCmdMusic : public ICommand
{
public:
    CCmdMusic(){}

    virtual const char* Name()
    {
        return "music";
    }
    virtual const char* Hint() // ������� �������� �������� �������
    {
        return "���������� ���������������� �������";
    }
    virtual string Help(CContext* pContext, const vector<stringEx>& vParameters);
    virtual bool Execute(CContext* pContext, vector<stringEx>& vParameters);
};

