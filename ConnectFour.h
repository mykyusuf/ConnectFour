/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConnectFour.h
 * Author: MacbookPro
 *
 * Created on 19 Ekim 2017 Perşembe, 22:27
 */

#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H
#include <vector>
#include <string>
#include <iostream>
#include "Cell.h"

using namespace std;

class ConnectFour {
    
public:
    ConnectFour();
    //ConnectFour(char m);
    ConnectFour(int n , int m);

    ~ConnectFour();
    
    //void playMulti(); //Multi modu
    void newSize(string f);
    
    void emptyBoard(int h,int w); //Bos tahta tanımlar
    
    void loadFile(string f,int h,int w);//Kaydedilmis oyunu yukleyen fonsiyon

    void saveFile(const int h, const int w,const char p,string t);//Oyunu kaydeden fonksiyon
    
    int turn; //Oyuncu sırasını tutar
            
    int rtrW(); //Value degerini doner
    int rtrH(); //Value degerini doner
     
    Cell** gameCells;         
    
    virtual void playGame(); // Ana oyun dongusu

protected:
    
    virtual int finish(const int h,const int w)=0;//Oyunun bitip bitmedigini kontrol eden fonksiyon
    
    void printBoard(const int h,const int w);//Oyun tahtasını ekrana basan fonksiyon
    
    virtual int playC(); // computer icin hamle yapar
    
    int play(int pos,char c); //Player icin hamle yapar
        
    int gameSizeH=0,gameSizeW=0; //Board Size
    
    char wh; //Oyun profilini tutar
        
};

#endif /* CONNECTFOUR_H */

