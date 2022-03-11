# %[name]%
---

- TODO: write brief project description



Documentation
---
The documentation for %[name]% is available at the following address:
- https://%[author]%.github.io/%[name]%/doc/html/index.html



Build system
---
NOTE: This project uses [cccmk](https://github.com/lexouduck/libccc/cccmk/) to harmonize files/styles across multiple projects/repositories.

%%if tracked(_if_ask_mkfile/Makefile)
This project is built using a cross-platform Makefile build system.
To learn more about what make scripts are provided, try `make help`, which will give a list of all rules and a brief description for each (the `make help-all` rule may also be of use).
%%end if

%%if is(lang,c)
This project is written in C, and is built using a C compiler (by default, typically `clang` or `gcc`/`mingw`), and uses `make` for dependency management.
%%end if
%%if is(lang,cpp)
This project is written in C++, is built using a C++ compiler (by default, typically `clang++` or `g++`), and uses `make` for dependency management.
%%end if
%%if is(lang,cs)
This project is written in C#, is built using `csc`, runs using `dotnet`, and uses `nuget` for dependency management.
%%end if
%%if is(lang,rs)
This project is written in Rust, is built using `rustc`, and uses `cargo` for dependency management.
%%end if
%%if is(lang,py)
This project is written in Python, and uses static type analysis tools (typically `mypy`, `pyre`, etc) to imitate a proper compilation process, and uses `pip` for dependency management.
%%end if
%%if is(lang,js)
This project is written in JavaScript, runs using `node`, and uses `npm` for dependency management.
%%end if
%%if is(lang,ts)
This project is written in TypeScript, is built using `tsc`, runs using `node`, and uses `npm` for dependency management.
%%end if
%%if is(lang,jsx)
This project is written in JavaScript with React, using `react-scripts`/`create-react-app`, and uses Node.js/NPM for package management.
%%end if
%%if is(lang,tsx)
This project is written in TypeScript with React, using `react-scripts`/`create-react-app`, and uses Node.js/NPM for package management.
%%end if



Contributing
---
Check `CONTRIBUTING.md`, which is the file that serves as a "contributions style guide" document.
This style described in it was chosen because it allows for more efficient version control and code review.
