#include "../stdafx.h"
#include "RoomObject.h"
#include "../Storage/_Storer.h"
#include "../Storage/_Loader.h"
#include <iostream>
#include <sstream>
using namespace std;

// ���� �������� ������������� ����� �������� ���� ������� (������� �������) � ��������� cp866
const char UPP_LEFT = (char)201;
const char UPP_RIGHT = (char)187;
const char DWN_LEFT = (char)200;
const char DWN_RIGHT = (char)188;
const char HORZ = (char)205;
const char VERT = (char)186;

CRoomObject::CRoomObject(const char* psName, int x, int y, int width, int height)
    : CBaseObject(psName),
      m_X(x),
      m_Y(y),
      m_Width(width),
      m_Height(height)
{
}

bool CRoomObject::InputParams(CConsoleManip& console)
{
    console <<"������� ��������� ������ �������� ���� �������: ";
    console >> m_X >> m_Y;
    if (!console)
    {
        console.ClearErrorFlag();
		console <<"������� ������������ ���������" << endl;
        return false;
    }
    if (m_X < 0 || m_X >= console.DrawSpaceSize().X ||
        m_Y < 0 || m_Y >= console.DrawSpaceSize().Y)
    {
        console << "�������� ���������� ��������� ��� �������" << endl;
        console << "������ ������������ ��� �����������:";
        console << console.DrawSpaceSize().X << " " <<
                   console.DrawSpaceSize().Y << endl;
        return false;
    }
    console << "������������ ������ ������� � ��������� ���������:";
    console << (console.DrawSpaceSize().X - m_X - 1) << " " <<
               (console.DrawSpaceSize().Y - m_Y - 1) << endl;
    console << "������� ������� ������� (������ � ������): ";
    console >> m_Width >> m_Height;
    if (!console)
    {
        console.ClearErrorFlag();
        console <<"����� ������������ ������ �������" << endl;
        return false;
    }
    if (m_Width <= 0 || m_X + m_Width >= console.DrawSpaceSize().X ||
        m_Height <= 0 || m_Y + m_Height >= console.DrawSpaceSize().Y)
    {
        console << "�������� ������� �� ���������� � ���������� ��� ����� ������� �������" << endl;
        return false;
    }
    return true;
}

bool CRoomObject::Draw(CConsoleManip& console) const
{
    bool bRes = true;
    stringEx sHorz;
    // ������ ������� �����
    sHorz.resize(m_Width + 1, HORZ);
    sHorz[0] = UPP_LEFT;
    sHorz[m_Width] = UPP_RIGHT;
    bRes &= console.DrawTextMultiline(m_X, m_Y, sHorz.c_str());
    // ������ ������ �����
    sHorz[0] = DWN_LEFT;
    sHorz[m_Width] = DWN_RIGHT;
    bRes &= console.DrawTextMultiline(m_X, m_Y + m_Height, sHorz.c_str());
    // ������ ������� ������
    sHorz = VERT;
    for (int i = 1; i < m_Height; i++)
    {
        bRes &= console.DrawTextMultiline(m_X, m_Y + i, sHorz);
        bRes &= console.DrawTextMultiline(m_X + m_Width, m_Y + i, sHorz);
    }
    return bRes;
}
bool CRoomObject::Store(IStorer* pStorer) const
{
    if (!CBaseObject::Store(pStorer))
        return false;
    return pStorer->Store(m_X) &&
           pStorer->Store(m_Y) &&
           pStorer->Store(m_Width) &&
           pStorer->Store(m_Height);
}
bool CRoomObject::Load(ILoader* pLoader)
{
    return CBaseObject::Load(pLoader) &&
           pLoader->Load(OUT m_X) &&
           pLoader->Load(OUT m_Y) &&
           pLoader->Load(OUT m_Width) &&
           pLoader->Load(OUT m_Height);
}

void CRoomObject::PrintProperties(CConsoleManip& console) const
{
    CBaseObject::PrintProperties(console);
    console << "X: " << m_X << ", Y: " << m_Y << endl;
    console << "�������: " << m_Width << " x " << m_Height << endl;
}
