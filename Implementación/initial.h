vector<int> rotateVector(vector<int> teams, int permutation){
    

    rotate(teams.begin()+1,teams.begin()+1+permutation,teams.end());
    reverse(teams.begin()+n/2,teams.end());

    

    return teams;
}

//generación de solución inicial no factible
vector<vector<int>> DoubleRoundRobin(){
    vector<int> teams;
    vector<int> permutes;
    vector<vector<int>> S;
    S.resize(2*(n-1));

    for(int i=0;i<2*(n-1);i++){
        S[i].resize(n);
        
    }
    for(int i=1;i<=n;i++){
        teams.push_back(i);        
    }
    for(int i=0;i<2*(n-1);i++){
        permutes.push_back(i);
    }


    random_shuffle(teams.begin(),teams.end());
    random_shuffle(permutes.begin(),permutes.end());
    //cout<<"second half :";printVector(secondHalf);
    //cout<<"permutes: ";printVector(permutes);
    //cout<<"teams: ";printVector(teams);

    for(int i=0;i<2*(n-1);i++){
        //cout<<"i: "<<i<<endl;
        int p=permutes[i];
        int inverse=0;
        if(p>=n-1){
            p=p-(n-1);
            inverse=1;
        }
        vector<int> v=rotateVector(teams,p);
        
        //cout<<"p: "<<p<<", inverse: "<<inverse<<", v: ";printVector(v);
        //cout<<"permute: "<<permutes[i]<<endl;
        //cout<<"v: ";printVector(v);
        if(!inverse){
            for(int j=0;j<n/2;j++){
                insertGame(S,v[j],v[j+n/2],i);
            }
        }
        else{
            for(int j=0;j<n/2;j++){
                insertGame(S,v[j+n/2],v[j],i);
            }
        }       
    }
    return S;

}