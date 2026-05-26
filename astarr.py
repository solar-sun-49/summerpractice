import heapq

def a_star(graph, heuristics, start, goal):
    pq = [(heuristics[start], start)]
    cost_so_far = {start: 0}
    path_history = {start: [start]}

    while pq:
        f_score, node = heapq.heappop(pq)

        if node == goal:
            return path_history[node]

        for neighbor, edge_cost in graph[node]:
            new_cost = cost_so_far[node] + edge_cost

            if neighbor not in cost_so_far or new_cost < cost_so_far[neighbor]:
                cost_so_far[neighbor] = new_cost
                path_history[neighbor] = path_history[node] + [neighbor]
                new_f = new_cost + heuristics[neighbor]
                heapq.heappush(pq, (new_f, neighbor))

    return None

my_graph = {
    'A': [('B', 1), ('C', 4)],
    'B': [('C', 2), ('D', 5)],
    'C': [('D', 1)],
    'D': []
}

my_heuristics = {'A': 3, 'B': 2, 'C': 1, 'D': 0}

result = a_star(my_graph, my_heuristics, 'A', 'D')
print("A* Shortest Path:", result)