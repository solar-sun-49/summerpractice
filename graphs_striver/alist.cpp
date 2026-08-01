#include <iostream>
using namespace std;

int main() {

    int n,m;

    cin >> n >> m;

    vector<int> adj[n+1];

    for(int i=0;i<m;i++) {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);

        //remove the below line if the graph is directed
        adj[v].push_back(u);
    }

    return 0;
}