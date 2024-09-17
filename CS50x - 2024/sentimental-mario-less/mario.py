from cs50 import get_int

while True:
    altura = get_int("Height: ")
    if altura > 0 and altura < 9:
        break

for i in range(altura):
    print(" " * (altura - i - 1) + "#" * (i + 1), end='')
    print("  "+ "#" * (i + 1))
