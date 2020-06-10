/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cell.h
 * Author: MacbookPro
 *
 * Created on 27 Kasım 2017 Pazartesi, 23:25
 */

#ifndef CELL_H
#define CELL_H

class Cell{
        
    public:
        
        //Cell tanımlama constructorları
        Cell(){ pos = 0; c = 'A'; who = '.'; };
        Cell(int pos , char c){
            this->pos = pos;
            this->c = c;
            
                
        };
        Cell(int pos , char c , char who){
            this->pos = pos;
            this->c = c;
            this->who = who;
        };
        
        inline void setc(char c){
            this->c = c;
        };
        inline void setpos(int pos){
            this->pos = pos;
        };
        inline char getc(){return c;};
        inline int getpos(){return pos;};
        inline void setwho(char who){
            this->who = who;
        };
        inline char getwho(){return who;
        };
        
    private:
        char c; //Sutun 
        int pos; // Satır
        char who; // Kim oldugu
        
        
    };
    

#endif /* CELL_H */

