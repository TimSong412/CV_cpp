import os
import numpy as np
import cv2
FILEDIR = "C:\\Users\\10347\\OneDrive - zju.edu.cn\\ZJU_online\\CV\\CV_cpp\\Lab3"
DATADIR = "C:\\Users\\10347\\OneDrive - zju.edu.cn\\ZJU_online\\CV\\CV_cpp\\Lab3\\data"


locs = []
rawimgs = []
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
                        rawimgs.append(img)
                        txtfile.close()
                        # print(loc)
                        # cv2.imshow("img", img)
                        # cv2.waitKey(0)
meanpos = np.array(np.around(np.mean(locs, 0)), dtype=int)
# mean:[27.49226804 51.7628866  60.93556701 52.2242268 ]
dstpts = np.array([meanpos[0:2], meanpos[2:4], [56, 0]], dtype=np.float32)
# print(dstpts)
newimgs = []
for i in range(len(rawimgs)):
    srcpts = np.array([locs[i][0:2], locs[i][2:4], [56, 0]], dtype=np.float32)
    trans = cv2.getAffineTransform(srcpts, dstpts)    
    # cv2.imshow("ori", rawimgs[i])
    transimg = cv2.warpAffine(rawimgs[i], trans, (92, 112))
    cropimg = transimg[20:100, 15:75].reshape(-1)
    newimgs.append(cropimg)


eigs = np.load(os.path.join(FILEDIR, "topeigs.npy"))

raw = np.real(eigs[0].reshape(80, 60)) 

alter = raw * 255/np.max(raw)
feature = np.uint8(alter)

proj = eigs.dot(newimgs[0])/np.linalg.norm(newimgs[0])
print(proj)
cv2.imshow("ori", newimgs[0].reshape(80,60))
cv2.imshow("feature", feature)
cv2.waitKey(0)