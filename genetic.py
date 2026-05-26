import random

# Basic configuration
n_queens = 5
population_size = 50
mutation_rate = 0.2
max_epochs = 1000

def create_random_board():
    # Index represents column, value represents row
    new_board = []
    for i in range(n_queens):
        new_board.append(random.randint(0, n_queens - 1))
    return new_board

# Generate the initial set of boards
population = []
for _ in range(population_size):
    population.append(create_random_board())

print(f"Initialized population with {len(population)} boards.")