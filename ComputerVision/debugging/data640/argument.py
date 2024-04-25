import os
import cv2

if not os.path.exists ("./images_argumented") :
    os.mkdir ("./images_argumented")

for i in range (0, 441) :
    img = cv2.imread (f"./images/{i}.jpg")
    img = cv2.pyrMeanShiftFiltering (img, 25, 10)
    cv2.imwrite (f"./images_argumented/{i}.jpg", img)
    print (f"img {i} succeed !")

