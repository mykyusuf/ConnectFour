/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConnectFourUndo.h
 * Author: MacbookPro
 *
 * Created on 27 Kasım 2017 Pazartesi, 23:08
 */

#ifndef CONNECTFOURUNDO_H
#define CONNECTFOURUNDO_H

#include "ConnectFourPlus.h"
#include <fstream>
class ConnectFourUndo: public ConnectFourPlus {
public:
    
    ConnectFourUndo():ConnectFourPlus(){}
    ConnectFourUndo(int x,int y):ConnectFourPlus(x,y){}

    int finish(const int h,const int w);
    
    void undo(char c);
    
    void yap(string f,int h,int w,int &n);
    
    void playGame();
    
    int playC();
    
    void convert(string f);
};




#endif /* CONNECTFOURUNDO_H */

