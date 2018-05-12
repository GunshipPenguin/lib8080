# i8080
[![Travis branch](https://img.shields.io/travis/GunshipPenguin/i8080/master.svg)](https://travis-ci.org/GunshipPenguin/i8080)

A well tested, cycle accurate emulation library for the Intel 8080 written
in C99.

Currently under construction.

## Building

i8080 uses Cmake as its build system. To build it, use:

```
cmake .
make -j2
```

## Tests

i8080 is heavily tested using
[AttoUnit](https://github.com/GunshipPenguin/attounit). Unit tests are located
in `test/unit`. Every CPU instruction is tested at least once, with many having
multiple tests to verify correct behaviour with regard to status flags / edge
cases, etc.

To run the unit tests, first build i8080 using Cmake as above, then run:

```
./i8080test
```

This repository also contains two CP/M test binaries that verify the
functionality of the 8080 pretty comprehensively. They are:

- CPUTEST.COM by Supersoft Associates
- TEST.COM by Microcosm Associates

These binaries are located in `test/integration/test_bins`, and files containing
their expected output are located in `test/integration/test_bins/output`.

They can be easily run using the binloader program (built with make target of
the same name). Binloader emulates a very minimal CP/M system only supporting
BDOS functions 2 and 9 (output character and output string).

As an example, to use binloader to run TEST.COM from the top level directory,
use:

```
./binloader test/integration/test_bins/TEST.COM
```

The `integrationtest.sh` script automatically runs both test binaries using
binloader.

## License

[MIT](https://github.com/GunshipPenguin/i8080/blob/master/LICENSE) © Rhys Rustad-Elliott

[CP/M binaries used for
testing](https://github.com/GunshipPenguin/i8080/tree/master/test/integration/test_bins)
are copyright their respective owners:
- CPUTEST.COM © 1981 Supersoft Associates
- TEST.COM © 1980 Microcosm Associates
