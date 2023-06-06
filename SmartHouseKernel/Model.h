#pragma once
#include "Utils\ConsoleManip.h"
#include "Utils\MusicContext.h"
#include "SmartObjects/_BaseObject.h"
#include "SmartObjects/_ObjectFactory.h"
using namespace std;


// ������ ��� "�����" ������� ������������� � ������ ������ �� �����

class CModel
{
private:
	vector<CBaseObject*> m_Objects; // ������� � ������� �������� (������ �������������� � ����� �������)
public:
	CMusicContext m_MusicContext;

	CModel();
	virtual ~CModel(); // virtual - �� ������ ���������� ����������� ���������� ���������, � ������ ������ �� ������������, ��������� ����������� ����� ������ ���

	// ������� ��� �������
	void DestroyAll();
	// ������� ����� ������������ �������� �� �������
	bool DrawAll(CConsoleManip& console);

	bool Store(IStorer* pStorer);
	bool Load(ILoader* pLoader, CObjectFactory* pFactory);
	// ����� ������ �� ��� ����� (���� ��� ������ - ����� nullptr)
	CBaseObject* FindObject(const char* psName);
	// ����� ��� ������� ���������� ����
	// ���������� ���������� ��������� �������� � ��������� ���������� ��������� ���������
	size_t GetObjectsByType(const char* psTypeName, OUT vector<CBaseObject*>& pvFoundObjects);
	// ����� ��� ������� �������������� ��������� ���������
	// ���������� ���������� ��������� �������� � ��������� ���������� ��������� ���������
	template<class INTERFACE_TO_SEARCH>
	size_t GetObjectsByType(OUT vector<INTERFACE_TO_SEARCH*>& pvFoundObjects)
    {
        pvFoundObjects.clear();
        for (vector<CBaseObject*>::iterator pIter = m_Objects.begin(); pIter != m_Objects.end(); ++pIter)
        {
            INTERFACE_TO_SEARCH* pObj = dynamic_cast<INTERFACE_TO_SEARCH*>(*pIter);
            if (pObj)
                pvFoundObjects.push_back(pObj);
        }
        return pvFoundObjects.size();
    }

	// ������� ������ � ��������� ������
	// ����������: true - ������ �����
	//             false - ������ ������� �� ����
	bool DeleteObject(const char* psName);
	// ��������� ������ � ��������
	// ����������: true - ������ ��������
	//             false - ������ � ����� ������ ��� ����������
	bool AddObject(CBaseObject* pObj);

	// ������� �� ����� ������ ��������
	void PrintListOfObjects(CConsoleManip& console) const;
};

