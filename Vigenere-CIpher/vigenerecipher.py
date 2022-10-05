

def main():
    choice = ""

    while True:
        print("===============================")
        print("HILL CIPHER")
        print("1. Encrypt")
        print("2. Decrypt")
        print("3. Exit")
        choice = input("Please chose action (1/2/3): ")

        match choice:
            case "1":
                plainText = input("Input plaintext: ")
                key = input("Input Key: ")
                print("Hasil Enkripsi: " + encryption(key, plainText))

            case "2":
                cipherText = input("Input ciphertext: ")
                key = input("Input Key: ")
                print("Hasil Enkripsi: " + decryption(key, cipherText))
            
            case "3":
                print("BYE BYE")
                break
            case _:
                print("please choose given choice")

def encryption(key: str, text: str) -> str:
    encrypted = ""

    symbol = {}
    text_list = list(text)

    for i in range(len(text)):
        if not text[i].isalpha():
            symbol[i] = text[i]
            text_list.remove(text[i])
    text = ''.join(text_list)

    upper = []
    for i in range(len(text)):
        if text[i].isupper():
            upper.append(i)

    text = text.lower()
    key = key.lower()

    i = 0
    while(len(key) != len(text)):
        if(i == len(key)):
            i = 0
        key += key[i]
        i += 1

    for i in range(len(text)):
        encrypted += chr((ord(text[i]) - ord('a') +
                         ord(key[i]) - ord('a')) % 26 + ord('a'))

    for i in range(len(upper)):
        encrypted = encrypted[:upper[i]] + \
            encrypted[upper[i]].swapcase() + encrypted[upper[i]+1:]

    for x, y in symbol.items():
        encrypted = encrypted[:x] + y + encrypted[x:]

    return encrypted


def decryption(key: str, text: str) -> str:
    decrypted = ""

    symbol = {}
    text_list = list(text)

    for i in range(len(text)):
        if not text[i].isalpha():
            symbol[i] = text[i]
            text_list.remove(text[i])
    text = ''.join(text_list)

    upper = []
    for i in range(len(text)):
        if text[i].isupper():
            upper.append(i)

    text = text.lower()
    key = key.lower()

    i = 0
    while(len(key) != len(text)):
        if(i == len(key)):
            i = 0
        key += key[i]
        i += 1

    print()
    for i in range(len(text)):
        decrypted += chr(((ord(text[i]) - ord('a')) -
                         (ord(key[i]) - ord('a'))) % 26 + ord('a'))

    for i in range(len(upper)):
        decrypted = decrypted[:upper[i]] + \
            decrypted[upper[i]].swapcase() + decrypted[upper[i]+1:]

    for x, y in symbol.items():
        decrypted = decrypted[:x] + y + decrypted[x:]

    return decrypted


if __name__ == "__main__":
    main()
