import py.test
from fac import factorial

def setup_module(module):
    module.dataset = {0:1, 1:1, 4:24, 10:3628800}

def test_factorial():
    for key,val in dataset.items():
        assert factorial(key) == val

def test_negative_factorial():
    with py.test.raises(ValueError):
        factorial(-1)

def test_factorial_half():
    with py.test.raises(ValueError):
        factorial(0.5)
