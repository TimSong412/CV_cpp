import cv2
import numpy as np
import os


objpts = []
for i in range(144):
    objpts.append(np.array([i/12, i%12, 0], dtype=np.float32))
objpts = np.array(objpts)

Msum = np.zeros((3, 3), dtype=np.float32)
powersum = 0.0
distsum = np.zeros((1, 5), dtype=np.float32)
for root, dirs, files in os.walk("./HW4_images/calibration"):
    for file in files:
        img = cv2.imread(os.path.join(root, file))
        retval, corners = cv2.findChessboardCornersSB(img, (12, 12))
        cornerimg = cv2.drawChessboardCorners(img, (12, 12), corners, retval)
        # cv2.imshow("corner", cornerimg)
        intM = cv2.calibrateCamera(objectPoints=[objpts], imagePoints=[corners], imageSize=img.shape[0:2], cameraMatrix=None, distCoeffs=None)
        undist = cv2.undistort(img, intM[1], intM[2])
        # print(intM[1:3])  
        cv2.imshow("ori", cv2.resize(img, (800, 600)))
        cv2.imshow("und", cv2.resize(undist, (800, 600)))
        cv2.waitKey(0)     
        Msum += intM[1]/intM[0]
        powersum += 1/intM[0]
        distsum += intM[2]/intM[0]

IM = Msum / powersum
dist = distsum / powersum
print(IM)
print(dist)


for root, dirs, files in os.walk("./HW4_images/birdseye"):
    for file in files: 
        img = cv2.imread(os.path.join(root, file))
        
        undistimg = cv2.undistort(img, IM, np.array([0, 0, 0, 0, 0]))
        retval, corners = cv2.findChessboardCornersSB(undistimg, (12, 12))
        print(corners[0])
        x_bias = corners[0][0][0]*0.9
        y_bias = corners[0][0][1]*0.9
        blk = 2
        objs = np.array([[x_bias, y_bias], [x_bias+11*blk, y_bias+0], [x_bias, y_bias+11*blk], [x_bias+11*blk, y_bias+11*blk]], dtype=np.float32)
        imgpts = np.array([corners[0], corners[11], corners[132], corners[143]])
        cv2.drawChessboardCorners(img, (2, 2), imgpts, True)
        H = cv2.getPerspectiveTransform(imgpts, objs)
        # H[2, 2] = 2
        shape = np.array((img.shape[0]/2, img.shape[1]/2), dtype=int)
        print(H)
        birdimg = cv2.warpPerspective(img, H, img.shape[0:2])
        cv2.imshow("undist", cv2.resize(undistimg, shape))
        cv2.imshow("ori", cv2.resize(img, shape))   
        cv2.imshow("bird", cv2.resize(birdimg, shape))
        cv2.waitKey(0)
