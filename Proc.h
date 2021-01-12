//
//  Proc.h
//  xxl
//
//  Created by 肖林 on 2020/12/26.
//

#ifndef Proc_h
#define Proc_h
#include <iostream>
#include <sstream>
#include <string.h>
#include <set>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <ctype.h>
#include <time.h>
#include <stdarg.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <stdlib.h>
#include <vector>
#include "Pos.h"

using namespace std;

#define N 12
#define SN 100

class Proc {
public:
    Proc();
    virtual ~Proc();
    void PrintValue();
    void Init();
    int GetValue(int i, int j);
    int IsRepete(int i, int j, int num);
    Pos GetPos(string in);
    int CheckInput(string & in);
    int CheckInput2(string & in1, string & in2);
    void ChangePos(string & in1, string & in2);
    int StringToInt(string s);
    string IntToString(int i);
    int ProcDelete();
    void ProcDown();
    string StrReplace(string str, string str1, string str2);
    void ProcDeleteDown();
    int IsOver();
private:
    int ** _data;
    int _num;
    vector<int> _v;
};

#endif /* Proc_h */
