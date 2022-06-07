import os
from cv2 import WINDOW_FREERATIO, WINDOW_NORMAL
import cv2 as cv
import numpy as np
cv.namedWindow('video',WINDOW_NORMAL)
cv.resizeWindow('video', 100,100)
execution_path = os.getcwd()
camera = cv.VideoCapture(0)
lower_blue = np.array([100,100,90])
upper_blue = np.array([140,255,255])

while True:
    ret, frame = camera.read()
    img = cv.cvtColor(frame,cv.COLOR_BGR2HSV)
    bluemask = cv.inRange(img,lower_blue,upper_blue)
    #blueImg = cv.bitwise_and(frame,frame,mask = bluemask)
    
    ret, thresh, =cv.threshold(bluemask,0,255,cv.THRESH_BINARY)
    contours, hierarchy = cv.findContours(thresh,cv.RETR_TREE,cv.CHAIN_APPROX_SIMPLE)
    
    if len(contours) != 0:
        for cnr in range(len(contours)):
                area = cv.contourArea(contours[cnr])
                if area > 500:
                    
                    cnt = contours[cnr]
                    moments = cv.moments(cnt)
                    cx = int(moments['m10']/moments['m00'])
                    print("X cord: " ,cx,)
                    color = (0,0,255)
                    
                    cv.circle(frame,(cx,250),6,color,-1)
                    cv.drawContours(frame,contours,cnr,color,4)

    cv.imshow('video',frame)
    a = cv.waitKey(50)

    if cv.waitKey(1) & 0xFF == ord('q'):
        break

camera.release()
cv.destroyAllWindows()