class Solution {
  public:
  
    bool isCycleDFS(unordered_map<int,vector<int>> &adj,vector<bool> &visited, int u, int parent) {
        
        visited[u] = true;
        
        for(int &v : adj[u]) {

            if(v == parent) continue;
            if(visited[v]) return true;
            
            visited[v] = true;
            if(isCycleDFS(adj,visited,v,u)) {
                return true;
            };
            
        }
        
        return false;
        
    }
    
    bool isCycle(int V, vector<vector<int>>& edges) {
        // Code here
        unordered_map<int,vector<int>> adj;
        vector<bool> visited(V,false);
        
        for(auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            adj[u].push_back(v);
            adj[v].push_back(u); // Add both directions for an undirected graph
        }
        for(int i=0;i<V;i++) {
            if(!visited[i] && isCycleDFS(adj,visited,i,-1)) {
                return true;
            }
        }
        
        return false;
    }
};