//
//  logic.cpp
//  拼图AI2
//
//  Created by 邓中强 on 2019/3/21.
//  Copyright © 2019 邓中强. All rights reserved.
//

#include "logic.hpp"
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <queue>
#include <vector>
#include <map>

extern uint8_t EXCEPT[];
double xx = 0;

// 获取下一个状态
PuzzleState* PuzzleState::nextState(uint8_t dir){
    if (EXCEPT[_dir]!=dir && _d.canmove(dir) ){
        PuzzleState* state = new PuzzleState;
        int n = _d.getSize();
        PuzzleData *d = nullptr;
        uint8_t paths[1024]={dir}, k = 1;
        auto tmp = this;
        while (tmp) {
            if (tmp->_d.hasData()){
                d = &tmp->_d;
                break;
            }
            if(tmp->_dir<UNKOWN)
                paths[k++] = tmp->_dir;
            else assert(false);
            tmp = tmp->_prevState;
        }
        assert(d != nullptr);
        
        // 移动到目标状态
        for(int i=k-1;i>=0;i--){
            d->move(paths[i]);
        }
        
        state->_prevState = this;
        state->_dir = dir;
        state->_runSteps = this->_runSteps + 1;
        state->_score = d->getScore();// +int(hscore/xx);
        state->uuid.hash[0] =d->hash();
        state->uuid.hash[1] = state->_score;
//        memcpy(state->uuid.hash+1, &hscore, 4);
//        state->_id = state->uuid.id;
        // 每隔d->_n步 保存一次数据
//        state->_d.setSize(n);
//        state->_d._0 = d->_0;
        
        if (state->_runSteps % n == 0){
            memcpy(&state->_d, d->clone(), sizeof(state->_d));
        }
        else{// 浅拷贝
            state->_d.setSize(n);
            state->_d._0 = d->_0;
        }
        // 恢复到原始状态
        for(int i=0;i<k;i++){
            d->unmove(paths[i]);
        }
        return state;
    }
    return nullptr;
}

//
// class Puzzle impl
//

Puzzle::Puzzle(uint8_t n){
    PuzzleData *d = new PuzzleData(n);
    d->rand(n*1000);
    _d = d;
}

Puzzle::~Puzzle(){
    if(_d!=nullptr){
        delete _d;
        _d = nullptr;
    }
}

PuzzleState* Puzzle::getState(){
    PuzzleState* out = new PuzzleState;
    out->_prevState = nullptr;
    out->_runSteps = 0;
    out->_d = *_d->clone();
    out->_score = _d->getScore();//out->_runSteps
//    int n = out->_d.getSize();
    //int(out->_score/1.2);
//    xx = 0.9;//double(out->_score) / (n*n*n);
    printf("初始分数：%d\n",out->_score);
    out->uuid.hash[0] =_d->hash();
    out->uuid.hash[1] = out->_score;
    out->_dir = UNKOWN;
    return out;
}

// 是否可解
bool Puzzle::solvable(){
    int n = _d->getSize();
    int nn = _d->getSize2();
    uint8_t *order = _d->getData()[0];
    
    int count = 0;
    for(int i=0;i<nn;i++){
        int v = order[i];
        if(v){
            for(int j=i+1;j<nn;j++){
                if( order[j]>0 && order[j] < v)
                    count++;
            }
        }
        else{
            count+= i/n + i%n + (nn-i-1);
        }
    }
    return  count%2==0;
}

struct mygreater : std::binary_function<PuzzleState*, PuzzleState*, bool>
{
    bool operator()(const PuzzleState *__x, const PuzzleState *__y) const
    {
        int a = __x->_score>>2;
        int b = __y->_score>>2;
        return __x->_runSteps+a >= __y->_runSteps+b;
    }
};

// 求解拼图
void Puzzle::resove(std::stack<uint8_t> &result){
    assert(solvable());
    
    std::priority_queue<PuzzleState*,
                        std::vector<PuzzleState*>,
                        mygreater > q;
    std::map<uint64_t,bool> visited;
    
    int n = _d->getSize(), k=0;
    int n2 = n*n;
    int cacheSize = n*n*n;
    // push root state
    auto rootState = getState();
    q.push(rootState);
//    uint32_t hscore = rootState->_score;
    
    PuzzleState* cache[cacheSize];
    memset(cache, 0, sizeof(PuzzleState*)*cacheSize);
    
    while(!q.empty()){
        auto lastState = q.top();
        q.pop();
        k++;
//        cache[k++] = lastState;
//        printf("k:%d,score:%d\n",k++, lastState->_score);
        if( lastState->_score == 0 ){
            printf("k:%d,score:%d\n",k++, lastState->_score);
            // 保存结果
            auto tmp = lastState;
            while (tmp&&tmp->_runSteps>=1) {
                result.push(tmp->_dir);
                tmp = tmp->_prevState;
            }
            break;
        }
        
        visited[lastState->uuid.id] = true;
        
        // push round dir
        for (uint8_t dir=0; dir<UNKOWN; dir++) {
            auto state = lastState->nextState(dir);
            if( state!=nullptr){
//                q.push(state);
                if( visited[state->uuid.id])
                    delete state;
                else{
                    q.push(state);
                }
            }
        }
    }
    
    // 释放所有的内存
//    for(int i=0;i<k;i++){
//        if(cache[i])
//            delete cache[i];
//    }
    
    while (!q.empty()) {
        auto *lastState = q.top();
        q.pop();
        delete lastState;
    }
}
