# cccmk

`cccmk` is a Makefile build system management tool. The name is derived from libccc/CCC/++C, and the aim is to have a build system tool akin to several modern programming languages (like `cargo` for Rust, or `npm/npx` for JavaScript/TypeScript).

`cccmk` is meant only as a tool to use and maintain several makefiles, which themselves hold the logic to do dependency management, version number management, etc.

`cccmk` is implemented entirely in `.sh` shell scripts, so it is fully modifiable by the end-user (the license is MIT, you are free to do whatever you wish).



### Project folder structure

- `./project`: holds the template source files used when creating a new project with `cccmk new`.
- `./scripts`: holds the source code sheel scripts which make up the `cccmk` toolchain.
