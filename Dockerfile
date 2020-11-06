FROM ubuntu:18.04

RUN apt-get update && apt-get install -y  \
	bash-completion vim nano git curl wget unzip \
	g++-arm-linux-gnueabihf make file tmux \
	g++ libssl-dev zlib1g-dev flex bison byacc

RUN echo deb http://ports.ubuntu.com/ubuntu-ports/ bionic main restricted universe multiverse >> /etc/apt/source/list
RUN echo deb http://ports.ubuntu.com/ubuntu-ports/ bionic-updates main restricted universe multiverse >> /etc/apt/source/list
RUN echo deb http://ports.ubuntu.com/ubuntu-ports/ bionic-backports main restricted universe multiverse >> /etc/apt/source/list
RUN echo deb http://ports.ubuntu.com/ubuntu-ports/ bionic-security main restricted universe multiverse >> /etc/apt/source/list
RUN dpkg --add-architecture armhf

RUN apt-get install -y openssl:armhf libssl-dev:armhf
RUN apt-get install liblz-dev:armhf liblz-dev zlib1g-dev:armhf

RUN mkdir /src
WORKDIR /src
