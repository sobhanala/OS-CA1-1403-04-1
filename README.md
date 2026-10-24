# Operating Systems — Networked Competition Project

A C++ client/server coursework project using Linux sockets. The domain includes players on red/blue teams, spectators, arbiters, and server-side rooms.

## Structure

- `main/src/`: client and server entry points.
- `helpers/`: networking and command-handling helpers.
- `common/`: shared definitions and utilities.
- `roles/`: participant roles.
- `Makefile`: build rules.

## Build and run

Use Linux, GNU Make, and a C++11-compatible compiler:

```sh
make
```

The build creates `server.out` and `client.out`. Review `socket_by_cli` in `common/src/utils.cpp` and the constants in `common/include/` for the address/port arguments and broadcast settings before launching the programs.

This snapshot is intended for local socket-programming experiments. It does not include a complete automated test suite or deployment setup.

## Credits and source

This is a public portfolio copy of the shared project [BehradElmi/OS-CA1-1403-04-1](https://github.com/BehradElmi/OS-CA1-1403-04-1), prepared for Sobhan Alaeddini's account. Original authorship and existing license notices are retained. See [SOURCE.md](SOURCE.md) for the source revision and publication notes.
