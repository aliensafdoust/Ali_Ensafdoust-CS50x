while True:
    long_number = str(input("Number: "))
    if long_number.isnumeric():
        break
    else:
        continue
long = int(long_number)

list_1 = 0
list_2 = 0
while long > 0:
    mod_1 = long % 10
    long = int(long / 10)
    list_1 += mod_1

    mod_2 = long % 10
    long = int(long / 10)
    mod_2 = mod_2 * 2

    if mod_2 >= 10:
        d1 = mod_2 % 10
        d2 = int(mod_2 / 10)
        list_2 += d1 + d2
    else:
        list_2 += mod_2

f_two = int(long_number[0:2])
count = len(long_number)

if (list_1 + list_2) % 10 == 0:
    if f_two in [34, 37] and count == 15:
        print("AMEX")
    elif f_two in range(51, 56) and count == 16:
        print("MASTERCARD")
    elif int(long_number[0]) == 4 and (count == 16 or count == 13):
        print("VISA")
    else:
        print("INVALID")

else:
    print("INVALID")
