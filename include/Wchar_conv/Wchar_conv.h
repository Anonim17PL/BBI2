#pragma once
#include <codecvt>
#include "Wchar_conv.h"
using namespace std;
wstring s2ws(const std::string& str);
string ws2s(const std::wstring& wstr);