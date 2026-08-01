#include <iostream>
using namespace std;

vector<int> bfs(int n,int starting, vector<int> adj[]) {
    vector<int> traversal;
    vector<bool> visited(n,false);
    visited[starting] = true;

    queue<int> q;
    q.push(starting);

    while(!q.empty()) {
        int curr = q.front();
        q.pop();
        traversal.push_back(curr);

        for(auto neighbour : adj[curr]) {
            if(!visited[neighbour]) {
                q.push(neighbour);
                visited[neighbour] = true;
            }
        }
    }

    return traversal;
}

int main() {

    

    return 0;
}