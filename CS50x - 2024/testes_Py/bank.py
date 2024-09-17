from cs50 import get_string

text = (get_string("Greeting: ")).lower()
lista = text.split()
intro = lista[0]
reward = 0

for word in lista:
    if word[0:5] == "hello":
        reward = 0
        break
    elif "h" in intro[0]:
        reward = 20
        break
else:
    reward = 100

print(f"${reward}")


