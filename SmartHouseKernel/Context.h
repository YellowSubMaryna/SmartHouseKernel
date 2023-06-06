#pragma once
#include "Commands/_CommandHolder.h"
#include "SmartObjects/_ObjectFactory.h"
#include "Utils\ConsoleManip.h"
#include "Model.h"

class CContext
{
private:
	// ����, ��� ���� ��������� ������ ���������
	// ��� ���������� ������ ������ ��������� � true
    bool m_bExiting;
public:
    CContext();
    virtual ~CContext();

	CModel m_ActiveModel; // ������� ����� ������������ ��������
    CConsoleManip m_Console; // �������, � ������������ ��������� ����� � ��������� ������ ������ 
    CObjectFactory m_ObjFactory; 
    CCommandHolder m_Commands; // ����� ��������� ���������� ������
    void Exit()
    {
        m_bExiting = true;
    }
    bool IsExiting() const
    {
        return m_bExiting;
    }
};

