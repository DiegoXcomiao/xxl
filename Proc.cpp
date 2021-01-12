//
//  Proc.cpp
//  xxl
//
//  Created by 肖林 on 2020/12/26.
//

#include "Proc.h"

Proc::Proc() {
    _num = N;
    _data = new int *[N];
    for (int i = 0; i < _num; i++) {
        _data[i] = new int[N];
    }
    for (int j = 0; j < _num; j++) {
        for (int i = 0; i < _num; i++) {
            _data[j][i] = 0;
        }
    }
    for (int k = 0; k < _num * _num / 3; k++) {
        _v.insert(_v.end(), 1);
        _v.insert(_v.end(), 2);
        _v.insert(_v.end(), 3);
    }
}

Proc::~Proc() {
    for (int i = 0; i < _num; i++) {
        delete [] _data[i];
    }
    delete [] _data;
}

void Proc::PrintValue() {
    for (int j = 0; j < _num; j++) {
        for (int i = 0; i < _num; i++) {
            if (_data[j][i] == 0) {
                cout << "空 ";
            }
            else if (_data[j][i] == 1) {
                cout << "\e[31;1m红\e[0m ";
                // cout << "红 ";
            }
            else if (_data[j][i] == 2) {
                cout << "\e[33;1m黄\e[0m ";
                // cout << "黄 ";
            }
            else if (_data[j][i] == 3) {
                cout << "\e[34;1m蓝\e[0m ";
                // cout << "蓝 ";
            }
        }
        cout << endl;
    }
}

void Proc::Init() {
    for (int j = 0; j < _num; j++) {
        for (int i = 0; i < _num; i++) {
            _data[j][i] = GetValue(i, j);
        }
    }
}

int Proc::IsRepete(int i, int j, int num) {
    if (i >= 2) {
        if (num == _data[j][i-1] && num == _data[j][i-2]) {
            return 1;
        }
    }
    if (j >= 2) {
        if (num == _data[j-1][i] && num == _data[j-2][i]) {
            return 1;
        }
    }
    return 0;
}

int Proc::GetValue(int i, int j) {
    int num = 0;
    int index = 0;
    int length = (int)_v.size();
    do {
        num = _v[index++];
    }
    while (IsRepete(i, j, num) == 1 && index < length);
    _v.erase(_v.begin() + index - 1);
    
    return num;
}

int Proc::StringToInt(string s) {
    stringstream ss;
    ss << s;
    int i = 0;
    ss >> i;
    return i;
}

string Proc::IntToString(int i) {
    stringstream ss;
    ss << i;
    string s = "";
    ss >> s;
    return s;
}

string Proc::StrReplace(string str, string str1, string str2)
{
    try
    {
        if (str.find(str1) == string::npos)
            return str;
        return str.replace(str.find(str1), str1.length(), str2);
    }
    catch (...){
        cout << "替换字符串错" << endl;
    }
    return "";
}

Pos Proc::GetPos(string in) {
    string s1;
    string s2;
    s1 = in.substr(0,in.find(","));
    s2 = in.substr(in.find(",") + 1, in.length() - in.find(",") - 1);
    int posy = StringToInt(s1);
    int posx = StringToInt(s2);
    Pos pos = Pos();
    pos.SetX(posx);
    pos.SetY(posy);
    return pos;
}

int Proc::CheckInput(string & in) {
    if (in.find(",") == string::npos && in.find("，") == string::npos) {
        return -1;
    }
    in = StrReplace(in, "，", ",");
    Pos pos = GetPos(in);
    if (pos.GetX() < 1 || pos.GetX() > _num) {
        return -1;
    }
    if (pos.GetY() < 1 || pos.GetY() > _num) {
        return -1;
    }
    return 0;
}

int Proc::CheckInput2(string & in1, string & in2) {
    if (CheckInput(in1) < 0) {
        return -1;
    }
    if (CheckInput(in2) < 0) {
        return -1;
    }
    
    Pos pos1 = GetPos(in1);
    Pos pos2 = GetPos(in2);
    
    if (pos1.GetX() == pos2.GetX()) {
        if (pos1.GetY() - pos2.GetY() == 1) {
            return 0;
        }
        if (pos1.GetY() - pos2.GetY() == -1) {
            return 0;
        }
    }
    if (pos1.GetY() == pos2.GetY()) {
        if (pos1.GetX() - pos2.GetX() == 1) {
            return 0;
        }
        if (pos1.GetX() - pos2.GetX() == -1) {
            return 0;
        }
    }
    return -1;
}

void Proc::ChangePos(string & in1, string & in2) {
    Pos pos1 = GetPos(in1);
    Pos pos2 = GetPos(in2);
    
    int y1 = pos1.GetY() - 1;
    int x1 = pos1.GetX() -1;
    int y2 = pos2.GetY() - 1;
    int x2 = pos2.GetX() -1;
    
    if (_data[y1][x1] == 0 || _data[y2][x2] == 0) {
        cout << "请勿交换空块" << endl;
        return;
    }
    int tmp = _data[y1][x1];
    _data[y1][x1] = _data[y2][x2];
    _data[y2][x2] = tmp;
    cout << "交换后为: " << endl;
    PrintValue();
}

int Proc::ProcDelete() {
    vector<Pos> v = vector<Pos>();
    for (int j = 0; j < _num; j++) {
        for (int i = 0; i < _num; i++) {
            int flag = 0;
            if (_num - 1 - i >= 2) {
                if (_data[j][i] == _data[j][i+1] && _data[j][i] == _data[j][i+2] && _data[j][i] != 0) {
                    flag = 1;
                    Pos p1 = Pos();
                    p1.SetX(i+1);
                    p1.SetY(j);
                    Pos p2 = Pos();
                    p2.SetX(i+2);
                    p2.SetY(j);
                    v.insert(v.end(), p1);
                    v.insert(v.end(), p2);
                    for (int k = i + 3; k <= _num - 1; k++) {
                        if (_data[j][i] == _data[j][k]) {
                            Pos p3 = Pos();
                            p3.SetX(k);
                            p3.SetY(j);
                            v.insert(v.end(), p2);
                        } else {
                            break;
                        }
                    }
                }
            }
            if (_num - 1 - j >= 2) {
                if (_data[j][i] == _data[j+1][i] && _data[j][i] == _data[j+2][i] && _data[j][i] != 0) {
                    flag = 1;
                    Pos p4 = Pos();
                    p4.SetX(i);
                    p4.SetY(j+1);
                    Pos p5 = Pos();
                    p5.SetX(i);
                    p5.SetY(j+2);
                    v.insert(v.end(), p4);
                    v.insert(v.end(), p5);
                    for (int k = j + 3; k <= _num - 1; k++) {
                        if (_data[j][i] == _data[k][i]) {
                            Pos p6 = Pos();
                            p6.SetX(i);
                            p6.SetY(k);
                            v.insert(v.end(), p6);
                        } else {
                            break;
                        }
                    }
                }
            }
            if (flag == 1) {
                Pos p7 = Pos();
                p7.SetX(i);
                p7.SetY(j);
                v.insert(v.end(), p7);
            }
        }
    }
    if (v.size() == 0) {
        return -1;
    }
    for (int i = 0; i < v.size(); i++) {
        _data[v[i].GetY()][v[i].GetX()] = 0;
    }
    cout << "消去后为: " << endl;
    PrintValue();
    return 0;
}

void Proc::ProcDown() {
    for (int j = 1; j < _num; j++) {
        for (int i = 0; i < _num; i++) {
            if (_data[j][i] == 0) {
                for (int k = j; k > 0 ; k--) {
                    _data[k][i] = _data[k-1][i];
                }
                _data[0][i] = 0;
            }
        }
    }
    cout << "落下后为: " << endl;
    PrintValue();
}

void Proc::ProcDeleteDown() {
    while (1) {
        if (ProcDelete() == -1) {
            break;
        } else {
            ProcDown();
        }
    }
}

int Proc::IsOver() {
    int score = 0;
    for (int j = 0; j < _num; j++) {
        for (int i = 0; i < _num; i++) {
            if (_data[j][i] == 0) {
                score++;
            }
        }
    }
    cout << "消去得分：" << score << endl;
    if (score > SN) {
        cout << "游戏结束得分：" << score << endl;
        return 1;
    }
    return 0;
}
