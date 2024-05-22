import random
import string

def generate_atomic_data():
    atomic_number = random.randint(1, 25)
    symbol = ''.join(random.choices(string.ascii_uppercase, k=2))
    name = ''.join(random.choices(string.ascii_uppercase, k=8))  
    atomic_weight = round(random.uniform(1.0, 100.0), 3)
    period = random.randint(1, 7)
    group = random.randint(1, 18)
    return f"{atomic_number} {symbol} {name} {atomic_weight} {period} {group}\n"

with open("random_data.txt", "w") as file:
    for _ in range(200):  #
        file.write(atomic_data)
