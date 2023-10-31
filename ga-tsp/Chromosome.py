import math


class Node:
    def __init__(self, id: str, x: str, y: str):
        self.x = float(x)
        self.y = float(y)
        self.id = int(id)


def create_dataset(file_name: str) -> list[Node]:
    _dataset = []
    with open(file_name, "r") as f:
        for line in f:
            new_line = line.strip()
            new_line = new_line.split(" ")
            _dataset.append(Node(id=new_line[0], x=new_line[1], y=new_line[2]))
    return _dataset


def create_distance_matrix(node_list: list[Node]) -> list[list[int]]:
    _len = len(node_list)
    result = [[0 for _ in range(_len)] for _ in range(_len)]
    for i in range(0, _len):
        for j in range(0, _len):
            _from = node_list[i].id - 1
            _to = node_list[j].id - 1
            result[_from][_to] = math.sqrt(
                pow((node_list[i].x - node_list[j].x), 2) + pow((node_list[i].y - node_list[j].y), 2))
    return result


# dataset = create_dataset("training/att532")
# matrix = create_distance_matrix(dataset)


class Chromosome:
    def __init__(self, node_list: list[Node], matrix: list[list[int]]):
        self.chromosome = node_list
        chr_representation = []
        for i in range(0, len(node_list)):
            chr_representation.append(self.chromosome[i].id)
        self.chr_representation = chr_representation
        distance = 0
        latest_index = len(self.chr_representation) - 1
        for j in range(0, latest_index):
            distance += matrix[self.chr_representation[j] - 1][self.chr_representation[j + 1] - 1]
        self.cost = distance
        self.fitness_value = 1 / self.cost
