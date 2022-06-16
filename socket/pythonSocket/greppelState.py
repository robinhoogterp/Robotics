import json
from json import JSONEncoder
from random import seed
import random
import json
import socketConnector

sc = socketConnector.SocketConnector()


class greppelState:
    def __init__(self):
        self.json = ""

    def getState(self):
        # print(self.xCoord)
        sc.getState()
        self.json = sc.getJson()

    def getJson(self):
        return self.json

    def passXPos(self, xpos):
        sc.setXPos(xpos)