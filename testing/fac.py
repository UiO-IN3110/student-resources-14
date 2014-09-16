def factorial(order):
    """
Calculate the factorial for an integer.

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

    if int(order)-order != 0.:
        raise ValueError, "order must be integer"

    if order<0:
        raise ValueError, "order must be non-negative"

    out = 1.
    for o in xrange(2, order+1):
        out *= o
    return out


