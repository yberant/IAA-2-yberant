//escoge al azar una permutación
vector<vector<int>> randomMove(vector<vector<int>> S){
    vector<vector<int>> newS=S;
    int random=rand();

    if(random) randomPartialSwapRounds(newS);
    else randomPartialSwapTeams(newS);
    
    return newS;
}

//escoge los parámetros de la permutación escogida
void randomPartialSwapRounds(vector<vector<int>> &S){
    int T=1+(rand()%n);
    int Rk=rand()%(2*(n-1));
    int Rl;
    do{
        Rl=rand()%(2*(n-1));
    }while(Rk==Rl);
    //cout<<"partialSwapRounds("<<T<<","<<Rk<<","<<Rl<<"):"<<endl;
    partialSwapRounds(S,T,Rk,Rl);    
}

//escoge los parámetros de la permutación escogida
void randomPartialSwapTeams(vector<vector<int>> &S){
    int R,Ti,Tj;
    do{
        R=rand()%(2*(n-1));
        Ti=1+(rand()%n);
        do{
            Tj=(1+rand()%n);
        }while(Ti==Tj);//para que no queden iguales
    }while(partialSwapTeams(S,R,Ti,Tj)==0);//si retorna 0, es porque no se hicieron cambios en S
    //cout<<"partialSwapTeams("<<R<<","<<Ti<<","<<Tj<<")"<<endl;
}