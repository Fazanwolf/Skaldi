FROM alpine:latest

RUN apk update && apk add --no-cache \
    bash curl git cmake make g++

COPY . /app

WORKDIR /app

RUN cmake -B build -S .

RUN cmake --build build --config Release