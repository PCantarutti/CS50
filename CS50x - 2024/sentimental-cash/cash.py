from cs50 import get_float

coin = 0

while True:
    cash = get_float("Change: ")
    if cash > 0:
        break

while cash >= 0.25:
    cash -= 0.25
    coin += 1
    cash = round(cash, 2)

while cash >= 0.10:
    cash -= 0.10
    coin += 1
    cash = round(cash, 2)

while cash >= 0.05:
    cash -= 0.05
    coin += 1
    cash = round(cash, 2)

while cash >= 0.01:
    cash -= 0.01
    coin += 1
    cash = round(cash, 2)

print(coin)
