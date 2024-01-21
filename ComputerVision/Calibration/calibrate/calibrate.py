import cv2
import os
import numpy as np

true_x = 0.14;
true_y = 0.066;
u = 0.000003
focus = 0.0028
path = r"./imgs/"
pic_list = os.listdir (path)

def getTarget (img) :
    pic = cv2.cvtColor (img, cv2.COLOR_BGR2GRAY)
    # pic = cv2.GaussianBlur (pic, (3, 3), 2, 2)
    pic = cv2.Canny (pic, 50, 150)
    contours, _ = cv2.findContours (pic, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    # print (contours)
    conpoly = 0
    for contour in contours :
        if cv2.contourArea (contour) > 2000 :
            # img = cv2.drawContours (img, [contour], 0, (0, 255, 0), 2)
            # boundingrect = cv2.boundingRect (contour)
            # img = cv2.rectangle (img, boundingrect, (255, 255, 0), 2)
            conpoly = cv2.approxPolyDP (contour, 7, True)
            # print (len (conpoly))
            img = cv2.drawContours (img, [conpoly], 0, (255, 255, 0), 1)
    
    # cv2.imshow ("Img", img)
    
    return conpoly

def orderp (points) :
    subp = []
    sump = []
    orderpoints = []
    for [[x, y]] in points :
        sump.append (x + y)
        subp.append (x - y)
        
    orderpoints.append (points[np.argmin (sump)])
    orderpoints.append (points[np.argmax (subp)])
    orderpoints.append (points[np.argmin (subp)])
    orderpoints.append (points[np.argmax (sump)])
    
    return orderpoints

def ppD (pt1, pt2) :
    return np.sqrt ((pt1[0][0] - pt2[0][0]) ** 2 + (pt1[0][1] - pt2[0][1]) ** 2)

def warpTarget (img, points, true_x, true_y) :
    
    ratio = true_y / true_x

    
    mw = max (ppD (points[0], points[1]), ppD (points[2], points[3]))
    mh = max (ppD (points[0], points[2]), ppD (points[1], points[3]))
    
    standard = max (mw, mh)
    other = standard * ratio
    
    src = np.float32 ([points[1][0], points[3][0], points[0][0], points[2][0]])
    dst = np.float32 ([[0, 0], [standard, 0], [0, other], [standard, other]])
    matrix = cv2.getPerspectiveTransform (src, dst)
    imgWarp = cv2.warpPerspective (img, matrix, (int (standard), int (other)))
    return imgWarp

d = []

for pic in pic_list :
    D = int (pic.split ('.')[0])
    # print (distance[0])
    img = cv2.imread (path + pic)
    conpoly = getTarget (img)
    # print (conpoly)
    points = orderp (conpoly)
    # print (points)
    # d = ppD (points[0], points[1])
    # print (d)
    imgWarp = warpTarget (img, points, true_x, true_y)
    # print (ppD (points[0], points[2]))
    # print (imgWarp.shape[1])
    # cv2.imshow ("ImgWarp", imgWarp)
    
    d1 = D / 100 * imgWarp.shape[1] * u / true_x
    d2 = D / 100 * imgWarp.shape[0] * u / true_y
    print (d1, " ", d2)
    d.append ((d1 + d2) / 2)
    
    # if cv2.waitKey (0) == 27 :
    #     continue

d_avg = np.average (d)
    
with open ("../param.csv", "w") as f :
    f.write (f"u = {u}\n")
    f.write (f"focus = {focus}\n")   
    f.write (f"d_list = {d}\n")
    f.write (f"d_average = {d_avg}, {round (d_avg, 7)}\n")
    f.write (f"w * h = 1280 * 720\n")     

print ("Calibration Succeed !")