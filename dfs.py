def dfs(graph, start, goal):
    """
    Depth-First Search (iterative)
    """
    stack = [start]
    visited = set()
    parent = {start: None}
    while stack:
        node = stack.pop()
        if node not in visited:
            visited.add(node)
            if node == goal:
                return reconstruct_path(parent, goal)
            for neighbor, _ in reversed(graph.get(node, [])):
                if neighbor not in visited:
                    parent[neighbor] = node
                    stack.append(neighbor)
    return None