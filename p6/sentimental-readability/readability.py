txt = input("Text: ")
let_ter = 0
sen = 0
wo = len(txt.split())

for i in txt:
    if i.isalpha() == True:
        let_ter += 1
    elif i == "?" or i == "!" or i == ".":
        sen += 1

L = 100 * (let_ter / wo)
S = 100 * (sen / wo)
ind = round(0.0588 * L - 0.296 * S - 15.8)

if ind < 1:
    print("Before Grade 1")
elif ind >= 16:
    print("Grade 16+")
else:
    print(f"Grade {ind}")
