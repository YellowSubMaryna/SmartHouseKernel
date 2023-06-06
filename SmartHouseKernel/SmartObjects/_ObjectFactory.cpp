#include "../stdafx.h"
#include "_ObjectFactory.h"
#include "LampObject.h"
#include "DoorObject.h"
#include "RoomObject.h"
#include "../Utils/StringEx.h"
#include <assert.h>
using namespace std;

CObjectFactory::CObjectFactory()
                : m_Objects()
{
    RegObjectType(new CRoomObject("", 0, 0, 0, 0));
    RegObjectType(new CLampObject("", 0, 0, false));
    RegObjectType(new CDoorObject("", 0, 0, enmDirection::down, false));
}

void CObjectFactory::RegObjectType(CBaseObject* pObj)
{
    stringEx str(pObj->Type());
    str.strlwr(); // ��������� � �������� ������ � ������ ���������� � ������ ��������
                  // ��� ������ ���� ���������� ������ �������� � ������� ��������
                  // ����� ������� ������� ����� �������� �� ���������� ����� �������� ���������� �� ��������
    assert(m_Objects.count(str) == 0); // ���������, ��� ��� ��� ������������������� ���� �������� � ��� �� ������ �, ���� �������,
                                       // �� �������� ������� �������� ������������
    m_Objects[str] = pObj;
}

CObjectFactory::~CObjectFactory()
{
    for (map<string, CBaseObject*>::iterator p = m_Objects.begin(); p != m_Objects.end(); ++p)
        delete p->second;
    m_Objects.clear();
}

CBaseObject* CObjectFactory::CreateObject(const char* psTypeName)
{
    stringEx str(psTypeName);
    str.strlwr();
    map<string, CBaseObject*>::const_iterator pIter = m_Objects.find(str);
    if (pIter == m_Objects.end()) // ��� ������ ���� ��������
        return NULL;
    return pIter->second->Clone();
}
