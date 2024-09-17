from cs50 import get_int

s = input("Você concorda? ").lower()

if s in ["y", "yes"]:
   print("Concorda")
elif s in ["n", "no"]:
   print("Não concorda")
