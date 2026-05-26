def bfs(graph, start, goal):
    """
    Breadth-First Search
    """
    queue = deque([start])
    visited = set([start])
    parent = {start: None}
    while queue:
        node = queue.popleft()
        if node == goal:
            return reconstruct_path(parent, goal)
        for neighbor, _ in graph.get(node, []):
            if neighbor not in visited:
                visited.add(neighbor)
                parent[neighbor] = node
                queue.append(neighbor)
    return None