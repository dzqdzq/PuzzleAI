//
//  PuzzleData.cpp
//  拼图AI2
//
//  Created by 邓中强 on 2019/3/22.
//  Copyright © 2019 邓中强. All rights reserved.
//

#include "PuzzleData.hpp"
#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <string.h>

#define MAX(x,y) ((x)>(y)?(x):(y))

uint8_t EXCEPT[] = {DOWN,UP,RIGHT,LEFT,UNKOWN};
const char *DESC[] = {"上","下","左","右"};

const uint32_t table[] = {
    0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419, 0x706af48f, 0xe963a535, 0x9e6495a3,
    0x0edb8832, 0x79dcb8a4, 0xe0d5e91e, 0x97d2d988, 0x09b64c2b, 0x7eb17cbd, 0xe7b82d07, 0x90bf1d91,
    0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de, 0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7,
    0x136c9856, 0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9, 0xfa0f3d63, 0x8d080df5,
    0x3b6e20c8, 0x4c69105e, 0xd56041e4, 0xa2677172, 0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
    0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940, 0x32d86ce3, 0x45df5c75, 0xdcd60dcf, 0xabd13d59,
    0x26d930ac, 0x51de003a, 0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423, 0xcfba9599, 0xb8bda50f,
    0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924, 0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d,
    0x76dc4190, 0x01db7106, 0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f, 0x9fbfe4a5, 0xe8b8d433,
    0x7807c9a2, 0x0f00f934, 0x9609a88e, 0xe10e9818, 0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
    0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e, 0x6c0695ed, 0x1b01a57b, 0x8208f4c1, 0xf50fc457,
    0x65b0d9c6, 0x12b7e950, 0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3, 0xfbd44c65,
    0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2, 0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb,
    0x4369e96a, 0x346ed9fc, 0xad678846, 0xda60b8d0, 0x44042d73, 0x33031de5, 0xaa0a4c5f, 0xdd0d7cc9,
    0x5005713c, 0x270241aa, 0xbe0b1010, 0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
    0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17, 0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad,
    0xedb88320, 0x9abfb3b6, 0x03b6e20c, 0x74b1d29a, 0xead54739, 0x9dd277af, 0x04db2615, 0x73dc1683,
    0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8, 0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1,
    0xf00f9344, 0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb, 0x196c3671, 0x6e6b06e7,
    0xfed41b76, 0x89d32be0, 0x10da7a5a, 0x67dd4acc, 0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
    0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252, 0xd1bb67f1, 0xa6bc5767, 0x3fb506dd, 0x48b2364b,
    0xd80d2bda, 0xaf0a1b4c, 0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55, 0x316e8eef, 0x4669be79,
    0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236, 0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f,
    0xc5ba3bbe, 0xb2bd0b28, 0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31, 0x2cd99e8b, 0x5bdeae1d,
    0x9b64c2b0, 0xec63f226, 0x756aa39c, 0x026d930a, 0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
    0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38, 0x92d28e9b, 0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21,
    0x86d3d2d4, 0xf1d4e242, 0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1, 0x18b74777,
    0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c, 0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45,
    0xa00ae278, 0xd70dd2ee, 0x4e048354, 0x3903b3c2, 0xa7672661, 0xd06016f7, 0x4969474d, 0x3e6e77db,
    0xaed16a4a, 0xd9d65adc, 0x40df0b66, 0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
    0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605, 0xcdd70693, 0x54de5729, 0x23d967bf,
    0xb3667a2e, 0xc4614ab8, 0x5d681b02, 0x2a6f2b94, 0xb40bbe37, 0xc30c8ea1, 0x5a05df1b, 0x2d02ef8d,
};

// 采用crc32算法
uint32_t crc32(uint8_t *d, int n){
    uint32_t crc = 0;
    
    for(int i=0; i < n; i++){
        crc = table[(crc ^ d[i]) & 0xff] ^ (crc >> 8);
    }
    
    return crc ^ 0xffffffff;
}

double rand01(){
    return 1.0*rand()/RAND_MAX;
}

// 曼哈顿距离
uint32_t manhattanDistance(int a,int b,int c, int d){
    return abs(a - c) + abs(b - d);
}

uint32_t manhattanDistance(Pos *a,Pos *b){
    return abs(a->i - b->i) + abs(a->j - b->j);
}

PuzzleData::PuzzleData(int n):_d(nullptr){
    assert(n>=2 && n<=16);
    int nn = n*n;
    _n = n;
    _d = new uint8_t*[n];
    uint8_t* data= new uint8_t[nn];
    for(int i=0,j=0;i<nn;i+=n,j++){
        _d[j] = data + i;
    }
}

PuzzleData::~PuzzleData(){
    if(_d!=nullptr){
        delete _d[0];
//        delete _d;
        _d = nullptr;
    }
}

// 取消移动
bool PuzzleData::unmove(uint8_t dir){
    return move(EXCEPT[dir]);
}

// 显示拼图
void PuzzleData::display(){
    if(_d != nullptr){
        const char *fmt = _n>=10 ? "%03d " : "%02d ";
        for(int i=0;i<_n;i++){
            for(int j=0;j<_n;j++){
                printf(fmt,_d[i][j]);
            }
            printf("\n");
        }
    }
}

uint32_t PuzzleData::hash(){
    return crc32(_d[0],_n*_n);
}

uint32_t PuzzleData::getScore(){
    uint32_t sum = 0;
    
    for(int i=0;i<_n;i++){
        for(int j=0;j<_n;j++){
            int v = _d[i][j];
            if( v ){
                v--;
                int dstPos_i = v/_n - i;
                int dstPos_j = v%_n - j;
                sum += abs(dstPos_i) + abs( dstPos_j);
            }
        }
    }
    return sum + getScore1() + getScore2();
}

// 计算逆序列个数
uint32_t PuzzleData::getScore1(){
    uint32_t sum=0;
    int nn = _n*_n;
    uint8_t* p = _d[0];
    for(int i=0;i<nn;i++){
        int v = p[i];
        if(v){
            for(int j=i+1;j<nn;j++){
                if ( p[j] &&  p[j] < v ){
                    sum++;
                }
            }
        }
    }
    return sum;
}

// 最大移动数
uint32_t PuzzleData::getScore2(){
    uint32_t sum=0;
    Pos curPos;
    int k=0;
    for(int i=0;i<_n;i++){
        for(int j=0;j<_n;j++){
            k++;
            int v = _d[i][j];
            if( v && v!=k){
                curPos.i = i;
                curPos.j = j;
                sum += moveDst(&curPos, v);
            }
        }
    }
    return sum<<1;
}

//  随机移动steps步
void PuzzleData::rand(int steps){
    if(steps>0 && _d != nullptr){
        int k=1;
        int nn = _n * _n;
        for(int i=0;i<_n;i++){
            for(int j=0;j<_n;j++){
                _d[i][j] = k++%nn;
            }
        }
        _0.i = _0.j = _n-1;
        while(steps){
            if ( this->move(::rand()%UNKOWN) ){
                steps--;
            }
        }
    }
}

PuzzleData* PuzzleData::clone(){
    PuzzleData *d = new PuzzleData;
    int nn = _n*_n;
    d->_0 = _0;
    d->_n = _n;
    d->_d = new uint8_t*[_n];
    uint8_t* data= new uint8_t[nn];
    for(int i=0;i<_n;i++){
        d->_d[i] = data + i*_n;
    }
    memcpy(d->_d[0],_d[0],nn);
    return d;
}

uint8_t PuzzleData::moveDst(Pos *curPos,uint8_t v){
    v--;
    
    // 目标位置
    uint8_t dstPos_i = v/_n;
    uint8_t dstPos_j = v%_n;
    Pos dstPos = {dstPos_i - curPos->i ,  dstPos_j - curPos->j};
    
    // 空白位置
    Pos whitePos ={_0.i - curPos->i, _0.j- curPos->j};

    // 数学方向坐标轴顺时针旋转90度。 即使拼图排列方向。原点为当前坐标curPos
    /*
     i 为 横轴  j 为 纵轴
     
             |
     第三象限 |   第二象限
             |
     -------------------> j >0
             |
     第四象限  |  第一象限
             |
             V i>0
     */
    uint8_t x =abs(dstPos.i);
    uint8_t y =abs(dstPos.j);

    uint8_t dif =abs(x-y);
    
    if(dif>0){
        dif+=2;
    }
    
    int sum = MAX(x,y)*6-2-dif;// 移动到目标位置最短步数
    // 空白移动到curpos的步数
    sum += manhattanDistance(curPos,&_0);
    // 将空白调整到curpos附近
    // 以下算法需牢记坐标系方向。 数学坐标系旋转90度
    if(dstPos.i>0 && dstPos.j == 0 ){// 第一象限与第四象限交界
        if(whitePos.i>0 && whitePos.j == 0 ){// 第一象限与第四象限交界
            sum-=1;
        }
        else if(whitePos.i>0 && whitePos.j > 0 ){// 第一象限
            sum-=1;
        }
        else if(whitePos.i==0 && whitePos.j > 0 ){// 第一象限与第二象限交界
            sum+=1;
        }
        else if(whitePos.i<0 && whitePos.j > 0 ){// 第二象限
            sum+=1;
        }
        else if(whitePos.i<0 && whitePos.j == 0 ){// 第二象限与第三象限交界
            sum+=3;
        }
        else if(whitePos.i<0 && whitePos.j < 0 ){// 第三象限
            sum+=1;
        }
        else if(whitePos.i==0 && whitePos.j < 0 ){// 第三象限与第四象限交界
            sum+=1;
        }
        else if(whitePos.i>0 && whitePos.j < 0 ){// 第四象限
            sum-=1;
        }
    }
    else if(dstPos.i>0 && dstPos.j > 0 ){// 第一象限
        if(whitePos.i>0 && whitePos.j == 0 ){// 第一象限与第四象限交界
            if(dstPos.j-dstPos.i>=1){
                sum+=1;
            }
            else{
                sum-=1;
            }
        }
        else if(whitePos.i>0 && whitePos.j > 0 ){// 第一象限
            sum-=1;
        }
        else if(whitePos.i==0 && whitePos.j > 0 ){// 第一象限与第二象限交界
            if(dstPos.i-dstPos.j>=1){
                sum+=1;
            }
            else{
                sum-=1;
            }
        }
        else if(whitePos.i<0 && whitePos.j > 0 ){// 第二象限
            if(x-y>=1){
                sum+=1;
            }
            else{
                sum-=1;
            }
        }
        else if(whitePos.i<0 && whitePos.j == 0 ){// 第二象限与第三象限交界
            sum+=1;
        }
        else if(whitePos.i<0 && whitePos.j < 0 ){// 第三象限
            sum+=1;
        }
        else if(whitePos.i==0 && whitePos.j < 0 ){// 第三象限与第四象限交界
            sum+=1;
        }
        else if(whitePos.i>0 && whitePos.j < 0 ){// 第四象限
            if(dstPos.j-dstPos.i>=1){
                sum+=1;
            }
            else{
                sum-=1;
            }
        }
    }
    else if(dstPos.i==0 && dstPos.j > 0 ){// 第一象限与第二象限交界
        if(whitePos.i>0 && whitePos.j == 0 ){// 第一象限与第四象限交界
            sum+=1;
        }
        else if(whitePos.i>0 && whitePos.j > 0 ){// 第一象限
            sum-=1;
        }
        else if(whitePos.i==0 && whitePos.j > 0 ){// 第一象限与第二象限交界
            sum-=1;
        }
        else if(whitePos.i<0 && whitePos.j > 0 ){// 第二象限
            sum-=1;
        }
        else if(whitePos.i<0 && whitePos.j == 0 ){// 第二象限与第三象限交界
            sum+=1;
        }
        else if(whitePos.i<0 && whitePos.j < 0 ){// 第三象限
            sum+=1;
        }
        else if(whitePos.i==0 && whitePos.j < 0 ){// 第三象限与第四象限交界
            sum+=3;
        }
        else if(whitePos.i>0 && whitePos.j < 0 ){// 第四象限
            sum+=1;
        }
    }
    else if(dstPos.i<0 && dstPos.j > 0 ){// 第二象限
        if(whitePos.i>0 && whitePos.j == 0 ){// 第一象限与第四象限交界
            sum+=1;
        }
        else if(whitePos.i>0 && whitePos.j > 0 ){// 第一象限
            if(x-y>=1){
                sum+=1;
            }
            else{
                sum-=1;
            }
        }
        else if(whitePos.i==0 && whitePos.j > 0 ){// 第一象限与第二象限交界
            if(x-y>=1){
                sum+=1;
            }
            else{
                sum-=1;
            }
        }
        else if(whitePos.i<0 && whitePos.j > 0 ){// 第二象限
            sum-=1;
        }
        else if(whitePos.i<0 && whitePos.j == 0 ){// 第二象限与第三象限交界
            if(y-x>=1){
                sum+=1;
            }
            else{
                sum-=1;
            }
        }
        else if(whitePos.i<0 && whitePos.j < 0 ){// 第三象限
            if(y-x>=1){
                sum+=1;
            }
            else{
                sum-=1;
            }
        }
        else if(whitePos.i==0 && whitePos.j < 0 ){// 第三象限与第四象限交界
            sum+=1;
        }
        else if(whitePos.i>0 && whitePos.j < 0 ){// 第四象限
            sum+=1;
        }
    }
    else if(dstPos.i<0 && dstPos.j == 0 ){// 第二象限与第三象限交界
        if(whitePos.i>0 && whitePos.j == 0 ){// 第一象限与第四象限交界
            sum+=3;
        }
        else if(whitePos.i>0 && whitePos.j > 0 ){// 第一象限
            sum+=1;
        }
        else if(whitePos.i==0 && whitePos.j > 0 ){// 第一象限与第二象限交界
            sum+=1;
        }
        else if(whitePos.i<0 && whitePos.j > 0 ){// 第二象限
            sum-=1;
        }
        else if(whitePos.i<0 && whitePos.j == 0 ){// 第二象限与第三象限交界
            sum-=1;
        }
        else if(whitePos.i<0 && whitePos.j < 0 ){// 第三象限
            sum-=1;
        }
        else if(whitePos.i==0 && whitePos.j < 0 ){// 第三象限与第四象限交界
            sum+=1;
        }
        else if(whitePos.i>0 && whitePos.j < 0 ){// 第四象限
            sum+=1;
        }
    }
    else if(dstPos.i<0 && dstPos.j < 0 ){// 第三象限
        if(whitePos.i>0 && whitePos.j == 0 ){// 第一象限与第四象限交界
            sum+=1;
        }
        else if(whitePos.i>0 && whitePos.j > 0 ){// 第一象限
            sum+=1;
        }
        else if(whitePos.i==0 && whitePos.j > 0 ){// 第一象限与第二象限交界
            sum+=1;
        }
        else if(whitePos.i<0 && whitePos.j > 0 ){// 第二象限
            if(y-x>=1){
                sum+=1;
            }
            else{
                sum-=1;
            }
        }
        else if(whitePos.i<0 && whitePos.j == 0 ){// 第二象限与第三象限交界
            if(y-x>=1){
                sum+=1;
            }
            else{
                sum-=1;
            }
        }
        else if(whitePos.i<0 && whitePos.j < 0 ){// 第三象限
            sum-=1;
        }
        else if(whitePos.i==0 && whitePos.j < 0 ){// 第三象限与第四象限交界
            if(x-y>=1){
                sum+=1;
            }
            else{
                sum-=1;
            }
        }
        else if(whitePos.i>0 && whitePos.j < 0 ){// 第四象限
            if(x-y>=1){
                sum+=1;
            }
            else{
                sum-=1;
            }
        }
    }
    else if(dstPos.i==0 && dstPos.j < 0 ){// 第三象限与第四象限交界
        if(whitePos.i>0 && whitePos.j == 0 ){// 第一象限与第四象限交界
            sum+=1;
        }
        else if(whitePos.i>0 && whitePos.j > 0 ){// 第一象限
            sum+=1;
        }
        else if(whitePos.i==0 && whitePos.j > 0 ){// 第一象限与第二象限交界
            sum+=3;
        }
        else if(whitePos.i<0 && whitePos.j > 0 ){// 第二象限
            sum+=1;
        }
        else if(whitePos.i<0 && whitePos.j == 0 ){// 第二象限与第三象限交界
            sum+=1;
        }
        else if(whitePos.i<0 && whitePos.j < 0 ){// 第三象限
            sum-=1;
        }
        else if(whitePos.i==0 && whitePos.j < 0 ){// 第三象限与第四象限交界
            sum-=1;
        }
        else if(whitePos.i>0 && whitePos.j < 0 ){// 第四象限
            sum-=1;
        }
    }
    else if(dstPos.i>0 && dstPos.j < 0 ){// 第四象限
        if(whitePos.i>0 && whitePos.j == 0 ){// 第一象限与第四象限交界
            if(y-x>=1){
                sum+=1;
            }
            else{
                sum-=1;
            }
        }
        else if(whitePos.i>0 && whitePos.j > 0 ){// 第一象限
            if(y-x>=1){
                sum+=1;
            }
            else{
                sum-=1;
            }
        }
        else if(whitePos.i==0 && whitePos.j > 0 ){// 第一象限与第二象限交界
            sum+=1;
        }
        else if(whitePos.i<0 && whitePos.j > 0 ){// 第二象限
            sum+=1;
        }
        else if(whitePos.i<0 && whitePos.j == 0 ){// 第二象限与第三象限交界
            sum+=1;
        }
        else if(whitePos.i<0 && whitePos.j < 0 ){// 第三象限
            if(x-y>=1){
                sum+=1;
            }
            else{
                sum-=1;
            }
        }
        else if(whitePos.i==0 && whitePos.j < 0 ){// 第三象限与第四象限交界
            if(x-y>=1){
                sum+=1;
            }
            else{
                sum-=1;
            }
        }
        else if(whitePos.i>0 && whitePos.j < 0 ){// 第四象限
            sum-=1;
        }
    }
    
    return sum;
}

bool PuzzleData::canmove(uint8_t dir){
    switch (dir) {
        case UP: return _0.i>0;
        case DOWN: return _0.i<_n-1;
        case LEFT: return _0.j>0;
        case RIGHT: return _0.j<_n-1;
    }
    return false;
}

bool PuzzleData::move(uint8_t dir){
    int i =_0.i, j =_0.j;
    switch (dir) {
        case UP:
            if(i>0){
                _d[i][j] = _d[i-1][j];
                _d[i-1][j]=0;
                _0.i--;
                return true;
            }
            
        case DOWN:
            if(i<_n-1){
                _d[i][j] = _d[i+1][j];
                _d[i+1][j]=0;
                _0.i++;
                return true;
            }
            break;
            
        case LEFT:
            if(j>0){
                _d[i][j] = _d[i][j-1];
                _d[i][j-1]=0;
                _0.j--;
                return true;
            }
            
        case RIGHT:
            if(j<_n-1){
                _d[i][j] = _d[i][j+1];
                _d[i][j+1]=0;
                _0.j++;
                return true;
            }
    }
    
    return false;
}
