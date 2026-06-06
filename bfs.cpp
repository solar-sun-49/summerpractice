class Solution {
  public:
  
  
    void BFS(unordered_map<int,vector<int>> &graph,int u,vector<bool> &visited, vector<int> &result) {
        
        queue<int> q;
        
        q.push(u);
        visited[u] = true;
        result.push_back(u);
        
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            
            for(int &v: graph[u]) {
                if(!visited[v]) {
                    q.push(v);
                    visited[v] = true;
                    result.push_back(v);
                }
            }
        }
        
    }
    
    
    vector<int> bfs(vector<vector<int>> &adj) {
        // code here
        unordered_map<int,vector<int>> graph;
        int n = adj.size();
        
        for(int u=0;u<n;u++) {
            for(auto v = adj[u].begin(); v != adj[u].end();v++) {
                graph[u].push_back(*v);
            }
        }
        
        vector<int> result;
        vector<bool> visited(n,false);
        
        BFS(graph,0,visited,result);
        
        return result;
    }
};