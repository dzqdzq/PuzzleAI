//
//  PuzzleData.hpp
//  拼图AI2
//
//  Created by 邓中强 on 2019/3/22.
//  Copyright © 2019 邓中强. All rights reserved.
//

#ifndef PuzzleData_hpp
#define PuzzleData_hpp
#include <stdio.h>
#include <stdint.h>

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define UNKOWN 4

typedef struct {
    int i,j;
}Pos;

uint32_t crc32(uint8_t *d, int n);
double rand01();
uint32_t manhattanDistance(int a,int b,int c, int d);
uint32_t manhattanDistance(Pos *a,Pos *b);

class PuzzleData{
    
public:
    PuzzleData():_n(0),_d(nullptr){};
    PuzzleData(int n);
    
    ~PuzzleData();
    
    void rand(int step);
    
    void display();
    
    uint8_t moveDst(Pos *curPos,uint8_t v);
    uint32_t getScore();
    uint32_t getScore1();
    uint32_t getScore2();// 最大移动步骤
    
    // 是否可以移动
    bool canmove(uint8_t dir);
    
    // 向某方向移动。  如果可以移动，那么就移动并返回true, 否则返回false
    bool move(uint8_t dir);
    
    // 取消某方向移动。
    bool unmove(uint8_t dir);
    
    PuzzleData* clone();
    uint8_t** getData() { return _d; }
    void setSize(int n) { _n = n; }
    int getSize() const { return _n; }
    int getSize2() { return _n*_n; }
    bool hasData(){ return _d != nullptr; }
    
    uint32_t hash();
    
    
public:
    Pos _0;
    
private:
    int _n;
    uint8_t** _d;
};
#endif /* PuzzleData_hpp */
