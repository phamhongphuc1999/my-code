## Simple api with Java maven and spark

### Run

- Start fuseki server

```shell
./fuseki-server --conf ./multiple-service.ttl
```

- Start API

Api will run with http://0.0.0.0:4567

### Try to run with docker

You should follow [documents](https://jena.apache.org/documentation/fuseki2/fuseki-docker.html) for more detail, but you can follow my brief instruction.

- Download .zip file in https://repo1.maven.org/maven2/org/apache/jena/jena-fuseki-docker/4.9.0/. You can use another fuseki version instead of 4.9.0.

- Unzip .zip file and begin running docker-compose by below command:

```shell
docker-compose build --build-arg JENA_VERSION=4.9.0
```

- After running successfully, you can start it:

```shell
docker-compose run --rm --service-ports fuseki --mem /ds
```

above command run n in-memory. If you want to load TDB2 database, you should run

```shell
mkdir -p databases/DB2
tdb2.tdbloader --loc databases/DB2 MyData.ttl
docker-compose run --rm --name MyServer --service-ports fuseki --update --loc databases/DB2 /ds
```
