import numpy as np
import cv2

img = cv2.imread ("imgs/2.jpg")


imgShift = cv2.pyrMeanShiftFiltering (img, 10, 25)

imgGray1 = cv2.cvtColor (img, cv2.COLOR_BGR2GRAY)
imgGray2 = cv2.cvtColor (imgShift, cv2.COLOR_BGR2GRAY)

# contours1 = cv2.findContours (imgGray1, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[0]
# contours2 = cv2.findContours (imgGray2, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)[0]

# cv2.drawContours (img, contours1, -1, (255, 0, 0), 2)
# cv2.drawContours (imgShift, contours2, -1, (255, 0, 0), 2)


imgCanny = cv2.Canny (imgShift, 50, 100)

cv2.imshow ("Canny", imgCanny)

kernel = np.ones ((3, 3), np.uint8)

imgDila = cv2.dilate (imgCanny, kernel,iterations=3)
cv2.imshow ("Dila", imgDila)


cv2.imshow ("Img", img)

# cv2.imshow ("Gray1", imgGray1)
cv2.imshow ("Gray2", imgGray2)

cv2.imshow ("SHIFT", imgShift)
if (cv2.waitKey (0) == 27) :
    exit ()