FROM ubuntu:20.04

RUN ln -fs /usr/share/zoneinfo/Europe/London /etc/localtime
RUN apt update -y
RUN apt install clang-10 clang-format-10 clang-tidy-10 clang-tools-10 libvulkan-dev gyp git cmake make -y