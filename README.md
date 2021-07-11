# httperror

A simple C program to query a list of HTTP error codes. Inspired by `errno` from [moreutils](https://joeyh.name/code/moreutils/).

# Building

`httperror` relies on the `getopt_long()` and `strcasestr()` extensions, so it will not work on all POSIX systems. However, it has been tested on Linux (glibc/musl), and it should also work on macOS and the BSDs.

```
git clone https://github.com/cptpcrd/httperror.git
cd httperror
make
```

This will create an executable called `httperror`. You can run it from the directory where the repo is cloned with e.g. `./httperror -l`. Alternatively, you can copy it to a directory on your `PATH` (e.g. `cp httperror ~/bin/`) to be able to call it as `httperror ...`.
