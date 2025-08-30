sudo apt-get update
cargo install wasm-pack

wget https://github.com/WebAssembly/binaryen/releases/download/version_117/binaryen-version_117-x86_64-linux.tar.gz
tar -xvf binaryen-version_117-x86_64-linux.tar.gz
sudo mv binaryen-version_117/bin/* /usr/local/bin/
