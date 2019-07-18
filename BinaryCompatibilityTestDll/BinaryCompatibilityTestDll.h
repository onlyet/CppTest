#pragma once
#include <string>

#ifdef BINARYCOMPATIBILITYTEST_EXPORTS
#define DLL_API _declspec(dllexport)
#else
#define DLL_API _declspec(dllimport)
#endif

class DLL_API Widget
{
public:
    Widget();

    //private:
    int m_geometry;
    //std::string m_stylesheet;
    //double m_number;
    char c;
};

class DLL_API Label : public Widget
{
public:
    Label();

    std::string text() const;

    //private:
    std::string m_text;
};