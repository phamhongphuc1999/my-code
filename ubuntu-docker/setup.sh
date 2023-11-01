#! /bin/bash

Green='\033[0;32m'
NC='\033[0m'

printf "${Green}Step 1: Update${NC}\n"
apt -y update && apt -y upgrade

printf "${Green}Step 2: Install sudo${NC}\n"
apt -y install sudo
printf "${Green}Step 2.1: Check sudo version${NC}\n"
sudo --version

printf "${Green}Step 3: Re-udpate${NC}\n"
sudo apt update && sudo apt upgrade

printf "${Green}Step 4: Install clang${NC}\n"
sudo apt -y install clang

printf "${Green}Step 4.1: Check clang version${NC}\n"
clang --version

printf "${Green}Step 5: Install g++${NC}\n"
sudo apt -y install build-essential

printf "${Green}Step 5.1: Check g++ version${NC}\n"
g++ --version

printf "${Green}Step 6: Install mpicc${NC}\n"
sudo apt -y install mpich

printf "${Green}Step 6.1: Check mpicc version${NC}\n"
mpicc --version

printf "${Green}Step 7: Install libomp${NC}\n"
sudo apt -y install libomp-dev

printf "${Green}Step 8: Install vim${NC}\n"
sudo apt -y install vim

printf "${Green}Step 8.1: Check vim version${NC}\n"
vim --version

printf "${Green}Step 9: Install python environment${NC}\n"
sudo apt-get -y install python-dev python-pip python3-dev python3-pip

printf "${Green}Step 10: Install neovim${NC}\n"
sudo add-apt-repository ppa:neovim-ppa/stable
sudo apt-get update
sudo apt-get -y install neovim

printf "${Green}Step 10.1: Check neovim version${NC}\n"
nvim --version

printf "${Green}Step 11: Install make${NC}\n"
sudo apt -y install make

printf "${Green}Step 11.1: Check make version${NC}\n"
make --version

printf "${Green}Step 12: Install some useful plugins${NC}\n"
sudo apt -y install curl wget git zsh

printf "${Green}Step 13: Install oh my zsh${NC}\n"
sh -c "$(curl -fsSL https://raw.github.com/ohmyzsh/ohmyzsh/master/tools/install.sh)"
