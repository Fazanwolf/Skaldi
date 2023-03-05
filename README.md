# Skaldi

Skaldi is a simple C++ library for creating and managing UDP and TCP server.

## Description

Skaldi is a simple C++ library for creating and managing UDP and TCP server. It is based on the [Boost::Asio](https://www.boost.org/doc/libs/1_76_0/doc/html/boost_asio.html) library.

## Getting Started

### Dependencies

Languages:
* [C++17](https://en.cppreference.com/w/cpp/17) - C++17 is the latest version of the C++ programming language, standardized by the International Organization for Standardization (ISO) in 2017.

Libraries:
* [Boost](https://www.boost.org/) - Boost is a set of libraries for the C++ programming language that provides support for tasks and structures such as linear algebra, pseudorandom number generation, multithreading, image processing, regular expressions, and unit testing.
* [spdlog](https://github.com/gabime/spdlog) - Very fast, header-only/compiled, C++ logging library.

Tools:
* [Git](https://git-scm.com/) - Git is a free and open source distributed version control system designed to handle everything from small to very large projects with speed and efficiency.
* [CMake](https://cmake.org/) - CMake is an open-source, cross-platform family of tools designed to build, test and package software.
* [Doxygen](https://www.doxygen.nl/index.html) - Doxygen is a documentation system for C++, C, Java, Objective-C, Python, IDL (Corba, Microsoft, and UNO/OpenOffice flavors), Fortran, VHDL, PHP, C#, and to some extent D.
* [Docker](https://www.docker.com/) - Docker is a set of platform as a service (PaaS) products that use OS-level virtualization to deliver software in packages called containers.

### Building

#### Manually

```bash
cmake -B build -S .
cmake --build build --config Release
```

#### With docker

```bash
# Building the image
docker build -t skaldi .
# Running the container
docker run -it --rm --name skaldi skaldi
```

### Executing program

Refer to the [example](example/README.md) folder.

## Help

If you have any questions, feel free open an issue on the [GitHub repository](https://github.com/Fazanwolf/Skaldi/issues)

## Authors

* [Fazanwolf](https://github.com/Fazanwolf)
* [Alwyn974](https://github.com/Alwyn974)

## License

This project is licensed under the [MIT License](LICENSE) - see the LICENSE file for details.