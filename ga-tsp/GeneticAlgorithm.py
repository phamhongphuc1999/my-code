import random
from Chromosome import Chromosome, Node


def create_random_list(n_list: list[Node]) -> list[Node]:
    start = n_list[0]

    temp = n_list[1:]
    temp = random.sample(temp, len(temp))

    temp.insert(0, start)
    temp.append(start)
    return temp


# initialization
def initialization(data: list[Node], pop_size: int) -> list[Chromosome]:
    initial_population = []
    for i in range(0, pop_size):
        temp = create_random_list(data)
        new_ch = Chromosome(temp)
        initial_population.append(new_ch)
    return initial_population


def selection(population: list[Chromosome]) -> Chromosome:
    _list: list[int] = random.sample(range(0, 99), 4)

    candidate_1 = population[_list[0]]
    candidate_2 = population[_list[1]]
    candidate_3 = population[_list[2]]
    candidate_4 = population[_list[3]]

    if candidate_1.fitness_value > candidate_2.fitness_value:
        winner = candidate_1
    else:
        winner = candidate_2

    if candidate_3.fitness_value > winner.fitness_value:
        winner = candidate_3

    if candidate_4.fitness_value > winner.fitness_value:
        winner = candidate_4

    return winner


def crossover(parent1: Chromosome, parent2: Chromosome) -> tuple[list[Node], list[Node]]:
    one_point = random.randint(2, 14)

    child_1 = parent1.chromosome[1:one_point]
    child_2 = parent2.chromosome[1:one_point]

    child_1_remain = [item for item in parent2.chromosome[1:-1] if item not in child_1]
    child_2_remain = [item for item in parent1.chromosome[1:-1] if item not in child_2]

    child_1 += child_1_remain
    child_2 += child_2_remain

    child_1.insert(0, parent1.chromosome[0])
    child_1.append(parent1.chromosome[0])

    child_2.insert(0, parent2.chromosome[0])
    child_2.append(parent2.chromosome[0])

    return child_1, child_2


def crossover_two(parent1: Chromosome, parent2: Chromosome) -> tuple[list[Node], list[Node]]:
    point_1, point_2 = random.sample(range(1, len(parent1.chromosome) - 1), 2)
    begin = min(point_1, point_2)
    end = max(point_1, point_2)

    child_1 = parent1.chromosome[begin:end + 1]
    child_2 = parent2.chromosome[begin:end + 1]

    child_1_remain = [item for item in parent2.chromosome[1:-1] if item not in child_1]
    child_2_remain = [item for item in parent1.chromosome[1:-1] if item not in child_2]

    child_1 += child_1_remain
    child_2 += child_2_remain

    child_1.insert(0, parent1.chromosome[0])
    child_1.append(parent1.chromosome[0])

    child_2.insert(0, parent2.chromosome[0])
    child_2.append(parent2.chromosome[0])

    return child_1, child_2


def crossover_mix(parent1: Chromosome, parent2: Chromosome) -> tuple[list[Node], list[Node]]:
    point_1, point_2 = random.sample(range(1, len(parent1.chromosome) - 1), 2)
    begin = min(point_1, point_2)
    end = max(point_1, point_2)

    child_1_1 = parent1.chromosome[:begin]
    child_1_2 = parent1.chromosome[end:]
    child_1 = child_1_1 + child_1_2
    child_2 = parent2.chromosome[begin:end + 1]

    child_1_remain = [item for item in parent2.chromosome[1:-1] if item not in child_1]
    child_2_remain = [item for item in parent1.chromosome[1:-1] if item not in child_2]

    child_1 = child_1_1 + child_1_remain + child_1_2
    child_2 += child_2_remain

    child_2.insert(0, parent2.chromosome[0])
    child_2.append(parent2.chromosome[0])

    return child_1, child_2


def mutation(chromosome: list[Node]) -> list[Node]:
    mutation_index_1, mutation_index_2 = random.sample(range(1, 19), 2)
    chromosome[mutation_index_1], chromosome[mutation_index_2] = chromosome[mutation_index_2], chromosome[
        mutation_index_1]
    return chromosome


def find_best(generation: list[Chromosome]) -> Chromosome:
    best = generation[0]
    for n in range(1, len(generation)):
        if generation[n].cost < best.cost:
            best = generation[n]
    return best


def create_new_generation(previous_generation: list[Chromosome], mutation_rate: float) -> list[Chromosome]:
    new_generation = [find_best(previous_generation)]

    for a in range(0, int(len(previous_generation) / 2)):
        parent_1 = selection(previous_generation)
        parent_2 = selection(previous_generation)

        child_1, child_2 = crossover_two(parent_1, parent_2)
        child_1 = Chromosome(child_1)
        child_2 = Chromosome(child_2)

        if random.random() < mutation_rate:
            mutated = mutation(child_1.chromosome)
            child_1 = Chromosome(mutated)

        new_generation.append(child_1)
        new_generation.append(child_2)

    return new_generation
