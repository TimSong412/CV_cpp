import os
import numpy as np
import cv2
FILEDIR = "C:\\Users\\10347\\OneDrive - zju.edu.cn\\ZJU_online\\CV\\CV_cpp\\Lab3"
DATADIR = "C:\\Users\\10347\\OneDrive - zju.edu.cn\\ZJU_online\\CV\\CV_cpp\\Lab3\\data"


testimg = cv2.imread(os.path.join(FILEDIR, "me.jpg"), cv2.IMREAD_GRAYSCALE)
cropimg = testimg[64:1230, :]
resizeimg = cv2.resize(cropimg, (92, 112))
# resizeimg[51, 25] = 255
# resizeimg[53, 54] = 255
cv2.imshow("test", resizeimg)
cv2.waitKey(0)
cv2.imwrite(os.path.join(DATADIR, "test1.png"), resizeimg)
