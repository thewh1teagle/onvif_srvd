FROM ubuntu:18.04

RUN apt-get update && apt-get install -y  \
	bash-completion vim nano git curl wget unzip \
	g++-arm-linux-gnueabihf make file tmux \
	g++ zlib1g-dev flex bison byacc

RUN echo deb [arch=arm64,armhf,ppc64el,s390x] http://ports.ubuntu.com/ubuntu-ports/ bionic main restricted universe multiverse > /etc/apt/sources.list && \
    echo deb [arch=arm64,armhf,ppc64el,s390x] http://ports.ubuntu.com/ubuntu-ports/ bionic-updates main restricted universe multiverse >> /etc/apt/sources.list && \
    echo deb [arch=arm64,armhf,ppc64el,s390x] http://ports.ubuntu.com/ubuntu-ports/ bionic-backports main restricted universe multiverse >> /etc/apt/sources.list && \
    echo deb [arch=arm64,armhf,ppc64el,s390x] http://ports.ubuntu.com/ubuntu-ports/ bionic-security main restricted universe multiverse >> /etc/apt/sources.list && \
    dpkg --add-architecture armhf 

RUN apt-get update && apt-get install -y  \
    libssl1.0-dev:armhf openssl1.0:armhf liblz-dev:armhf liblz-dev zlib1g-dev:armhf

RUN mkdir /src
WORKDIR /src
