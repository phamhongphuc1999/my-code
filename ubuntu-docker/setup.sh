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

printf "${Green}Step 9: Install make${NC}\n"
sudo apt -y install make

printf "${Green}Step 9.1: Check make version${NC}\n"
make --version
