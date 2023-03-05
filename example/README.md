# Skaldi example

This is a simple example of how to use Skaldi.

## Installation

## Usage

```bash
USAGE
./test [flag]
-h, --help      Display this help message.
-v, --version   Display the version of the library.
./test base type [ip] port
base            The base network that you want, server or client.
type            The type of socket connection, TCP or UDP.
[ip]            The target ip, needed only for client base.
port            The port to use."

EXAMPLES
./test server udp 5000"               
./test client udp 0.0.0.0 5000"       
./test server tcp 5001"               
./test client tcp 0.0.0.0 5001

Skaldi is a library free of use by anyone and developped by Fazanwolf.\
```

## Contributors

* [Fazanwolf](https://github.com/Fazanwolf)

## License

[MIT](../LICENSE)