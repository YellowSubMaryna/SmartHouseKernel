#include "../stdafx.h"
#include "CmdStore.h"
#include <iostream>
#include <memory>
#include "../Context.h"
#include "../Storage/BinStorer.h"
#include "../Storage/TxtStorer.h"
using namespace std;

bool CCmdStore::Execute(CContext* pContext, vector<stringEx>& vParameters)
{
    if (vParameters.size() == 0 ||
        (vParameters[0] != "bin" && vParameters[0] != "txt"))
    {
        pContext->m_Console << "�� ������ ������ �����: bin - �������� ��� txt - ���������" << endl;
        return false;
    }
    if (vParameters.size() == 1)
    {
        pContext->m_Console << "�� ������� ��� �����" << endl;
        return false;
    }
    if (vParameters.size() > 2)
    {
        pContext->m_Console << "���������������� �������� �������" << endl;
        return false;
    }
    // ���������� ����� ���������, ����� �� �������������� ������� ����� �����, ����� delete �������� �������������
    unique_ptr<IStorer> pStorer;

    if (vParameters[0] == "bin")
        pStorer.reset(new CBinStorer(vParameters[1].c_str()));
    else
        pStorer.reset(new CTxtStorer(vParameters[1].c_str()));
    if (!*pStorer)
    {
        pContext->m_Console << "��������� ���� �� ������" << endl;
        return false;
    }
    if (!pContext->m_ActiveModel.Store(pStorer.get()))
    {
        pContext->m_Console.SetTextColor(enmColors::black, enmColors::dark_red);
        pContext->m_Console << "�� ������� ��������� �������� �������� �� ���������� �����" << endl <<
                               "�� �������� ��� ������� � ������ �������" << endl <<
                               "��������: ��� �������� ������� ����� ������������ �������� ���� �������" << endl;
        pContext->m_ActiveModel.DestroyAll(); // ������� �������� ����������� ����� ������������ ��������
        return false;
    }
    pContext->m_Console << "���� ������� �������" << endl;
    return true;
}