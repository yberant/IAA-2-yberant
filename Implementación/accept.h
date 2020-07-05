//determina si acepta o no una solución candidata
bool accept(vector<vector<int>> candidateS, vector<vector<int>> bestS, double bestDistance, int bestConflicts){
    double candidateDistance=scheduleDistance(candidateS);
    int candidateConflicts=totalConflicts(candidateS);
    int candidateCost=cost(candidateDistance,candidateConflicts);
    int bestCost=cost(bestDistance,bestConflicts);

    if(
        (candidateCost<bestCost)
    ){}

    return false;
}