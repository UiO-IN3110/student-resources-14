import sys
import numpy as np
import cProfile
import pstats
from scipy import weave


def numpy_filter(x):
    "filtering using iterations over numpy arrays"

    out = np.empty(len(x))
    out[0] = x[0]
    for i in xrange(1, len(x)-1):
        out[i] = .25*x[i-1] + .5*x[i] + .25*x[i+1]
    out[-1] = x[-1]
    return out


def weave_filter(x):
    "filtering using Weave inline"

    out = np.empty(len(x))
    length = len(x)
    code = r"""
        out[0] = x[0] ;
        for (int i=1; i<length-1; i++)
            out[i] = .25*x[i-1] + .5*x[i] + .25*x[i+1] ;
        out[length-1] = x[length-1] ;
    """
    io = ["x", "length", "out"]
    weave.inline(code, io)
    return out


if __name__ == "__main__":

    order = len(sys.argv) == 1 and 5 or int(sys.argv[1])
    x = np.cumsum(np.random.normal(0, 1, 10**order))

    cProfile.run("numpy_filter(x)", "numpy_timing")
    pstats.Stats("numpy_timing").sort_stats("cumulative").print_stats()

    cProfile.run("weave_filter(x)", "weave_timing")
    pstats.Stats("weave_timing").print_stats("weave_examples\.py")
    # Apparently we can filter on regex!
