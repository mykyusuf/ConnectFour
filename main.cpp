/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: MacbookPro
 *
 * Created on 19 Ekim 2017 Perşembe, 22:26
 */

#include <cstdlib>
#include "ConnectFour.h"
#include "ConnectFourUndo.h"
#include "ConnectFourDiag.h"
#include "ConnectFourPlus.h"
#include "Cell.h"
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {    
       
    char c,g;
    string w;
    int w2,h2,h;
    int f=1;

        cout<<"Enter Board Width: ";
        cin>>w;
        w2=(w[0])-48;
        if(w2<0||w2>9);
        else{
            cout<<"Enter Board Height: ";
            cin>>h;
            h2=h;
            w2=stoi(w);
                ConnectFour *p = new ConnectFourUndo(h2,w2);
                 p->playGame();
        }

    
    return 0;
}

