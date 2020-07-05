double distance(int i, int j){//recibe numeros de equipos, no indices (hay que restar)
    /*cout<<"locacion actual:"<<i<<endl;
    cout<<"me muevo a:"<<j<<endl;
    cout<<"recorro una distancia de:"<< D[i-1][j-1]<<endl;*/
    return D[i-1][j-1];
}

double teamScheduleDistance(vector<vector<int>> S, int j){
    double dist=0;
    int actual=j;
    int next=j;
    for(int i=0;i<2*(n-1);i++){
        int t=S[i][j-1];
        //cout<<endl<<"siguiente rival: "<<t<<endl;
        if(t<0){//juego de visita
            next=abs(t);
        }
        else{//juego como local
            next=j;
        }
        dist+=distance(actual,next);
        //cout<<"distancia actual recorrida por el equipo "<<j<<": "<<dist<<endl;
        actual=next;
    }
    next=j;
    dist+=distance(actual,j);
    //cout<<"distancia final recorrida por el equipo "<<j<<": "<<dist<<endl;
    return dist;
}

double scheduleDistance(vector<vector<int>> S){
    //cout<<"A"<<endl;
    double dist=0;
    for(int j=1;j<=n;j++){
        dist+=teamScheduleDistance(S,j);
        //cout<<"distancia recorrida por equipos actualmente: "<<dist<<endl;
    }
    return dist;
}


//actualiza rondas y equipos que están en conflicto  por la restriccion atMost
int atMostConflicts(vector<vector<int>> S){
    int cost=0;
    
    for(int j=0;j<n;j++){
        int consecutive=0;
        int sign;
        if (S[0][j]>0) sign=1;
        else sign=-1;
        for(int i=0;i<2*(n-1);i++){
            //cout<<"S["<<i<<"]["<<j<<"]: "<<S[i][j]<<endl;
            if(S[i][j]*sign>0) consecutive++;
            else{
                consecutive=1;
                sign=-sign;
            }


            if(consecutive>3){//u=3
                cost++;
            }
            //cout<<"consecutive: "<<consecutive<<", sign: "<<sign<<" cost: "<<cost<<endl;
        }
    }
    return cost;
}

//actualiza rondas y equipos que están en conflicto  por la restriccion noRepeat
int noRepeatConflicts(vector<vector<int>> S){
    double cost=0;
    
    for(int j=0;j<n;j++){
        int actual=0;
        int next=0;
        for(int i=0;i<2*(n-1);i++){
            next=S[i][j];
            if(abs(actual)==abs(next)) cost++;
            actual=next;

        }
    }
    return cost/2;//se divide por dos porque se estaría contando en los dos equipos en donde ocurre cada conflicto
}

int totalConflicts(vector<vector<int>> S){
    int CT=noRepeatConflicts(S);
    int CR=atMostConflicts(S);
    return CT+CR;
}


double cost(double distance, int conflicts){
    if(conflicts==0){
        return distance;
    }
    else{
        int c=(double)conflicts;
        //cout<<"c: "<<c<<endl;
        double f=1+(sqrt(c)*log(c))/2;//ver anagnostooulos para mas info
        return sqrt(distance+pow(w*f,2));//ojo que esta es la versión de Nourollahi de la función objetivo
    }
}