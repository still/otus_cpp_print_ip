#include "lib.h"
#include <vector>
#include <list>
#include <tuple>

using namespace std;

int main()
{
    print_ip(char(-1));
    print_ip(short(0));
    print_ip(int(2130706433));
    print_ip(long(8875824491850138409));
    print_ip("192.168.1.1");
    print_ip(vector<int>{ 192, 168, 1, 2 });
    print_ip(list<long>{ 192, 168, 1, 3 });
    print_ip(make_tuple(192, 168, 1, 4));
    print_ip(make_tuple("192", "168", "1", "5"));
//    print_ip(make_tuple("192", 168, "1", 6));
}
