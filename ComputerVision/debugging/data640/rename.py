import os

file_list = os.listdir ("./images_argumented/")

for i in range (441, 441 + len (file_list)) : 
    os.system (f"cp ./labels/{i - 441}.txt ./images_arg_order/labels/{i}.txt")
