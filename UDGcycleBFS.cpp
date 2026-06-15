class Solution {
  public:
  
    bool isCycleBFS(unordered_map<int,vector<int>> &adj,vector<bool> &visited, int i) {
        
        queue<pair<int,int>> q;
        ok
        
        q.push({i,-1});
        visited[i] = true;
        
        while(!q.empty()) {
            pair<int,int> p = q.front();
            q.pop();
            int source = p.first;
            int parent = p.second;
            
            for(int &v : adj[source]) {
                if(visited[v] == false) {
                    visited[v] = true;
                    q.push({v, source});
                }
                
                else if(v != parent) {
                    return true;
                }
                
                
            }
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
            if(!visited[i] && isCycleBFS(adj,visited,i)) {
                return true;
            }
        }
        
        return false;
    }
};