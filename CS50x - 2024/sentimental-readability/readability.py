from cs50 import get_string


def main():

    quantidade = {
        "letras": 0,
        "palavras": 1,
        "frases": 0,
    }

    texto = get_string("Text: ")

    count_text(texto, quantidade)

    letras = quantidade["letras"]
    palavras = quantidade["palavras"]
    frases = quantidade["frases"]

    L = letras / palavras * 100
    S = frases / palavras * 100
    index = 0.0588 * L - 0.296 * S - 15.8
    grade = round(index)

    print(grade)
    print(f"Letras: {quantidade['letras']}")
    print(f"Palavras: {quantidade['palavras']}")
    print(f"Frases: {quantidade['frases']}")

    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print("Grade", grade)


def count_text(texto, quantidade):

    for char in texto:
        if char.isalpha():
            quantidade["letras"] += 1
        elif char == " ":
            quantidade["palavras"] += 1
        elif char in [".", "!", "?"]:
            quantidade["frases"] += 1


main()
