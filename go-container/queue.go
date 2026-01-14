package main

type Queue[T any] struct {
    data []T
}

func (q *Queue[T]) Push(x T) {
    q.data = append(q.data, x)
}

func (q *Queue[T]) Pop() T {
    x := q.data[0]
    q.data = q.data[1:]
    return x
}

func (q *Queue[T]) Empty() bool {
    return len(q.data) == 0
}

