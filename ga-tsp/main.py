import numpy as np
import matplotlib.pyplot as plt
from GeneticAlgorithm import initialization, create_new_generation, find_best
from Chromosome import dataset, Node

# parameters
numbers_of_generations = 200
population_size = 100
mut_rate = 0.2


def genetic_algorithm(num_of_generations: int, pop_size: int, mutation_rate: float, data_list: list[Node]):
    new_gen = initialization(data_list, pop_size)
    costs_for_plot = []

    for iteration in range(0, num_of_generations):
        new_gen = create_new_generation(new_gen, mutation_rate)
        print(str(iteration) + ". generation --> " + "cost --> " + str(new_gen[0].cost))
        costs_for_plot.append(find_best(new_gen).cost)
    return new_gen, costs_for_plot


def draw_cost_generation(y_list):
    x_list = np.arange(1, len(y_list) + 1)
    plt.plot(x_list, y_list)
    plt.title("Route Cost through Generations")
    plt.xlabel("Generations")
    plt.ylabel("Cost")
    plt.show()


def draw_path(solution):
    x_list = []
    y_list = []

    for m in range(0, len(solution.chromosome)):
        x_list.append(solution.chromosome[m].x)
        y_list.append(solution.chromosome[m].y)

    fig, ax = plt.subplots()
    plt.scatter(x_list, y_list)

    ax.plot(x_list, y_list, '--', lw=2, color='black', ms=10)
    ax.set_xlim(0, 1650)
    ax.set_ylim(0, 1300)

    plt.show()


last_generation, y_axis = genetic_algorithm(
    num_of_generations=numbers_of_generations, pop_size=population_size, mutation_rate=mut_rate, data_list=dataset
)

best_solution = find_best(last_generation)
draw_cost_generation(y_axis)
draw_path(best_solution)
