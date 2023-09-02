## Getting Started

Welcome to the VS Code Java world. Here is a guideline to help you get started to write Java code in Visual Studio Code.

## Folder Structure

The workspace contains two folders by default, where:

- `src`: the folder to maintain sources
- `lib`: the folder to maintain dependencies

Meanwhile, the compiled output files will be generated in the `bin` folder by default.

> If you want to customize the folder structure, open `.vscode/settings.json` and update the related settings there.

## Dependency Management

The `JAVA PROJECTS` view allows you to manage your dependencies. More details can be found [here](https://github.com/microsoft/vscode-java-dependency#manage-dependencies).

## Test connection to fuseki database

#### 1. Run database

- First, you make sure you have fuseki-server to run server
- I run fuseki with a .ttl config file

```shell
./fuseki-server --conf ./multiple-service.ttl
```

#### 2. Try to connect to database

## Get start

- This is just a very simple [apache-jena](https://jena.apache.org/) project. The first thing you must prepare is making sure you installed Java and downloaded [apache-jena library](https://jena.apache.org/download/index.cgi).
- Then, you have to import jena JAR to your java project. Personally, I use VSCode so some config steps certainly differ from using other IDE or editor.
- For someone who want to use VScode like me, you should read [document](https://code.visualstudio.com/docs/java/java-tutorial) before starting.
- For more detail about jena package, you can read [here](https://jena.apache.org/documentation/javadoc/jena). For more detail about how to connect to fuseki, you can read [here](https://jena.apache.org/documentation/rdfconnection/). Finally, if you want to learn more about jena, you can find all documents [here](https://jena.apache.org/documentation/).
