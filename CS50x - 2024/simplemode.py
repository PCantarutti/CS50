def SimpleMode(arr):
  Aset = set(arr)
  modeC = 1
  modeN = arr[0]  # Inicializar o modo com o primeiro elemento da lista
  modeIndex = 0

  for i in Aset:
    count = arr.count(i)
    index = arr.index(i)

    if count > modeC:
      modeC = count
      modeN = i
      modeIndex = index
    elif count == modeC and index < modeIndex:
      # Se a frequência é a mesma e o índice é menor, atualiza o modo
      modeN = i
      modeIndex = index

  return modeN if modeC != 1 else -1

# keep this function call here
print(SimpleMode([5,5,2,2,1]))
