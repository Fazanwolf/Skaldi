FROM ubuntu:latest

# Update and upgrade
RUN apt-get update -y && apt-get upgrade -y

# Base dependencies
RUN apt-get install -y gcc-multilib g++ cmake git fd-find lsb-release wget software-properties-common gnupg
# Graphical dependencies
RUN apt-get install -y libglfw3 libglfw3-dev libx11-dev libxcursor-dev libxrandr-dev libudev-dev libopenal-dev libvorbis-dev libflac-dev libfreetype-dev libfreetype6 libfreetype6-dev

# Install clang 16
RUN wget https://apt.llvm.org/llvm.sh && chmod +x llvm.sh && ./llvm.sh 16
RUN apt-get install -y clang-format-16 clang-tidy-16 clang-16

# Set working directory
WORKDIR /app

# Copy source files
ONBUILD COPY . /app

# Build project
ONBUILD RUN cmake -B build -S .
ONBUILD RUN cmake --build build --config Release