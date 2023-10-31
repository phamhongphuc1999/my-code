import numpy as np
import matplotlib.pyplot as plt
from GeneticAlgorithm import initialization, create_new_generation, find_best, display_node
from Chromosome import Node, create_dataset, create_distance_matrix
from constant import NUM_GENERATION
import time


def genetic_algorithm(data_list: list[Node], matrix: list[list[int]]):
    new_gen = initialization(data_list, matrix)
    costs_for_plot = []

    for iteration in range(0, NUM_GENERATION):
        new_gen = create_new_generation(new_gen, matrix)
        best_individual = find_best(new_gen)
        # if iteration == 0:
        #     print(f"initial cost: {best_individual.cost}, best solution: {display_node(best_individual.chromosome)}")
        # elif iteration == NUM_GENERATION - 1:
        #     print(f"final cost: {best_individual.cost}, best solution: {display_node(best_individual.chromosome)}")
        # print(f"{iteration + 1} cost: {best_individual.cost}, solution: {display_node(best_individual.chromosome)}")
        costs_for_plot.append(best_individual.cost)
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
    x_max = max(x_list)
    y_max = max(y_list)
    ax.set_xlim(0, x_max)
    ax.set_ylim(0, y_max)
    plt.show()


def run_ten_times(file: str):
    times: list[[float, float]] = []
    for i in range(0, 10):
        start = time.time()
        dataset = create_dataset(file)
        _matrix = create_distance_matrix(dataset)
        last_generation, y_axis = genetic_algorithm(dataset, _matrix)
        end = time.time()
        best_solution = find_best(last_generation)
        times.append([best_solution.cost, end - start])
    print(times)
    total = 0
    min_cost = 1000000000
    for _time in times:
        total += _time[1]
        if min_cost > _time[0]:
            min_cost = _time[0]
    print(f"average time: {total / 10}, min cost: {min_cost}")
    # draw_cost_generation(y_axis)
    # draw_path(best_solution)


def run(file: str):
    start = time.time()
    dataset = create_dataset(file)
    _matrix = create_distance_matrix(dataset)
    last_generation, y_axis = genetic_algorithm(dataset, _matrix)
    end = time.time()
    best_solution = find_best(last_generation)
    print(f"time: {end - start}, cost: {best_solution.cost}")
    # draw_cost_generation(y_axis)
    # draw_path(best_solution)


if __name__ == '__main__':
    run_ten_times("training/oliver30")
    # run("training/berlin52")
