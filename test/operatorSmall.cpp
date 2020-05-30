#include "common.h"

class OperatorSmall
{
public:
    OperatorSmall(int i) : i(i) {}

    bool operator==(OperatorSmall& rhs)
    {
        return i == rhs.i;
    }

    int i;
};

void operatorSmallDemo()
{
    OperatorSmall x(1), y(1);
    cout << (x == y) << endl;
}