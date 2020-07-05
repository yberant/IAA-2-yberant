void printMatrix(vector<vector<int>> M){
    for(int i=0;i<M.size();i++){
        for(int j=0;j<M[i].size();j++){
            cout<<M[i][j]<<"\t";
        }
        cout<<"\n";
    }
    cout<<"\n";
}

void printTournament(vector<vector<int>> M){
    vector<int> printedTeams;
    for(int i=0;i<n;i++){
        printedTeams.push_back(0);
    }
    for(int i=0;i<2*(n-1);i++){
        vector<int> pt=printedTeams;
        cout<<"ronda "<<i<<": ";
        for(int j=0;j<n;j++){
            if(pt[j]==0){
                int k=M[i][j];//contra quien compite j en ronda k
                pt[abs(k)-1]=1;//para no volver a imprimir el partido
                if(k>0){//j juega como local
                    cout<<j+1<<"(L) vs "<<abs(k)<<"(V), ";
                }
                else cout<<abs(k)<<"(L) vs "<<j+1<<"(V), ";
            }
            pt[j]=1;
        }
        cout<<endl;
    }
}


vector<vector<int>> transpose(vector<vector<int>> M){
    if (M.size()==0) return M;
    vector<vector<int>> Mt(M[0].size(), vector<int>());
    for (int i=0;i<M.size();i++)
        for(int j = 0;j<M[i].size();j++)
            Mt[j].push_back(M[i][j]);
    return Mt;
}


void swapElements(vector<vector<int>> &M, int x1, int y1,int x2,int y2){
    int aux=M[x1][y1];
    M[x1][y1]=M[x2][y2];
    M[x2][y2]=aux;
}

void printVector(vector<int> v){
    for(int i=0;i<v.size();i++)cout<<v[i]<<"\t";
    cout<<endl;
}

//inserta en la ronda r, un juego de Ti(L) contra Tj(V);
void insertGame(vector<vector<int>> & S, int Ti, int Tj, int r){
    //cout<<"Ti: "<<Ti<<", Tj: "<<Tj<<", r: "<<r<<endl;
    //cout<<"vector: ";printVector(S[r]);
    S[r][Ti-1]=Tj;
    S[r][Tj-1]=-Ti;
    //cout<<"S actual"<<endl;printMatrix(S);
}

//añade un elemento a un arreglo, si es que no se ha agregado aún
void add(vector<int> & arr, int value){
    for(auto v:arr){
        if(v==value) return;
    }
    arr.push_back(value);
    return;
}

//añade valores de "values" en arreglo arr.
void addValues(vector<int> & arr, vector<int> & values){
    for(auto v: values){
        add(arr, v);
    }
    
}

//este se explica por sì solo
void resetVector(vector<int> & v){
    vector<int> newV;
    v=newV;
}