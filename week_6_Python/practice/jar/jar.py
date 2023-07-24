class Jar:
    def __init__(self, capacity=12):
        if capacity < 0:
            raise ValueError
        self.cookies = []
        self._capacity = capacity

    def __str__(self):
        if len(self.cookies) == 0:
            return f"0"
        return f"{self.cookies[0] * len(self.cookies)}"

    def deposit(self, n):
        for i in range(n):
            if len(self.cookies) >= 12:
                return ValueError
            self.cookies.append("#")


    def withdraw(self, n):
        for i in range(n):
            if len(self.cookies) == 0:
                return ValueError
            self.cookies.pop(0)

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return len(self.cookies)


def main():
    jar = Jar()
    print(str(jar.capacity))
    jar.deposit(100)
    jar.withdraw(15)
    print(str(jar))
    print(jar.size)


main()