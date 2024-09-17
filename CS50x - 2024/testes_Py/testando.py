text = "My baby want a burkin why the hell do i work so hard"

for word in text.split():
    if "a" in word[1:]:
        print(word)
