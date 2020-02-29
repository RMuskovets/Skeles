FROM ubuntu:18.04

USER root

RUN apt-get update && apt-get install -y \
    wget \
    gcc g++ make binutils \
    qemu \
    build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo

# Installing i386-elf-*

RUN wget -O toolchain.sh https://github.com/RMuskovets/cross-compiler/raw/master/gcc830-binutils230.sh
RUN source toolchain.sh