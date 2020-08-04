#include "common.h"
#include <Thread>
#include <sstream>

using namespace std;

void print_thread_id()
{
	ostringstream os;
	os << this_thread::get_id();
	cout << os.str() << endl;

	size_t a = std::hash<std::thread::id>()(std::this_thread::get_id());
	cout << a << endl;
}
