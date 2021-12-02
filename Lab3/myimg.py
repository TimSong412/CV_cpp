import os
# import numpy as np
import cv2
FILEDIR = "C:\\Users\\10347\\OneDrive - zju.edu.cn\\ZJU_online\\CV\\CV_cpp\\Lab3"
MYDIR = "/home/tim/文档/CV/CV_cpp/Lab3/data/meraw"

for root, dirs, files in os.walk(os.path.join(MYDIR)):
    for file in files:
        name = os.path.splitext(file)
        img = cv2.imread(os.path.join(root, file), cv2.IMREAD_GRAYSCALE)
        
        cv2.imshow("crop", img)
        cv2.waitKey(0)
        
