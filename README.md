# simple-bbp-gmp-pi
Compute Pi in C using GMP and BBP formula 

    Usage: pi [nth digit] [file]

Compute the nth digit of pi using the [BBP-formula](https://en.wikipedia.org/wiki/Bailey%E2%80%93Borwein%E2%80%93Plouffe_formula) and write it to stdout or a file. The implementation is in C and based on [GMP](https://gmplib.org/). The goal was to provide an easy understandable, straight forward implementation and not performance.

Related information:
 - [https://bellard.org/pi/](https://bellard.org/pi/)
 - [https://gmplib.org/pi-with-gmp.html](https://gmplib.org/pi-with-gmp.html)
 - [http://www.numberworld.org/y-cruncher/](http://www.numberworld.org/y-cruncher/)
