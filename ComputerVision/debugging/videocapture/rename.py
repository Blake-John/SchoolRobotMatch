import os

n = 441

for file in range (800, 1050) : 
    os.rename (f"./data640p2/{file}.jpg", f"./data640p2/{n}.jpg")
    n += 1
