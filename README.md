# clingo-sys [![Build Status](https://github.com/potassco/clingo-sys/workflows/CI%20Test/badge.svg)](https://github.com/potassco/clingo-sys)[![Latest Version](https://img.shields.io/crates/v/clingo-sys.svg)](https://crates.io/crates/clingo-sys)[![Rust Documentation](https://docs.rs/clingo-sys/badge.svg)](https://docs.rs/clingo-sys)

Rust raw FFI bindings to the C API of [clingo](https://github.com/potassco/clingo) library.
Clingo version 5.8.3.

## Requirements library

Per default the crate uses the clingo library via dynamic linking.
It is assumed that a clingo dynamic library is installed on the system.
You have to set the environment variable `CLINGO_LIBRARY_PATH`. For example:

```sh
export CLINGO_LIBRARY_PATH=/scratch/miniconda3/envs/test/lib
```

## Using `static-linking`

The crate defines a [Cargo feature] that allows to use the clingo library via static linking.

The recommended way to use the optional static linking support is as
follows.

```toml
[dependencies]
clingo-sys = { version = "0.8.0", features = ["static-linking"] }
```

To build clingo for static linking you need the following tools installed:

- a C++14 conforming compiler
  - *at least* [GCC](https://gcc.gnu.org/) version 4.9
  - [Clang](http://clang.llvm.org/) version 3.1 (using either libstdc++
    provided by gcc 4.9 or libc++)
  - *at least* MSVC 15.0 ([Visual Studio](https://www.visualstudio.com/) 2017)
  - other compilers might work
- the [cmake](https://www.cmake.org/) build system
  - at least version 3.18 is recommended
  - at least version 3.10 is *required*

### Accessing clasp

With `static-linking`, the crate also builds a few C wrappers around clasp's `ClaspFacade`
(see `clasp_shim.cpp`), for example `clingo_sys_clasp_facade_num_vars()`.
They take the pointer returned by `clingo_control_clasp_facade()`.

To write further C++ code against clasp, depend on `clingo-sys` with `static-linking` directly.
Its build script passes the directory with the installed clingo, clasp and potassco headers to
the build scripts of dependent crates as `DEP_CLINGO_INCLUDE`:

```rust
// build.rs
fn main() {
    cc::Build::new()
        .cpp(true)
        .std("c++14")
        .include(std::env::var("DEP_CLINGO_INCLUDE").unwrap())
        .file("my_clasp.cpp")
        .compile("my_clasp");
}
```

Inside, the facade pointer can be cast to `Clasp::ClaspFacade*`.
Note that clingo considers this access experimental and not part of its stable API,
and that the code has to be compiled against the clasp version shipped with this crate.

[Cargo feature]: https://doc.rust-lang.org/cargo/reference/manifest.html#the-features-section
