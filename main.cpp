//
//  main.cpp
//  拼图AI2
//
//  Created by 邓中强 on 2019/3/21.
//  Copyright © 2019 邓中强. All rights reserved.
//

#include <iostream>
#include "logic.hpp"
#include <time.h>
#include <stack>

extern const char *DESC[];

int main(int argc, const char * argv[]) {
    std::stack<uint8_t> result;
    
    for(uint8_t i=2;i<=6;i++){
        Puzzle p(i);
        
        printf("%d x %d 的拼图：\n", i,i);
        p.display();
        
        printf("%d x %d 拼图最优解：\n",i,i);
        
        p.resove(result);
        int step = 0;
        while(!result.empty()){
            uint8_t dir = result.top();
            result.pop();
            if(step++%5 == 0){
                printf("\n%d:",step);
            }
            printf("%s",DESC[dir]);
        }
        printf("\n");
    }
    
    // insert code here...
    
    return 0;
}
