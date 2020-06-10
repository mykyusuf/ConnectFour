/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConnectFourPlus.cpp
 * Author: MacbookPro
 * 
 * Created on 27 Kasım 2017 Pazartesi, 23:05
 */

#include "ConnectFourPlus.h"

int ConnectFourPlus::finish(const int h, const int w){
    
    int var=0,i,j;
        
    for(i=h;i>0;i--){
        
        for(j=0;j<w-3;j++){
            
            if(gameCells[i][j].getwho()=='O')
                var+=1;
            if(gameCells[i][j+1].getwho()=='O')
                var+=1;
            if(gameCells[i][j+2].getwho()=='O')
                var+=1;
            if(gameCells[i][j+3].getwho()=='O')
                var+=1;
            
            if(var==4){
                return 2;
            }
            var=0;
         
        }
        
    }
    for(i=h;i>3;i--){
        
        for(j=w-1;j>=0;j--){
            
            
            if(gameCells[i][j].getwho()=='O')
                var+=1;
            if(gameCells[i-1][j].getwho()=='O')
                var+=1;
            if(gameCells[i-2][j].getwho()=='O')
                var+=1;
            if(gameCells[i-3][j].getwho()=='O')
                var+=1;
            
            if(var==4){
                return 2;
            }
            var=0;
            
        }
        
        
    }
    
    for(i=h;i>3;i--){
        
        for(j=w-1;j>=0;j--){
            
            
            if(gameCells[i][j].getwho()=='X')
                var+=1;
            if(gameCells[i-1][j].getwho()=='X')
                var+=1;
            if(gameCells[i-2][j].getwho()=='X')
                var+=1;
            if(gameCells[i-3][j].getwho()=='X')
                var+=1;
            
            if(var==4){
                return 1;
            }
            var=0;
            
        }
        
        
    }
    for(i=h;i>0;i--){
        
        for(j=0;j<w-3;j++){
            
            if(gameCells[i][j].getwho()=='X')
                var+=1;
            if(gameCells[i][j+1].getwho()=='X')
                var+=1;
            if(gameCells[i][j+2].getwho()=='X')
                var+=1;
            if(gameCells[i][j+3].getwho()=='X')
                var+=1;
            
            if(var==4){
                return 1;
            }
            var=0;
         
        }
        
    }
    return 0;
    
}
