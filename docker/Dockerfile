FROM ubuntu:18.04

RUN apt-get update && apt-get install -y  \
	bash-completion vim nano git curl wget unzip \
	g++-arm-linux-gnueabihf make file tmux \
	g++ libssl-dev zlib1g-dev flex bison byacc
RUN mkdir /src
WORKDIR /src
