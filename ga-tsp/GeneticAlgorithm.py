import random
from Chromosome import Chromosome, Node
from constant import POPULATION_SIZE, MUTATION_RATE, CROSSOVER_RATE


def create_random_list(data: list[Node]) -> list[Node]:
    _len = len(data)
    _list = list(range(1, _len))
    times = random.randint(10, 30)
    _range = range(0, len(_list))
    for i in range(0, times):
        index1, index2 = random.sample(_range, 2)
        _temp = _list[index1]
        _list[index1] = _list[index2]
        _list[index2] = _temp
    result = []
    for _index in _list:
        result.append(data[_index])
    result.insert(0, data[0])
    result.append(data[0])
    return result


def initialization(data: list[Node], matrix: list[list[int]]) -> list[Chromosome]:
    initial_population = []
    for i in range(0, POPULATION_SIZE):
        temp = create_random_list(data)
        new_ch = Chromosome(temp, matrix)
        initial_population.append(new_ch)
    return initial_population


def selection(population: list[Chromosome]) -> Chromosome:
    _list: list[int] = random.sample(range(0, POPULATION_SIZE), 4)
    candidate1 = population[_list[0]]
    candidate2 = population[_list[1]]
    candidate3 = population[_list[2]]
    candidate4 = population[_list[3]]

    if candidate1.fitness_value > candidate2.fitness_value:
        winner = candidate1
    else:
        winner = candidate2

    if candidate3.fitness_value > winner.fitness_value:
        winner = candidate3

    if candidate4.fitness_value > winner.fitness_value:
        winner = candidate4

    return winner


def _is_in(item: Node, data: list[Node]) -> bool:
    for i in data:
        if i.id == item.id:
            return True
    return False


def display_node(data: list[Node]):
    result = []
    for i in data:
        result.append(str(i.id))
    return ','.join(result)


def _create_new_children(begin: int, parent: list[Node], middle_parent: list[Node]) -> list[Node]:
    child = middle_parent.copy()

    counter = 1
    index = 1
    latest_index = len(parent) - 1
    while counter < latest_index and index < latest_index:
        if not _is_in(parent[counter], child):
            if index < begin:
                child.insert(index - 1, parent[counter])
            elif index == begin:
                index += len(middle_parent)
                if index < latest_index:
                    child.append(parent[counter])
            else:
                child.append(parent[counter])
            index += 1
        counter += 1
    return child


def crossover(parent1: Chromosome, parent2: Chromosome) -> tuple[list[Node], list[Node]]:
    one_point = random.randint(2, 14)

    child1 = parent1.chromosome[1:one_point]
    child2 = parent2.chromosome[1:one_point]

    child1_remain = [item for item in parent2.chromosome[1:-1] if item not in child1]
    child2_remain = [item for item in parent1.chromosome[1:-1] if item not in child2]

    child1 += child1_remain
    child2 += child2_remain

    child1.insert(0, parent1.chromosome[0])
    child1.append(parent1.chromosome[0])

    child2.insert(0, parent2.chromosome[0])
    child2.append(parent2.chromosome[0])
    return child1, child2


def crossover_two1(parent1: Chromosome, parent2: Chromosome) -> tuple[list[Node], list[Node]]:
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


def crossover_two(parent1: Chromosome, parent2: Chromosome) -> tuple[list[Node], list[Node]]:
    point1, point2 = random.sample(range(1, len(parent1.chromosome) - 1), 2)
    begin = min(point1, point2)
    end = max(point1, point2)

    child1 = _create_new_children(begin, parent2.chromosome, parent1.chromosome[begin:end + 1])
    child2 = _create_new_children(begin, parent1.chromosome, parent2.chromosome[begin:end + 1])

    child1.insert(0, parent1.chromosome[0])
    child1.append(parent1.chromosome[0])

    child2.insert(0, parent2.chromosome[0])
    child2.append(parent2.chromosome[0])
    return child1, child2


def crossover_mix(parent1: Chromosome, parent2: Chromosome) -> tuple[list[Node], list[Node]]:
    point1, point2 = random.sample(range(1, len(parent1.chromosome) - 1), 2)
    begin = min(point1, point2)
    end = max(point1, point2)

    child11 = parent1.chromosome[:begin]
    child12 = parent1.chromosome[end:]
    child1 = child11 + child12
    child2 = parent2.chromosome[begin:end + 1]

    child1_remain = [item for item in parent2.chromosome[1:-1] if item not in child1]
    child2_remain = [item for item in parent1.chromosome[1:-1] if item not in child2]

    child1 = child11 + child1_remain + child12
    child2 += child2_remain

    child2.insert(0, parent2.chromosome[0])
    child2.append(parent2.chromosome[0])
    return child1, child2


def mutation(chromosome: list[Node]) -> list[Node]:
    _len = len(chromosome)
    index1, index2 = random.sample(range(1, _len - 1), 2)
    chromosome[index1], chromosome[index2] = chromosome[index2], chromosome[index1]
    return chromosome


def find_best(generation: list[Chromosome]) -> Chromosome:
    best = generation[0]
    for n in range(1, len(generation)):
        if generation[n].cost < best.cost:
            best = generation[n]
    return best


def find_two_best(generation: list[Chromosome]) -> tuple[Chromosome, Chromosome]:
    best1 = generation[0]
    best2 = generation[1]
    for n in range(1, len(generation)):
        if generation[n].cost < best1.cost:
            best2 = best1
            best1 = generation[n]
    return best1, best2


def create_new_generation(previous_generation: list[Chromosome], matrix: list[list[int]]) -> list[Chromosome]:
    new_generation = [find_best(previous_generation)]
    # new_generation = list(find_two_best(previous_generation))

    for a in range(0, int(len(previous_generation) / 2)):
        parent_1 = selection(previous_generation)
        parent_2 = selection(previous_generation)
        if random.random() < CROSSOVER_RATE:
            child_1, child_2 = crossover_mix(parent_1, parent_2)
        else:
            child_1 = parent_1.chromosome
            child_2 = parent_2.chromosome

        if random.random() < MUTATION_RATE:
            child_1 = mutation(child_1)
            child_2 = mutation(child_2)

        new_generation.append(Chromosome(child_1, matrix))
        new_generation.append(Chromosome(child_2, matrix))

    return new_generation
