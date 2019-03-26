//
//  logic.hpp
//  拼图AI2
//
//  Created by 邓中强 on 2019/3/21.
//  Copyright © 2019 邓中强. All rights reserved.
//

#ifndef logic_hpp
#define logic_hpp

#include <stdio.h>
#include <stdint.h>
#include <stack>
#include "PuzzleData.hpp"

class PuzzleState {
public:
    PuzzleState():_prevState(nullptr),
                _dir(UNKOWN),
                _runSteps(0),
                _score(0),
                uuid({.id = 0})
    
    { }
    
//    bool operator < (const PuzzleState &s)const{
//        return _score > s._score;
////        return (_runSteps + _score) > (s->_runSteps + s->_score);
//    }
    
    
    // 下一个状态
    PuzzleState* nextState(uint8_t dir);
    
public:
    
    union UUID {
        uint32_t hash[2];// hash[1] 存放hscore
        uint64_t id;
    }uuid;
    
    uint32_t _score;// 状态分数
    PuzzleState *_prevState;
    PuzzleData _d;
    uint8_t _dir;// 在前一个状态的基础上 进行dir操作后，达到当前状态
    uint32_t _runSteps;//执行到当前状态，所经历的步骤
};

class Puzzle{
public:
    Puzzle(uint8_t n);
    ~Puzzle();
    
    // A* 求解拼图
    void resove(std::stack<uint8_t> &result);
    
    // 是否可解
    bool solvable();
    
    void display(){ _d->display(); }
private:
    PuzzleState* getState();
    
private:
    PuzzleData *_d;
};

#endif /* logic_hpp */
