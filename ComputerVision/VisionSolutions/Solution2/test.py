import cv2

cap = cv2.VideoCapture (2)
print ("Hue : ", cap.get (cv2.CAP_PROP_HUE))
print ("Bright : ", cap.get (cv2.CAP_PROP_BRIGHTNESS))
print ("Saturation : ", cap.get (cv2.CAP_PROP_SATURATION))

while True :
    _, img = cap.read ()
    cv2.imshow ("Cam", img)
    if cv2.waitKey (20) == 27 :
        break
