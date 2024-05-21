## My rust tutorial

### Config

1. Install dev container for VSCode

```shell
code --install-extension ms-vscode-remote.remote-containers
npm install -g @devcontainers/cli
```

2. Up your image

```shell
devcontainer up --workspace-folder .
```

3. Attach

- To attach to a Docker container, either select Dev Containers: Attach to Running Container... from the Command Palette(read [here](https://code.visualstudio.com/docs/devcontainers/attach-container))

4. Run project

```shell
cargo run
```

- If you want to see docs, you can run following command line to generate docs

```shell
cargo doc --open
```

### Reference

-   https://code.visualstudio.com/docs/devcontainers/devcontainer-cli
