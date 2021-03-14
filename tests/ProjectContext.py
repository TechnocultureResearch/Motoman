""" Easy fix: Adds the parent directory of this folder to system path """
""" Inserts the parent directory of the directory this script is within as a part of path variable """
import os, sys
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "..")))


""" Imports needed by tests """
from motors_manager import *
from motors_manager.commands.devices import ports