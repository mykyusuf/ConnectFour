/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ConnectFourUndo.cpp
 * Author: MacbookPro
 * 
 * Created on 27 Kasım 2017 Pazartesi, 23:08
 */

#include "ConnectFourUndo.h"

int ConnectFourUndo::finish(const int h, const int w){
    
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

void ConnectFourUndo::undo(char c){
    
    
    ofstream save("undo.txt", std::ios_base::app | std::ios_base::out);
    
    if(save.is_open()){
       
        save<<c<<endl;
        
        save.close();
    }    
    
}

void ConnectFourUndo::yap(string f,int h,int w,int &n){
        
    string line;
    ifstream load(f);
    ofstream save("yap.txt");
    
    int j=0,i=0;
    int tuth=h;
    int tutw=w;
    
    if(n>0){
        emptyBoard(h,w);
        turn=0;

        while(j<n-1){
            getline(load,line);
            save<<line<<endl;
            tutw=line[0]-65;
            for(i=gameSizeH-1;gameCells[i][tutw].getwho() !='.' && i>0;i--);
            play(i,line[0]);
            j++;
        } 

        n--;  
        save.close();
        load.close();
        convert(f);
   
    }
    else
        cerr<<"You Cant Undo!"<<endl;
}
void ConnectFourUndo::convert(string f){
    
    string line;
    ofstream load(f);
    ifstream save("yap.txt");
    
    while(getline(save,line)){
        load<<line<<endl;
    }
    save.close();
    load.close();
}
void ConnectFourUndo::playGame(){

    char k;
    int win=0,i=0,ok=0;
    string t;
    int w;
    int n=0;
    
    cout<<"Do you want to play with C/P? : ";
    cin>>k;
   

    if(k=='P' || k=='C'){
    
        //Ana Oyun Dongusu
        
        while(win==0){
        
            printBoard(gameSizeH,gameSizeW);

            cout<<"Player 1: ";
            
            cin>>t;                 
           
            while(t=="LOAD"){
                        newSize("myk.txt");
                        printBoard(gameSizeH,gameSizeW);
                        cout<<"Player 1: ";
                        cin>>t;
            }
            while(t=="SAVE"){
                        saveFile(gameSizeH,gameSizeW,k,"p1");
                        printBoard(gameSizeH,gameSizeW);
                        cout<<"Player 1: ";
                        cin>>t;
            }
            if(t=="UNDO"){
                        yap("undo.txt",gameSizeH,gameSizeW,n);
                        
            }
            else{
                w=t[0]-65;
                
                while(w>gameSizeW-1){
                    cerr<<"Wrong İnput ! Try again: ";
                    cin>>t;
                    w=t[0]-65;

                }


                ok=0;

                while(ok==0){

                    for(i=gameSizeH-1;gameCells[i][w].getwho() !='.' && i>0;i--);

                    if(i==0){
                        cerr<<"You cant play this column ! Try again: ";
                        cin>>t;
                        w=t[0]-65;
                    }
                    else
                        ok=1;
                }

                play(i,t[0]);
                undo(t[0]);

                win=finish(gameSizeH-1,gameSizeW);

                if(win==0){
                    
                n++;
            
                printBoard(gameSizeH,gameSizeW);
            
                cout<<"Player 2: ";
                            
                if(k=='P'){
                    
                    cin>>t;
                    
                    while(t=="LOAD"){
                        newSize("myk.txt");
                        printBoard(gameSizeH,gameSizeW);
                        cout<<"Player 2: ";
                        cin>>t;
                    }
                    while(t=="SAVE"){
                        saveFile(gameSizeH,gameSizeW,k,"p2");
                        printBoard(gameSizeH,gameSizeW);
                        cout<<"Player 2: ";
                        cin>>t;
                    }
                    if(t=="UNDO"){
                        yap("undo.txt",gameSizeH,gameSizeW,n);
                       
                    }
                    else{
                    w=t[0]-65;
                        
                    while(w>gameSizeW-1){
                            cerr<<"Wrong İnput ! Try again: ";
                            cin>>t;
                            w=t[0]-65;

                        }

                    ok=0;

                    while(ok==0){


                            for(i=gameSizeH-1; gameCells[i][w].getwho() !='.' && i>0;i--);

                            if(i==0){
                                cerr<<"You cant play this column ! Try again: ";
                                cin>>t;
                                w=t[0]-65;
                            }
                            else
                                ok=1;
                        }
        
                    play(i,t[0]);
                    undo(t[0]);
                    }
                    
                }
                else if(k=='C'){
                    cout<<endl;
                    playC();
                    turn++;
                }
                win=finish(gameSizeH-1,gameSizeW);
                n++;
              
            }
            }
        }
        printBoard(gameSizeH,gameSizeW);
        // Oyunun Sonucu
        
        if(win==1)
            cout<<"Player1 Won !"<<endl;
        else if(win==2 && k=='P')
            cout<<"Player2 Won !"<<endl;
        else if(win==2 && k=='C')
            cout<<"Computer Won !"<<endl;
        else
            cout<<"Draw !"<<endl;
    }
    else
        cerr<<"Wrong Input Type !"<<endl;

}
int ConnectFourUndo::playC(){
    
    int var=0,i,j;
        
    for(i=gameSizeH-1;i>0;i--){
        
        for(j=0;j<gameSizeW-3;j++){
            
            if(gameCells[i][j].getwho()=='O')
                var+=1;
            if(gameCells[i][j+1].getwho()=='O')
                var+=1;
            if(gameCells[i][j+2].getwho()=='O')
                var+=1;
            if(gameCells[i][j+3].getwho()=='O')
                var+=1;
            
            if(var==3){
                for(int m=0;m<4;m++){
                    if(gameCells[i][j+m].getwho()=='.'&& gameCells[i+1][j+m].getwho()!='.'){
                        gameCells[i][j+m].setwho('O');
                        undo(gameCells[i][j+m].getc());
                        return 1;
                    }
                }
            }
            var=0;
         
        }
        
    }
    
    for(i=gameSizeH-1;i>3;i--){
        
        for(j=gameSizeW-1;j>=0;j--){
            
            
            if(gameCells[i][j].getwho()=='O')
                var+=1;
            if(gameCells[i-1][j].getwho()=='O')
                var+=1;
            if(gameCells[i-2][j].getwho()=='O')
                var+=1;
            if(gameCells[i-3][j].getwho()=='O')
                var+=1;
            
            if(var==3){
                for(int m=0;m<4;m++){
                    if(gameCells[i-m][j].getwho()=='.'&& gameCells[i-m+1][j].getwho()!='.'){
                        gameCells[i-m][j].setwho('O');
                        undo(gameCells[i-m][j].getc());
                        return 1;
                    }
                }
            }
            var=0;
            
        }
        
        
    }
    for(i=gameSizeH-1;i>3;i--){
        
        for(j=0;j<gameSizeW-3;j++){
            
            
            if(gameCells[i][j].getwho()=='O')
                var+=1;
            if(gameCells[i-1][j+1].getwho()=='O')
                var+=1;
            if(gameCells[i-2][j+2].getwho()=='O')
                var+=1;
            if(gameCells[i-3][j+3].getwho()=='O')
                var+=1;
            
            if(var==3){
                for(int m=0;m<4;m++){
                    if(gameCells[i-m][j+m].getwho()=='.' && gameCells[i-m+1][j+m].getwho()!='.'){
                        
                        gameCells[i-m][j+m].setwho('O');
                        undo(gameCells[i-m][j+m].getc());
                        return 1;
                    }
                }
            }
            var=0;
            
        }
        
        
    }
    for(i=gameSizeH-1;i>3;i--){
        
        for(j=gameSizeW-1;j>2;j--){
            
            
            if(gameCells[i][j].getwho()=='O')
                var+=1;
            if(gameCells[i-1][j-1].getwho()=='O')
                var+=1;
            if(gameCells[i-2][j-2].getwho()=='O')
                var+=1;
            if(gameCells[i-3][j-3].getwho()=='O')
                var+=1;
            
            if(var==3){
                for(int m=0;m<4;m++){
                    if(gameCells[i-m][j-m].getwho()=='.' && gameCells[i-m+1][j+m].getwho()!='.'){
                        gameCells[i-m][j-m].setwho('O');
                        undo(gameCells[i-m][j-m].getc());
                        return 1;
                    }
                }
            }
            var=0;
            
        }
        
        
    }
    for(i=gameSizeH-1;i>3;i--){
        
        for(j=gameSizeW-1;j>=0;j--){
            
            
            if(gameCells[i][j].getwho()=='X')
                var+=1;
            if(gameCells[i-1][j].getwho()=='X')
                var+=1;
            if(gameCells[i-2][j].getwho()=='X')
                var+=1;
            if(gameCells[i-3][j].getwho()=='X')
                var+=1;
            
            if(var==3){
                for(int m=0;m<4;m++){
                    if(gameCells[i-m][j].getwho()=='.' && gameCells[i-m+1][j].getwho()!='.'){
                        gameCells[i-m][j].setwho('O');
                        undo(gameCells[i-m][j].getc());
                        return 1;
                    }
                }
            }
            var=0;
            
        }
        
        
    }
    for(i=gameSizeH-1;i>0;i--){
        
        for(j=0;j<gameSizeW-3;j++){
            
            if(gameCells[i][j].getwho()=='X')
                var+=1;
            if(gameCells[i][j+1].getwho()=='X')
                var+=1;
            if(gameCells[i][j+2].getwho()=='X')
                var+=1;
            if(gameCells[i][j+3].getwho()=='X')
                var+=1;
                                

            if(var==3){
                for(int m=0;m<4;m++){
                    if((i==gameSizeH-1 && gameCells[i][j+m].getwho()=='.' ) ||(gameCells[i][j+m].getwho()=='.'&& gameCells[i+1][j+m].getwho()!='.' && i<gameSizeH-1) ){
                        gameCells[i][j+m].setwho('O');
                        undo(gameCells[i][j+m].getc());
                        return 1;
                    }
                }
            }
            var=0;
         
        }
        
    }
    
    for(i=gameSizeH-1;i>3;i--){
        
        for(j=gameSizeW-1;j>2;j--){
            
            
            if(gameCells[i][j].getwho()=='X')
                var+=1;
            if(gameCells[i-1][j-1].getwho()=='X')
                var+=1;
            if(gameCells[i-2][j-2].getwho()=='X')
                var+=1;
            if(gameCells[i-3][j-3].getwho()=='X')
                var+=1;
            
            if(var==3){
                for(int m=0;m<4;m++){
                    if(gameCells[i-m][j-m].getwho()=='.' && gameCells[i-m+1][j-m].getwho()!='.'){
                        gameCells[i-m][j-m].setwho('O');
                        undo(gameCells[i-m][j-m].getc());
                        return 1;
                    }
                }
            }
            var=0;
            
        }
        
        
    }
    
    
    for(i=gameSizeH-1;i>3;i--){
        
        for(j=0;j<gameSizeW-3;j++){
            
            
            if(gameCells[i][j].getwho()=='X')
                var+=1;
            if(gameCells[i-1][j+1].getwho()=='X')
                var+=1;
            if(gameCells[i-2][j+2].getwho()=='X')
                var+=1;
            if(gameCells[i-3][j+3].getwho()=='X')
                var+=1;
            
            if(var==3){
                for(int m=0;m<4;m++){
                    if(gameCells[i-m][j+m].getwho()=='.' && gameCells[i-m+1][j+m].getwho()!='.'){
                        
                        gameCells[i-m][j+m].setwho('O');
                        undo(gameCells[i-m][j+m].getc());
                        return 1;
                    }
                }
            }
            var=0;
            
        }
        
        
    }

    
    for(i=gameSizeH-1;i>0;i--){
        
        for(j=0;j<gameSizeW-1;j++){
            
            if(gameCells[i][j].getwho()=='O'){
                
                if( (gameCells[i-1][j].getwho()=='.'&&i==gameSizeH-1 && gameCells[i][j+1].getwho()!='O') || (gameCells[i-1][j].getwho()=='.'&& i<gameSizeH-1 && gameCells[i][j].getwho()!='.' && gameCells[i][j+1].getwho()!='O')) {
                    gameCells[i-1][j].setwho('O');
                    undo(gameCells[i-1][j].getc());
                    return 1;
                }
                
                else if( ( j>0&&gameCells[i][j-1].getwho()=='.'&&i==gameSizeH-1 )|| (j>0&&gameCells[i][j-1].getwho()=='.'&& i<gameSizeH-1 &&gameCells[i+1][j].getwho()!='.' ) ){
                    gameCells[i][j-1].setwho('O');
                    undo(gameCells[i][j-1].getc());
                    return 1;
                }
                else if( ( gameCells[i][j+1].getwho()=='.'&&i==gameSizeH-1 ) || (gameCells[i][j+1].getwho()=='.'&& i<gameSizeH-1 && gameCells[i+1][j+1].getwho()!='.' ) ){
                    gameCells[i][j+1].setwho('O');
                    undo(gameCells[i][j+1].getc());
                    return 1;
                }
            }
            
        }
        
    }
    for(i=gameSizeH-1;i>0;i--){
        
        for(j=0;j<gameSizeW-1;j++){
            
            if(gameCells[i][j].getwho()=='X'){
                
                if( (gameCells[i-1][j].getwho()=='.'&&i==gameSizeH-1 && gameCells[i][j+1].getwho()!='O') || (gameCells[i-1][j].getwho()=='.'&& i<gameSizeH-1 && gameCells[i][j].getwho()!='.' && gameCells[i][j+1].getwho()!='O')) {
                    gameCells[i-1][j].setwho('O');
                    undo(gameCells[i-1][j].getc());
                    return 1;
                }
                
                else if( ( j>0&&gameCells[i][j-1].getwho()=='.'&&i==gameSizeH-1 )|| (j>0&&gameCells[i][j-1].getwho()=='.'&& i<gameSizeH-1 &&gameCells[i+1][j].getwho()!='.' ) ){
                    gameCells[i][j-1].setwho('O');
                    undo(gameCells[i][j-1].getc());
                    return 1;
                }
                else if( ( gameCells[i][j+1].getwho()=='.'&&i==gameSizeH-1 ) || (gameCells[i][j+1].getwho()=='.'&& i<gameSizeH-1 && gameCells[i+1][j+1].getwho()!='.' ) ){
                    gameCells[i][j+1].setwho('O');
                    undo(gameCells[i][j+1].getc());
                    return 1;
                }
            }
            
        }
        
    }
    
    return 0;
    
}
