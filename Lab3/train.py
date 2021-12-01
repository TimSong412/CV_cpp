import cv2
import numpy as np
import os
DATADIR = "C:\\Users\\10347\\OneDrive - zju.edu.cn\\ZJU_online\\CV\\CV_cpp\\Lab3\\data"


locs = []
imgs = []
for root, dirs, files in os.walk(os.path.join(DATADIR)):
    for dir in dirs:
        for subroot, subdirs, subfiles in os.walk(os.path.join(root, dir)):
            for subfile in subfiles:
                name = os.path.splitext(subfile)
                if name[1] == ".png":
                    txt = os.path.join(subroot, name[0]+".txt")
                    png = os.path.join(subroot, subfile)
                    if os.path.exists(txt):
                        txtfile = open(txt, 'r')
                        img = cv2.imread(png, cv2.IMREAD_GRAYSCALE)
                        rawloc = txtfile.read()
                        loc = np.array(list(map(int, rawloc.split())))
                        locs.append(loc)
                        imgs.append(img)
                        txtfile.close()
                        # print(loc)
                        # cv2.imshow("img", img)
                        # cv2.waitKey(0)
meanpos = np.array(np.around(np.mean(locs, 0)), dtype=int)
dstpts = np.array([meanpos[0:2], meanpos[2:4], [(meanpos[0]+ meanpos[2])/2, (meanpos[1]+ meanpos[3])/2]], dtype=np.float32)
# print(dstpts)
# for i in range(len(imgs)):
srcpts = np.array([locs[0][0:2], locs[0][2:4], [(locs[0][0]+ locs[0][2])/2, (locs[0][1]+ locs[0][3])/2]], dtype=np.float32)
trans = cv2.getAffineTransform(srcpts, dstpts)
print(trans)
cv2.imshow("ori", imgs[0])
transimg = cv2.warpAffine(imgs[0], trans, (90, 110))
cv2.imshow("trans", transimg)
cv2.waitKey(10)
# mean:[27.49226804 51.7628866  60.93556701 52.2242268 ]
                        
                    
