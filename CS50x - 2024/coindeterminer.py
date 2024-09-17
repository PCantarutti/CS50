def CoinDeterminer(num):

  coin = 0

  while num >= 9:
    num -= 9
    coin += 1

  while num >= 7:
    num -= 7
    coin += 1

  while num >= 5:
    num -= 5
    coin += 1

  while num >= 1:
    num -= 1
    coin += 1

  return coin

# keep this function call here
print(CoinDeterminer(input()))
