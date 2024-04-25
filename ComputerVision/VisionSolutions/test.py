import cv2

img = cv2.imread ("~/.config/Backgrounds/background.png")

cv2.imshow ("img", img)

while cv2.waitKey (0) != 27 :
    exit ()
