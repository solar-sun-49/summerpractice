class Solution {
  public:
    
    void DFS(unordered_map<int,vector<int>> &graph, int u, vector<bool>& visited,vector<int>& result) {
        if(visited[u] == true) {
            return;
        }
        
        visited[u] = true;
        result.push_back(u);
        for(int &v : graph[u]) {
            if(!visited[v]) {
                DFS(graph,v,visited,result);
            }
        }
    }
  
  
    
    vector<int> dfs(vector<vector<int>>& adj) {
        // Code here
        unordered_map<int,vector<int>> graph;
        int n = adj.size();
        
        for(int u=0;u<n;u++) {
            for(auto v = adj[u].begin(); v != adj[u].end();v++) {
                graph[u].push_back(*v);
            }
        }
        
        vector<int> result;
        vector<bool> visited(n,false);
        
        DFS(graph,0,visited,result);
        
        return result;
        
    }
};