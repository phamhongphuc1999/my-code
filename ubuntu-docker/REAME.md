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

## References

- https://www.tecmint.com/install-oh-my-zsh-in-ubuntu/
- https://qirolab.com/posts/install-and-setup-oh-my-zsh-on-ubuntu-system
