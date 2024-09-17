import sys

def main():

    if len(sys.argv) < 4:
        print("Uso: python calculadora.py (x) (operação) (y)")
        sys.exit(1)

    x = int(sys.argv[1])
    y = int(sys.argv[3])
    operacao = sys.argv[2]

    calculo(x, y, operacao)

def calculo(x, y, operacao):

    if operacao in ["+", "mais", "soma"]:
        print(f"resultado = {x + y}")
    elif operacao in ["-", "menos", "subtrair"]:
        print(f"resultado = {x - y}")
    elif operacao in ["/", "dividido", "divisão"]:
        print(f"resultado = {(x / y)}")

main()
