import cv2
import os

def main () :
    """the main function to shoot the dataset"""
    path:str = r"./imgs/"
    if not os.path.exists (path) :
        os.mkdir ("./imgs")
    key:int = 0
    count:int = 191
    time:int = 0
    cap = cv2.VideoCapture (2)

    while True :
        _, img = cap.read ()
        cv2.imshow ("Cam", img)
        key = cv2.waitKey (20)
        time += 20

        if key == 27 :
            break

        if time == 100 :
            cv2.imwrite (f"{path}{count}.jpg", img)
            count += 1
            time = 0

if __name__ == "__main__" :
    input ()
    main ()
