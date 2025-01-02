FROM ubuntu:20.04

RUN apt-get update && apt-get install -y \
    build-essential \
    nasm \
    gcc \
    libgcc-10-dev \
    binutils \
    make \
    wget \
    curl \
    && rm -rf /var/lib/apt/lists/*

RUN apt-get update && apt-get install -y \
    gcc-multilib \
    binutils-mingw-w64-i686 \
    && rm -rf /var/lib/apt/lists/*

ENV PREFIX=/root/opt/cross \
    TARGET=i686-elf \
    PATH=/root/opt/cross/bin:$PATH


WORKDIR /project

COPY . .

CMD [ "make", "-c", "make clean && ./build.sh" ]