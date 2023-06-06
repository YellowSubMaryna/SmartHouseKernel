#include "../stdafx.h"
#include "DoorObject.h"
#include "../Storage/_Storer.h"
#include "../Storage/_Loader.h"
#include <iostream>
#include <sstream>
using namespace std;

CDoorObject::CDoorObject(const char* psName, int x, int y, enmDirection dir, bool isOpen)
    : CBaseObject(psName),
      m_X(x),
      m_Y(y),
      m_Dir(dir),
      m_isOpen(isOpen)
{
}


CDoorObject::~CDoorObject()
{
}

bool CDoorObject::InputParams(CConsoleManip& console)
{
    console << "������� ��������� ����� X Y ������������ ������ �������� ���� �������: ";
    console >> m_X >> m_Y;
    if (!console)
    {
        console.ClearErrorFlag();
        console << "������� ������������ ���������" << endl;
        return false;
    }
    if (m_X < 0 || m_X >= console.DrawSpaceSize().X ||
        m_Y < 0 || m_Y >= console.DrawSpaceSize().Y)
    {
        console << "�������� ���������� ��������� ��� �������" << endl;
        console << "������ ������������ ��� �����������:";
        console << console.DrawSpaceSize().X << " " << console.DrawSpaceSize().Y << endl;
        return false;
    }
    console << "������� ����������� �������� �����"
               "(����� - " << (int)enmDirection::up <<
               ", ����� - " << (int)enmDirection::left <<
               ", ���� - " << (int)enmDirection::down <<
               ", ������ - " << (int)enmDirection::right <<
               "): ";
    int dir;
    cin >> dir;
    if (!console ||
        (dir != (int)enmDirection::up &&
         dir != (int)enmDirection::down &&
         dir != (int)enmDirection::right &&
         dir != (int)enmDirection::left))
    {
        console.ClearErrorFlag();
        console << "������� ������������ �����������" << endl;
        return false;
    }
    m_Dir = static_cast<enmDirection>(dir);
    m_isOpen = false;
    return true;
}

bool CDoorObject::Draw(CConsoleManip& console) const
{
    if (!m_isOpen)
    {
        if (m_Dir == enmDirection::down ||
            m_Dir == enmDirection::up)
            return console.DrawTextMultiline(m_X, m_Y, "----");
        else
            return console.DrawTextMultiline(m_X, m_Y, "|\n"
                                                       "|\n"
                                                       "|");
    }
    // open
    if (m_Dir == enmDirection::down)
    {
        return console.DrawTextMultiline(m_X, m_Y, "\\   \n"
                                                   " \\\n"
                                                   "  \\");
    }
    else if (m_Dir == enmDirection::up)
    {
        return console.DrawTextMultiline(m_X, m_Y - 2, "  /\n"
                                                       " /\n"
                                                       "/   ");
    }
    else if (m_Dir == enmDirection::left)
    {
        return console.DrawTextMultiline(m_X - 2, m_Y, "  /\n"
                                                       " / \n"
                                                       "/  ");
    }
    else // if (m_Dir == Direction::right)
    {
        return console.DrawTextMultiline(m_X, m_Y, "\\\n"
                                                   " \\\n"
                                                   "  \\");
    }
}
bool CDoorObject::Store(IStorer* pStorer) const
{
    if (!CBaseObject::Store(pStorer))
        return false;
    return pStorer->Store(m_X) &&
        pStorer->Store(m_Y) &&
        pStorer->Store(m_isOpen) &&
        pStorer->Store(static_cast<int>(m_Dir));
}
bool CDoorObject::Load(ILoader* pLoader)
{
    int dir = 0;
    if (!CBaseObject::Load(pLoader) ||
        !pLoader->Load(OUT m_X) ||
        !pLoader->Load(OUT m_Y) ||
        !pLoader->Load(OUT m_isOpen) ||
        !pLoader->Load(OUT dir))
        return false;
    m_Dir = static_cast<enmDirection>(dir);
    return true;
}

void CDoorObject::Open()
{
    m_isOpen = true;
}
void CDoorObject::Close()
{
    m_isOpen = false;
}

void CDoorObject::PrintProperties(CConsoleManip& console) const
{
    CBaseObject::PrintProperties(console);
    console << "X: " << m_X << ", Y: " << m_Y << endl;
    console << "���������: " << (m_isOpen ? "�������" : "�������") << endl;
    console << "�����������: ";
    switch (m_Dir)
    {
    case enmDirection::up:
        console << "�����";
        break;
    case enmDirection::down:
        console << "����";
        break;
    case enmDirection::left:
        console << "�����";
        break;
    case enmDirection::right:
        console << "������";
        break;
    default:
        console << "����������";
    }
    console << endl;
}
