import os
import cv2
DIR = "C:\\Users\\10347\\OneDrive - zju.edu.cn\\ZJU_online\\CV\\CV_cpp\\Lab4"

cam = cv2.VideoCapture(os.path.join(DIR, "phone_cam.mp4"))
cnt = 0
ret, frame = cam.read()
while ret:
    if cnt % 10 == 0:
        cv2.imwrite(os.path.join(DIR, "images", str(int(cnt/10))+".jpg"), frame)
    cnt += 1
    cv2.imshow("frame", frame)
    cv2.waitKey(25)
    ret, frame = cam.read()
cam.release()
print("cnt= ", cnt)