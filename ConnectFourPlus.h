/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConnectFourPlus.h
 * Author: MacbookPro
 *
 * Created on 27 Kasım 2017 Pazartesi, 23:05
 */

#ifndef CONNECTFOURPLUS_H
#define CONNECTFOURPLUS_H
#include "ConnectFour.h"

class ConnectFourPlus: public ConnectFour {
public:
    
    ConnectFourPlus():ConnectFour(){}
    ConnectFourPlus(int x,int y):ConnectFour(x,y){}

    int finish(const int h,const int w);
    
};


#endif /* CONNECTFOURPLUS_H */

