#include <iostream>
using namespace std;

void bfs(int n,int start,vector<int> adj[]) {
    vector<bool> visisted(n,false);
    queue<int> q;
    visisted[start] = true;
    q.push(start);
    vector<int> traversal;

    while(!q.empty()) {
        int u = q.front();
        q.pop();
        traversal.push_back(u);

        for(auto v : adj[u]) {
            if(!visisted[v]) {
                visisted[v] = true;
                q.push(v);
            }
        }
    }
}

int main() {

    

    return 0;
}