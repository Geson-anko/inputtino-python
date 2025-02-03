from importlib import metadata
from ._core import hello_from_bin

__version__ = metadata.version("inputtino-python")

def hello() -> str:
    return hello_from_bin()
