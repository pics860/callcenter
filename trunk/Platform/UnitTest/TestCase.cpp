#include "stdlib.h"
#include "Config.h"

#include "CString.h"

#include <iostream>

using namespace std;

int Test_CString()
{
    CString str("tttt", 3);
    CString str2 = str;
//    CString str3((LPCWSTR)"ssdsd");
    cout << "Hello world!" << endl;
    cout << str2 << endl;


    return 0;
}

int main(int argc, char** argv)
{
    Test_CString();

    return 0;
}

