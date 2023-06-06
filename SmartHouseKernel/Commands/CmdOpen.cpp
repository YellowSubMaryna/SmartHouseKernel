#include "../stdafx.h"
#include "CmdOpen.h"
#include <iostream>
#include "../Context.h"
#include "../SmartObjects/_IOpenCloseObject.h"
using namespace std;

bool CCmdOpen::Execute(CContext* pContext, vector<stringEx>& vParameters)
{
    if (vParameters.size() == 0)
    {
        pContext->m_Console << "�� ������� ��� �����" << endl;
        return false;
    }
    if (vParameters.size() > 1)
    {
        pContext->m_Console << "���������������� �������� �������" << endl;
        return false;
    }
    CBaseObject* pObj = pContext->m_ActiveModel.FindObject(vParameters[0].c_str());
    if (pObj)
    {
        IOpenCloseObject* pDoor = dynamic_cast<IOpenCloseObject*>(pObj);
        if (!pDoor)
        {
            pContext->m_Console << "��������� ������ �� ������������ ��������/��������" << endl;
            return false;
        }
        pDoor->Open();
        return true;
    }
    if (vParameters[0] == "all")
    {
        vector<IOpenCloseObject*> vpObjects;
        if (!pContext->m_ActiveModel.GetObjectsByType<IOpenCloseObject>(OUT vpObjects))
            pContext->m_Console << "������ �� �������" << endl;
        else
        {
            for (vector<IOpenCloseObject*>::iterator pIter = vpObjects.begin(); pIter != vpObjects.end(); ++pIter)
                (*pIter)->Open();
        }
        return true;
    }
    pContext->m_Console << "��������� ����� �� �������" << endl;
    return false;
}