<h1>Ubuntu environment</h1>

Setup a simple ubuntu environment for run openmp and mpi

## Run

### 1. Start docker container

```shell
docker-compose up -d
```

### 2. Inject to docker container

```shell
docker exec -it my-ubuntu bin/bash
```

### 3. Setup your ubuntu

```shell
./setup.sh
```

## Reference

- https://www.nginx.com/blog/what-are-namespaces-cgroups-how-do-they-work/
