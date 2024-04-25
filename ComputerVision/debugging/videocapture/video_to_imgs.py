import os
import cv2

cap = cv2.VideoCapture (r"./videos/target2.mp4")

count = 0

if not os.path.exists (r"./imgs2") :
    os.mkdir ("imgs2")

while True :
    _, img = cap.read ()
    cv2.imwrite (f"./imgs/{count}.jpg", img)
    count += 1
    

