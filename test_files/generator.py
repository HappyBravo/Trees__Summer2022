import time
import random

# GENERATING n RANDOM NUMBERS AND SAVING THOSE IN filename 
def generate(n, filename, min_limit = 0, max_limit = 10000): 
    f = open(filename, 'w')
    for i in range(n):
        j = random.randint(min_limit, max_limit)
        f.write(f"{j}, ")
    f.close()

if __name__ == "__main__":
    cases = [10**i for i in range(1, 7)]

    for i in range(len(cases)):
        name = f"test_{cases[i]}.txt"
        generate(cases[i], name)
