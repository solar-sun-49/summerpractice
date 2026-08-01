#include <iostream>
using namespace std;

int main() {

    int n,m;

    cin >> n >> m;

    int matrix[n+1][n+1];

    for(int i=0;i<m;i++) {
        int u,v;
        cin >> u >> v;
        matrix[u][v] = 1;

        //remove the below line if the graph is directed
        matrix[v][u] = 1;
    }



    return 0;
}