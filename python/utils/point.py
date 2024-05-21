class Point:
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

    def __add__(self, other):
        if isinstance(other, Point):
            new_x = self.x + other.x
            new_y = self.y + other.y
            return Point(new_x, new_y)
        else:
            raise TypeError("Can't add not-Point object to Point")

    def __mul__(self, scalar):
        if isinstance(scalar, (int, float)):
            return Point(self.x * scalar, self.y * scalar)
        else:
            raise TypeError("Can't multiply something other than point and a scalar")

    def __str__(self):
        return f'({self.x}, {self.y})'

    def __repr__(self):
        return f'Point(x={self.x}, y={self.y})'

    def translate(self, dx, dy):
        self.x += dx
        self.y += dy
