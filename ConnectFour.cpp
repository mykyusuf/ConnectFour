#include <iostream>
#include <fstream>
#include <cstdlib>

#include "ConnectFour.h"

ConnectFour::~ConnectFour() {
    
    for (int i = 0; i < gameSizeH; ++i)
        delete [] gameCells[i];
    delete [] gameCells;
    
}
ConnectFour::ConnectFour() {
    gameSizeH = 6;
    gameSizeW = 5;
    
    //gelen degere gore gameCells olusturulur
    
    gameCells = new Cell*[gameSizeH];
    for (int i = 0; i < gameSizeH; ++i)
        gameCells[i] = new Cell[gameSizeW];
           
    turn=0;
    
    //Bos board olusturur
    
    emptyBoard(gameSizeH,gameSizeW);
    
}
ConnectFour::ConnectFour(int n , int m) {
    gameSizeH = n+1;
    gameSizeW = m;
    
    //gelen degere gore gameCells olusturulur
    
    gameCells = new Cell*[gameSizeH];
    for (int i = 0; i < gameSizeH; ++i)
        gameCells[i] = new Cell[gameSizeW];
           
    turn=0;
    
    //Bos board olusturur
    
    emptyBoard(gameSizeH,gameSizeW);

}
void ConnectFour::loadFile(string f,int h,int w){ //Dosyadan board okuma yapar
    
    string line;
    ifstream load(f);
    int j,i=0;
    int tuth=h;
    int tutw=w;
    getline(load,line);
    w=line.size();
    
    if(w==0){
        cerr<<"Txt Cant Found !";
        load.close();
        w=tutw;
        h=tuth;
        
    }
    
    else{
        
        load.close();
        load.open(f);
    
        if(load.is_open()){
        
                   
            while(getline(load,line) && i<h){
            
            
                for(j=0;j<w;j++){
                
                    gameCells[i][j].setwho(line[j]);
                
                }
                i++;
            }
                

            load.close();
        }
    }
    
}

void ConnectFour::saveFile(const int h, const int w,const char p,string t){ // Dosyaya o anki oyunu kaydeder
    
    ofstream save("myk.txt");
    
    if(save.is_open()){
        for(int i=0;i<h;i++){
            for(int j=0;j<w;j++){
                save<<gameCells[i][j].getwho();
                
            }
            save<<endl;
        }
        
        if(p=='P')
            save<<"P1 vs P2 played on "<<h<<"x"<<w<<" board."<<endl;
        else
            save<<"P1 vs COM played on "<<h<<"x"<<w<<" board."<<endl;
        
        if(t=="p1")
            save<<"P1: PLAYER 1 SAVED GAME."<<endl;
        else
            save<<"P2: PLAYER 2 SAVED GAME."<<endl;
        
        save.close();
    }
    
}

void ConnectFour::printBoard(const int h,const int w){ //Tahtayı ekrana basar
    
        for(int i=0;i<h;i++){
            for(int j=0;j<w;j++){
                cout<<gameCells[i][j].getwho();
            }
            cout<<endl;
        }       
}

void ConnectFour::emptyBoard(int h, int w){ //Bos tahta tanımlar
    
    char x;
    for(int i=0;i<w;i++){
        x=65+i;
        (gameCells[0][i]).setwho(x);
    }
    for(int i=1;i<h;i++){
        for(int j=0;j<w;j++)
            (gameCells[i][j]).setwho('.');
        
    }
    
}

void ConnectFour::newSize(string f){

    string line;
    ifstream load(f);
    
    int h;
    int w;
    int say=0;
    
    //dosyadan okumak icin dosyadaki sutun sayısını bulur
    
    getline(load,line);
    w=line.size();
    
    if(w==0)
        cerr<<"Txt Not Found! "<<endl,load.close();
    else{
    
        while(getline(load,line))
            say++;
    
        h=say-2;
    
        gameSizeH = h+1;
        gameSizeW = w;
    
        //gelen degere gore gameCells olusturulur
    
        gameCells = new Cell*[gameSizeH];
        for (int i = 0; i < gameSizeH; ++i)
            gameCells[i] = new Cell[gameSizeW];
           
        turn=0;
        
        //Dosyadan oyunu yukler
    
        loadFile(f,gameSizeH,gameSizeW);
    
    }

    
}

void ConnectFour::playGame(){ //Oyunun dondugu dongu
    
    char k;
    int win=0,i=0,ok=0;
    string t;
    int w;
    
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
                        saveFile(gameSizeH,gameSizeW,k,"p2");
                        printBoard(gameSizeH,gameSizeW);
                        cout<<"Player 1: ";
                        cin>>t;
            }
            
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

                win=finish(gameSizeH-1,gameSizeW);

                if(win==0){
            
                printBoard(gameSizeH,gameSizeW);
            
                cout<<"Player 2: ";
                            
                if(k=='P'){
                    
                    cin>>t;
                    
                    while(t=="LOAD"){
                        newSize("myk.txt");
                        printBoard(gameSizeH,gameSizeW);
                        cout<<"Player 2: ";
                        turn++;
                        cin>>t;
                    }
                    while(t=="SAVE"){
                        saveFile(gameSizeH,gameSizeW,k,"p2");
                        printBoard(gameSizeH,gameSizeW);
                        cout<<"Player 2: ";
                        turn++;
                        cin>>t;
                    }
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
                    
                }
                else if(k=='C'){
                    cout<<endl;
                    playC();
                    turn++;
                }
                win=finish(gameSizeH-1,gameSizeW);
              
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

int ConnectFour::rtrW(){ // total live cell sayısını doner
    
    return gameSizeW;
    
}
int ConnectFour::rtrH(){ // total live cell sayısını doner
    
    return gameSizeH-1;
    
}
int ConnectFour::play(int pos, char c){ //Playerın yolladıgı degeri oynar
    
    int w=c-65;
    
    if(turn%2==0){
        gameCells[pos][w].setwho('X');
        turn++;
    }
    else{
        gameCells[pos][w].setwho('O');
        turn++;
    }
    
    return 0;
}

int ConnectFour::playC(){ // Computer icin hamle yapar
    
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
                    return 1;
                }
                
                else if( ( j>0&&gameCells[i][j-1].getwho()=='.'&&i==gameSizeH-1 )|| (j>0&&gameCells[i][j-1].getwho()=='.'&& i<gameSizeH-1 &&gameCells[i+1][j].getwho()!='.' ) ){
                    gameCells[i][j-1].setwho('O');
                    return 1;
                }
                else if( ( gameCells[i][j+1].getwho()=='.'&&i==gameSizeH-1 ) || (gameCells[i][j+1].getwho()=='.'&& i<gameSizeH-1 && gameCells[i+1][j+1].getwho()!='.' ) ){
                    gameCells[i][j+1].setwho('O');
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
                    return 1;
                }
                
                else if( ( j>0&&gameCells[i][j-1].getwho()=='.'&&i==gameSizeH-1 )|| (j>0&&gameCells[i][j-1].getwho()=='.'&& i<gameSizeH-1 &&gameCells[i+1][j].getwho()!='.' ) ){
                    gameCells[i][j-1].setwho('O');
                    return 1;
                }
                else if( ( gameCells[i][j+1].getwho()=='.'&&i==gameSizeH-1 ) || (gameCells[i][j+1].getwho()=='.'&& i<gameSizeH-1 && gameCells[i+1][j+1].getwho()!='.' ) ){
                    gameCells[i][j+1].setwho('O');
                    return 1;
                }
            }
            
        }
        
    }
    
    return 0;
    
}

int ConnectFour::finish(const int h, const int w){ //oyunun bitip bitmedigini kontrol eder
    
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
        
        for(j=0;j<w-3;j++){
            
            
            if(gameCells[i][j].getwho()=='O')
                var+=1;
            if(gameCells[i-1][j+1].getwho()=='O')
                var+=1;
            if(gameCells[i-2][j+2].getwho()=='O')
                var+=1;
            if(gameCells[i-3][j+3].getwho()=='O')
                var+=1;
            
            if(var==4){
                return 2;
            }
            var=0;
            
        }
        
        
    }
    for(i=h;i>3;i--){
        
        for(j=w-1;j>2;j--){
            
            
            if(gameCells[i][j].getwho()=='O')
                var+=1;
            if(gameCells[i-1][j-1].getwho()=='O')
                var+=1;
            if(gameCells[i-2][j-2].getwho()=='O')
                var+=1;
            if(gameCells[i-3][j-3].getwho()=='O')
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
    
    for(i=h;i>3;i--){
        
        for(j=w-1;j>2;j--){
            
            
            if(gameCells[i][j].getwho()=='X')
                var+=1;
            if(gameCells[i-1][j-1].getwho()=='X')
                var+=1;
            if(gameCells[i-2][j-2].getwho()=='X')
                var+=1;
            if(gameCells[i-3][j-3].getwho()=='X')
                var+=1;
            
            if(var==4){
                return 1;
            }
            var=0;
            
        }
        
        
    }
    
    
    for(i=h;i>3;i--){
        
        for(j=0;j<w-3;j++){
            
            
            if(gameCells[i][j].getwho()=='X')
                var+=1;
            if(gameCells[i-1][j+1].getwho()=='X')
                var+=1;
            if(gameCells[i-2][j+2].getwho()=='X')
                var+=1;
            if(gameCells[i-3][j+3].getwho()=='X')
                var+=1;
            
            if(var==4){
                return 1;
            }
            var=0;
            
        }
        
        
    }
 
    return 0;
}
