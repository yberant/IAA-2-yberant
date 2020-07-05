void partialSwapRounds(vector<vector<int>> & S, int Ti, int rk, int rl){
    int actualTeam=Ti;
    int actualRound=rk;
    int otherRow=rl;

    vector<int> roundK=S[rk];
    vector<int> roundL=S[rl];
    vector<int> actualRow=roundK;
    //cout<<"ronda K:";printVector(roundK);
    //cout<<"ronda L:";printVector(roundL);

    int rival;
    do{//repairchain
        //cout<<"equipo actual: "<<actualTeam<<endl;

        //se revisa contra quien juega el equipo en la ronda actual
        int rival=actualRow[actualTeam-1];
        //cout<<"juega contra "<<rival<<endl;

        //se mueve ese juego a la siguiente ronda (sin afectar roundK y roundL, que son arreglos auxiliares copias de las rondas)
        //actualizo solución
        if(rival>0){//rival juega visita, actualteam como local
            insertGame(S,actualTeam,abs(rival),otherRow);
        }
        else{//actualTeam juega como visita, rival como local
            insertGame(S,abs(rival),actualTeam,otherRow);
        }
        actualTeam=abs(rival);
        //me muevo a la otra ronda
        if(actualRound==rk){
            actualRound=rl;
            actualRow=roundL;
            otherRow=rk;
        }
        else{
            actualRound=rk;
            actualRow=roundK;
            otherRow=rl;

        } 
        //cout<<"resultato actual: "<<endl;
        //cout<<S[rk].size()<<" S["<<rk<<"]: ";printVector(S[rk]);
        //cout<<S[rl].size()<<" S["<<rl<<"]: ";printVector(S[rl]);
    }while(actualTeam!=Ti);
    //cout<<"resultato: "<<endl;
    //cout<<S[rk].size()<<"S["<<rk<<"]: ";printVector(S[rk]);
    //cout<<S[rl].size()<<"S["<<rl<<"]: ";printVector(S[rl]);
}

int partialSwapTeams(vector<vector<int>> & S, int r, int Ti, int Tj){
    //auto start = chrono::high_resolution_clock::now();
    if(abs(S[r][Ti-1])==Tj || abs(S[r][Tj-1]==Ti)) return 0;//returna 0 si el cambio daría lo mismo (osea, cuando Ti juga contra Tj en la ronda r)
    int actualR=r;
    int initialRival=S[actualR][Ti-1];
    int rivalI;
    int rivalJ;
    int begin=0;
    vector<int> columnI;
    for(int round=0;round<2*(n-1);round++)columnI.push_back(S[round][Ti-1]);
    vector<int> hashVector=hashVectorPSR(columnI);
    //cout<<"columnI (Ti) inicial: ";printVector(columnI);
    //cout<<"hashvector: ";printVector(hashVector);
    

    do{
        //cout<<"Ti actual: ";printVector(tS[Ti-1]);
        rivalI=S[actualR][Ti-1];
        rivalJ=S[actualR][Tj-1];
        if(rivalI==initialRival && begin){
            //cout<<"???"<<endl;
            break; //se completó el ciclo
        } 

        begin=1;
        
        //cambio los juegos entre Ti y Tj en la ronda actual:
        if(rivalI>0) insertGame(S,Tj,rivalI,actualR);//Ti está jugando de local
        else insertGame(S,-rivalI,Tj,actualR);//Ti está jugando de visita

        if(rivalJ>0) insertGame(S,Ti,rivalJ,actualR);//Tj está jugando de local
        else insertGame(S,-rivalJ,Ti,actualR);//Tj está jugando de visita


        //busco la siguente ronda en la cadena, en la que juega Ti contra el rival que jugaba antes Tj,rivalJ
        //cout<<" busqueda segun hv: "<<findByHash(hashVector,rivalJ)<<endl;
        /*for(int newR=0;newR<2*(n-1);newR++){
            if(S[newR][Ti-1]==rivalJ && newR!=actualR){
                actualR=newR;
                //cout<<" busqueda tradicional: "<<newR<<endl;
                break;
            }
        }*/
        //cout<<endl;
        actualR=findByHash(hashVector,rivalJ);//permite averiguar en que posicion está el juego contra rival en tiempo O(1), gracias a hashvector

    //if(actualR==r) cout<<"!!!!"<<endl;        
    }while(actualR!=r);
    return 1;
    /*auto stop = chrono::high_resolution_clock::now(); 
    auto duration=chrono::duration_cast<chrono::microseconds>(stop-start);
    cout<<"tiempo de ejecucion de swapteams:"<<duration.count()/1000000.0<<" segundos"<<endl;*/
}

int teamToIndex(int t){
    if(t>0) return t-1;
    else return(-t+n-1);
}


//permite averiguar en que posicion está el juego contra rival en tiempo O(1), gracias a hashvector
int findByHash(vector<int> hashVector, int rival){
    int index=teamToIndex(rival);
    return hashVector[index];
}

vector<int> hashVectorPSR(vector<int> column){
    vector<int> hashVector;
    hashVector.resize(2*n);
    for(int c=0;c<2*n;c++){
        hashVector[c]=-1;
    }
    for(int r=0;r<column.size();r++){

        int index=teamToIndex(column[r]);
        hashVector[index]=r;
    }
    
    return hashVector;
}
