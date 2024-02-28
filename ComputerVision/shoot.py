import cv2
import os

if not os.path.exists ("imgs") :
    os.mkdir ("imgs")

cap = cv2.VideoCapture (2);
i = 177
cap.set (cv2.CAP_PROP_FRAME_HEIGHT, 720)
cap.set (cv2.CAP_PROP_FRAME_WIDTH, 1280)
while True :
    _, img = cap.read ()
    cv2.imshow ("Cam", img);
    key = cv2.waitKey (20);
    if key == 49 :
        cv2.imwrite (f"imgs/{i}.jpg", img)
        i += 1
    elif key == 27 :
        break
