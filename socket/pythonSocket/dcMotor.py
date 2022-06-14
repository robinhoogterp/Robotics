from random import seed
import random


class dcMotor:
    def __init__(self, pin_forward):
        self.pin = pin_forward
        self.ran1 = random.randint(0, 100)

