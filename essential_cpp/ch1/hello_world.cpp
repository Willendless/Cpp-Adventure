#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int
main()
{
    string user_name;
    cout << "Please input your name: ";
    cin >> user_name;
    cout << "\n";

    cout << "Hello world, "
         << user_name
         << "... and goodbye!"
         << "\n";

    return 0;
}
