/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConnectFourDiag.h
 * Author: MacbookPro
 *
 * Created on 27 Kasım 2017 Pazartesi, 23:07
 */

#ifndef CONNECTFOURDIAG_H
#define CONNECTFOURDIAG_H

#include "ConnectFour.h"

class ConnectFourDiag: public ConnectFour {
public:
    
    ConnectFourDiag():ConnectFour(){}
    ConnectFourDiag(int x,int y):ConnectFour(x,y){}

    virtual int finish(const int h,const int w);
    
};


#endif /* CONNECTFOURDIAG_H */

