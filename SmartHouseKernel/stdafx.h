// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#pragma once

#define _WIN32_WINNT _WIN32_WINNT_WIN2K
// _WIN32_WINNT_WIN7

// � ����� ������ ����������� �� ���������� ��� �������� ��� std::byte, ��� �������� �� ���������,
// �� ��� ���������� �� ��� �� ��� ���������� �� �� ���, ����������� ����� byte.
// ����� ���������� �� �������, ���� ���� �� ��� ���������.
#define _HAS_STD_BYTE 0

#include <stdio.h>
#include <tchar.h>
#include <math.h>
// TODO: reference additional headers your program requires here
#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "Utils/StringEx.h"
#include <map>
using namespace std;

#define OUT
#define countof(a) (sizeof(a)/sizeof(*(a)))

