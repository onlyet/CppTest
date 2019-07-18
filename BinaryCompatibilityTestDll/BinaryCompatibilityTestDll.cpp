// BinaryCompatibilityTestDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"

#include "BinaryCompatibilityTestDll.h"

using namespace std;

Widget::Widget()
    : m_geometry(4)
    //, m_stylesheet("qwer")
    //, m_number(1000)
{
}

Label::Label()
    : Widget()
{
    m_text = "hello";
}

string Label::text() const
{
    return m_text;
}
