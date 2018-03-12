// main.cpp  String类新增加功能（基于KMP算法实现的）使用示例
#include <iostream>
#include "WoodString.h"
#include "Exception.h"

using namespace std;
using namespace WoodLib;

int main()
{
    String s = "Liyao learning DataStruct";
    const char* c = "Li";
    String p = "DataStruct";

    cout << " ------------- test 1 --------------- " << endl;
    cout << s.find("Li") << endl;
    cout << s.find(c) << endl;
    cout << s.find(p) << endl;

    cout << " ------------- test 2 --------------- " << endl;
    cout << s.remove("DataStruct").str() << endl;

    cout << " ------------- test 3 --------------- " << endl;
    cout << (s + "DataStruct").str() << endl;
    cout << s.str() << endl;
    cout << (s += "DataStruct").str() << endl;
    cout << s.str() << endl;

    cout << " ------------- test 4 --------------- " << endl;
    cout << s.replace("DataStruct","Qt").str() << endl;

    cout << " ------------- test 5 --------------- " << endl;
    cout << s.creatSubstr(0, 2).str() << endl;
    cout << s.str() << endl;

    cout << " ------------- test 6 --------------- " << endl;
    cout << (s - "Qt").str() << endl;
    cout << s.str() << endl;
    cout << (s -= "Qt").str() << endl;
    cout << s.str() << endl;

    return 0;
}
/* 运行结果
 ------------- test 1 ---------------
0
0
15
 ------------- test 2 ---------------
Liyao learning
 ------------- test 3 ---------------
Liyao learning DataStruct
Liyao learning
Liyao learning DataStruct
Liyao learning DataStruct
 ------------- test 4 ---------------
Liyao learning Qt
 ------------- test 5 ---------------
Li
Liyao learning Qt
 ------------- test 6 ---------------
Liyao learning
Liyao learning Qt
Liyao learning
Liyao learning
*/
