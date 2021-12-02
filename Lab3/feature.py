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
dstpts = np.array([meanpos[0:2], meanpos[2:4], [46, 0]], dtype=np.float32)
eigs = np.load(os.path.join(FILEDIR, "topeigs.npy"))
newimgs = []
projs = []
for i in range(len(rawimgs)):
    srcpts = np.array([locs[i][0:2], locs[i][2:4], [46, 0]], dtype=np.float32)
    trans = cv2.getAffineTransform(srcpts, dstpts)    
    transimg = cv2.warpAffine(rawimgs[i], trans, (92, 112))
    cropimg = transimg[20:100, 15:75].reshape(-1)
    newimgs.append(cropimg)
    projs.append(eigs.dot(cropimg)/np.linalg.norm(cropimg))


testimg = cv2.imread(os.path.join(FILEDIR, "test1.png"), cv2.IMREAD_GRAYSCALE)

testtxt = open(os.path.join(FILEDIR, "test1.txt"), 'r')
rawloc = testtxt.read()
loc = np.array(list(map(int, rawloc.split())))
testtxt.close()
srcpts = np.array([loc[0:2], loc[2:4], [46, 0]], dtype=np.float32)
trans = cv2.getAffineTransform(srcpts, dstpts)    
transimg = cv2.warpAffine(testimg, trans, (92, 112))
imgvec = transimg[20:100, 15:75].reshape(-1)

proj = eigs.dot(imgvec)/np.linalg.norm(imgvec)

overlay = np.zeros(imgvec.shape)
for i in range(len(proj)):
    overlay += proj[i] * eigs[i]

overlay = overlay*255/np.max(overlay)
finalimg = np.uint8(overlay).reshape(80, 60)
cv2.imshow("final", finalimg)
cv2.waitKey(0)

maxangle = 0
idx = -1
for i in range(len(projs)):
    cos = proj.dot(projs[i])
    if cos > maxangle:
        maxangle = cos
        idx = i
print(idx)
print("angle= ", maxangle)
cv2.imshow("target", newimgs[idx].reshape(80, 60))
cv2.waitKey(0)