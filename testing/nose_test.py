from fac import factorial
from nose.tools import raises

def setup_module(module):
    module.dataset = {0:1, 1:1, 4:24, 10:3628800}

def test_factorial():
    for key,val in dataset.items():
        assert factorial(key) == val

@raises(ValueError)
def test_negative_factorial():
    factorial(-1)

@raises(ValueError)
def test_factorial_half():
    factorial(0.5)
