#include<stdlib.h>
#include<ctime>
#include<cmath>
#include<cstddef>
#include<iterator>
#include<algorithm> 
#include<fstream>
#include<chrono>
#include<iostream>
#include<vector>
#include<cstdlib>
#include<string>
#include<fstream>
#include <sstream>
#include"tda.h"
#include"initial.h"
#include"basic.h"
#include"cost.h"
#include"permutations.h"
#include"randommove.h"
#include"accept.h"



int ReadNumbers( const string & s, vector<int> & v) {
    istringstream is( s );
    double n;
    while( is >> n ) {
        v.push_back( n );
    }
    return v.size();
}

//fuente: https://www.quora.com/How-do-I-read-a-matrix-from-a-file-in-C++
vector<vector<double>> distanceMatrix(string arch){

    ifstream File; 
    vector<vector<double>> d;

    std::string line;
    vector<int> v;

    File.open(arch);
    if (File.is_open()){
        int i=0;
        getline(File, line);
        n =ReadNumbers(line, v);
        cout << "N:" << n << endl;
        for ( i=1;i<32767;i++){
            if (!getline(File, line)) break;//TODO: OJO CON EL COMPILADOR ACÁ!!!!!!!!!
            ReadNumbers( line, v );
            
        }
        File.close();
    }
    else{
        cout << "file open failed";
    }
    for (int i=0;i<n;i++){
        vector<double> row;
        for (double j=0;j<n;j++){
            row.push_back(v[i*n+j]);
            //cout<<v[i*n+j]<<"\t"
        }
        //cout << endl;
        d.push_back(row);
    }
    return d;
}


int main(int argc ,char* argv[]){

    // ./main semilla archivo T_inicial Ratio_enfriamiento maxIteraciones

    srand(atoi(argv[1]));
    cout<<"seed: "<<argv[1]<<endl;

    string f=string(argv[2]);
    string arch="instancias/"+string(argv[2]);
    D=distanceMatrix(arch);
    //auto start = chrono::high_resolution_clock::now();
    
    
    vector<vector<int>> bestS;//matriz inicial
    vector<vector<int>> bestFactibleS;

    
    vector<vector<int>> actualS;
    double actualDistance;
    int actualConflicts;
    double actualCost;
    /* double actualDistance=scheduleDistance(actualS);
    int actualConflicts=totalConflicts(bestS);
    double actualCost=cost(actualDistance,actualConflicts); */  

    double bestFactibleDistance=INFINITY;
    double bestCost;
    
   

    T=atoi(argv[3]);//5000;
    cout<<"initial T: "<<T<<endl;
    initialT=T;
    w=500*n;
    double ratioW=1.2;//ratio en que cambian los pesos de los conflictos

    double coolRatio=atof(argv[4]);//0.9999;
    cout<<"coolRatio: "<<coolRatio<<endl;

    
    /* double coolRatio=0.9999;//proporción de enfriamiento
    double heatRatio=1.7; */

    int maxR=atoi(argv[5]);//reheats del algoritmo/
    cout<<"maxR: "<<maxR<<endl;
    int r=0;

    int q=1;//cantidad de torneos iniciales que se probarán

    int maxC=50*n;
    int c=0;

    int iterations=0;
    int maxIterations=atoi(argv[5]);//25000*n;
    cout<<"max iterations: "<<maxIterations<<endl;

    bool factibleFound=false;//si ya se encontró una solucion factible
    cout<<"ejecutando..."<<endl;
    auto start = chrono::high_resolution_clock::now();
    while(iterations<maxIterations){
        actualS=DoubleRoundRobin();//generación de solución inicial

        actualDistance=scheduleDistance(actualS);
        actualConflicts=totalConflicts(actualS);
        actualCost=cost(actualDistance,actualDistance);
        bestCost=actualCost;
        r=0;

        while(r<maxR && iterations<maxIterations){//desde acá se busca desde una solución inicial
            c=0;
            while(c<maxC && iterations<maxIterations){//empieza un "ciclo" (ver informe)
                vector<vector<int>> candidateS=randomMove(actualS);
                double candidateDistance=scheduleDistance(candidateS);
                int candidateConflicts=totalConflicts(candidateS);
                double candidateCost=cost(candidateDistance,candidateConflicts);
                //se revisa si se encontró el mejor factible
                if(candidateConflicts==0 && candidateDistance<bestFactibleDistance){
                        bestFactibleS=candidateS;
                        bestFactibleDistance=candidateDistance;
                        factibleFound=true;
                    }

                //aceptacion, segun el criterio de simmulated annealing
                bool accept=(candidateCost<actualCost);
                if(!accept){
                    double random=double(rand()%10000)/10000;
                    double value=pow(EPSILON,(bestCost-candidateCost)/T);
                    accept=random<value; 
                }
                if(accept){
                    c=0;
                    actualS=candidateS;
                    actualConflicts=candidateConflicts;
                    actualDistance=candidateDistance;
                    actualCost=candidateCost;

                    if(actualCost<bestCost){
                        bestS=actualS;
                        bestCost=actualCost;

                        if(actualConflicts==0) w/=ratioW;
                        else w*=ratioW;
                    }
                }
                //enfriamiento
                T*=coolRatio;
                c++;
                iterations++;
            }
            //fin del ciclo y recalentamiento
            T=initialT;
            r++;    
        }
        q++;
    }
    auto stop = chrono::high_resolution_clock::now(); 
    auto duration=chrono::duration_cast<chrono::microseconds>(stop-start);
    if(factibleFound){//si se encontró una sol. factible
        cout<<"torneo final encontrado: "<<endl;
        printTournament(bestFactibleS);
        cout<<"distancia total de viajes del torneo: "<<bestFactibleDistance<<endl;
    }
    else{
        cout<<"no se pudo encontrar un toreno factible"<<endl;
    }
    
    cout<<"tiempo de ejecucion:"<<duration.count()/1000000.0<<" segundos"<<endl;
    cout<<"numero total de iteraciones: "<<iterations<<endl;
    cout<<"numero total de soluciones iniciales exploradas: "<<q<<endl;

    return 0;
}


