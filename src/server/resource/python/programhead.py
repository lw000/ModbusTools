#!/usr/bin/python

from os import sys, path
from time import sleep, time
import argparse

_parser = argparse.ArgumentParser()
_parser.add_argument('-prj', '--project', type=str, default="")
_parser.add_argument('-imp', '--importpath', type=str, default="")
_parser.add_argument('-i', '--memid' , type=str, default="")
_parser.add_argument('-p', '--period' , type=int, default=100)
_args = _parser.parse_args()

_pathList = _args.importpath.split(";")

sys.path.insert(0, path.normpath(path.dirname(path.abspath(__file__))))
sys.path.extend(_pathList)

from mbserver import _MbDevice

mbdevice = _MbDevice(_args.memid, _args.project)
mem0x = mbdevice.getmem0x()
mem1x = mbdevice.getmem1x()
mem3x = mbdevice.getmem3x()
mem4x = mbdevice.getmem4x()

_mb_time_period = _args.period / 1000

