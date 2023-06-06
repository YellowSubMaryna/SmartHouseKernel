#include "../stdafx.h"
#include "CmdCreate.h"
#include <iostream>
#include <assert.h>
#include "../Context.h"
using namespace std;

// ����� ��������� � ���� ������ ������ ������������ ��� ����� ��������. ��� ��������������� ��� ������������� ���
// �������������� ��������� ������
const char* g_vsReservedWords[] = { "all" };

std::string CCmdCreate::Help(CContext* pContext, const vector<stringEx>& vParameters)
{
    if (!vParameters.size())
    {
        string res = "�������������:\n    create <��� �������> <��� ������� ��� ��������>\n�������������� ���� ��������:\n";
        const map<string, CBaseObject*>* pvObjSamples = &pContext->m_ObjFactory.Objects();
        for (map<string, CBaseObject*>::const_iterator p = pvObjSamples->begin(); p != pvObjSamples->end(); ++p)
        {
            res += "   ";
            res += p->second->Type();
            res += " - ";
            res += p->second->Hint();
            res += '\n';
        }
        return res;
    }
    return ICommand::Help(pContext, vParameters);
}

bool CCmdCreate::Execute(CContext* pContext, vector<stringEx>& vParameters)
{
    if (vParameters.size() == 0)
    {
        pContext->m_Console << "�� ������ ��� ������������ �������" << endl;
        return false;
    }
    if (vParameters.size() == 1)
    {
        pContext->m_Console << "�� ������� ��� ������������ �������" << endl;
        return false;
    }
    if (vParameters.size() != 2)
    {
        pContext->m_Console << "������� ������� ����� ���������� ��� ���� �������" << endl;
        return false;
    }
    CBaseObject* pObj = pContext->m_ActiveModel.FindObject(vParameters[1].c_str());
    if (pObj)
    {
        pContext->m_Console << "������ � ����� ������ ��� ����������" << endl;
        return false;
    }
    for (size_t i = 0; i < countof(g_vsReservedWords); i++)
    {
        if (vParameters[1] == g_vsReservedWords[i])
        {
            pContext->m_Console << "��������� ��� �� ����� ���� ��������� �������, ��� ����� ���������������" << endl;
            return false;
        }
    }
    pObj = pContext->m_ObjFactory.CreateObject(vParameters[0].c_str());
    if (!pObj)
    {
        pContext->m_Console << "������ ����������� ��� �������" << endl;
        return false;
    }
    pObj->m_Name = vParameters[1];
    if (!pObj->InputParams(pContext->m_Console))
    {
        pContext->m_Console.ClearErrorFlag();
        delete pObj;
        return false;
    }
    if (!pContext->m_ActiveModel.AddObject(pObj))
    {
        assert(false); // ������ ��� ��������� ��� ����� ��� �� ������������
        delete pObj;
        pContext->m_Console << "������ � ����� ������ ��� ����������" << endl;
        return false;
    }
    pContext->m_Console << "����� ������ " << vParameters[1].c_str() << " ������" << endl;
    return true;
}
