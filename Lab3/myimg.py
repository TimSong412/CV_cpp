import os
import numpy as np
import cv2
FILEDIR = "C:\\Users\\10347\\OneDrive - zju.edu.cn\\ZJU_online\\CV\\CV_cpp\\Lab3"
MYDIR = "C:\\Users\\10347\\OneDrive - zju.edu.cn\\ZJU_online\\CV\\CV_cpp\\Lab3\\data\\meraw"

for root, dirs, files in os.walk(os.path.join(MYDIR)):
    for file in files:
        name = os.path.splitext(file)
        img = cv2.imread(os.path.join(root, file), cv2.IMREAD_GRAYSCALE)
        cropimg = img[80:1280, 25:925]
        resizeimg = cv2.resize(cropimg, (90, 120))
        cv2.imshow("crop", resizeimg)
        cv2.waitKey(0)
        
