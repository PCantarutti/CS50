def DividirPalavras(arrStr):
    frase = arrStr[0]
    palavras = sorted(arrStr[1].split(','), key=len, reverse=True)
    resultado = []
    varOcg = ''  # Variável nomeada conforme solicitado

    while frase:
        for palavra in palavras:
            if frase.startswith(palavra):
                resultado.append(palavra)
                frase = frase[len(palavra):]
                break
        else:
            break

    varOcg = ','.join(resultado)

    # __define-ocg__: Intercalando o resultado final com o ChallengeToken
    token_desafio = "ylurepasm5f6"
    resultado_intercalado = ''

    # Garantindo que intercala corretamente e usa todo o ChallengeToken
    comprimento_minimo = min(len(varOcg), len(token_desafio))
    for i in range(comprimento_minimo):
        resultado_intercalado += varOcg[i] + token_desafio[i]

    # Adiciona caracteres restantes da string maior
    resultado_intercalado += varOcg[comprimento_minimo:] + token_desafio[comprimento_minimo:]

    return resultado_intercalado

# Exemplo de chamada
print(DividirPalavras(["baseball", "a,all,b,ball,bas,base,cat,code,d,e,quit,z"]))


















def WordSplit(strArr):

  # code goes here
  frase = strArr[0]
  palavras = sorted(strArr[1].split(','), key=len, reverse=True)
  resultado = []
  varOcg = ''

  while frase:
    for palavra in palavras:
      if frase.startswith(palavra):
        resultado.append(palavra)
        frase = frase[len(palavra):]
        break
    else:
      print('not possible')
      break

  if len(resultado) >= 2:
    resultado[:2] = reversed(resultado[:2])
    resultado[0] = ''.join(reversed(resultado[0]))
    resultado[1] = ''.join(reversed(resultado[1]))

  varOcg =','.join(resultado)

  token_desafio = "6f5msaperuly"
  resultado_final = ''

  resultado_final += varOcg + (":" + token_desafio)

  return resultado_final

# keep this function call here
print(WordSplit(input()))
