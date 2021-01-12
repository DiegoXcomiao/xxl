//
//  main.cpp
//  xxl
//
//  Created by 肖林 on 2020/12/26.
//

#include "Proc.h"

int main(int argc, const char * argv[]) {
    Proc proc = Proc();
    proc.Init();
    proc.PrintValue();
    while (1) {
        cout << "请输入想移动的块的位置，例如1,2就是第一行第二列，输入quit退出游戏： " << endl;
        string pos1;
        cin >> pos1;
        if (pos1 == "quit") {
            break;
        }
        if (proc.CheckInput(pos1) < 0) {
            cout << "请输入正确的位置" << endl;
            continue;
        }
        cout << "请输入想交换位置的块的位置，例如2,2就是第二行第二列，输入quit退出游戏： " << endl;
        string pos2;
        cin >> pos2;
        if (pos2 == "quit") {
            break;
        }
        if (proc.CheckInput2(pos1, pos2) < 0) {
            cout << "请输入上下或者左右挨着第一次输入的位置的正确的位置" << endl;
            continue;
        }
        proc.ChangePos(pos1, pos2);
        proc.ProcDeleteDown();
        if (proc.IsOver() == 1) {
            break;
        }
    }
    return 0;
}
