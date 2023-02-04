#include "protected_test.h"
#include "common.h"

void protected_test()
{
    Widget w;
    w.call_base_protected_func();
    //w.protected_func();
    //w.protected_data
}

void Object::tt()
{
    Widget* w = new Widget;
    w->protected_data;
    //w->protected_func();  //错误，调用的是派生类Widget::protected_func()
}

void protected_tt()
{
    Widget* w = new Widget;
    //w->protected_data;
    
}

void Widget::test()
{
    Widget* w = new Widget;
    w->protected_data;
    w->protected_func();
    protected_data;
}
