# TODO

while True:
    try:
        Hight_1_8 = int(input("Height: "))
        if 1 <= Hight_1_8 <= 8:
            break
    except ValueError:
        continue

for i in range(Hight_1_8):
    print((Hight_1_8 - i - 1) * " ", (i + 1) * "#", "  ", (i + 1) * "#", sep="")
