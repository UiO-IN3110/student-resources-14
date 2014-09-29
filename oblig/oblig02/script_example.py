#!/usr/bin/env python

def factorial(order):
    """
Calculate the factorial of an integer.

Parameters
----------
order : int
    Input argument

Returns
-------
fact : int, long
    The factorial of `order`.

Example
-------
>>> factorial(3)
6.0
    """
    out = 1.
    for o in xrange(2, order+1):
        out *= o
    return out

if __name__=="__main__":
    import sys
    if len(sys.argv)>1:
        print factorial(int(sys.argv[1]))

    import doctest
    doctest.testmod()
