//
//  Pos.hpp
//  xxl
//
//  Created by 肖林 on 2021/1/8.
//

#ifndef Pos_hpp
#define Pos_hpp

class Pos {
public:
    int GetX();
    int GetY();
    void SetX(int x);
    void SetY(int y);
private:
    int _x;
    int _y;
};

#endif /* Pos_h */
