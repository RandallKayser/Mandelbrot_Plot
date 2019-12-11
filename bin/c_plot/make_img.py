import PIL
import PIL.Image as im
import numpy as np
import sys

if(len(sys.argv)!=3):
   print("usage: python make_img.py, runnum, plotfolder\n")

filestring = "../../dat/" + sys.argv[2] + "/" + sys.argv[1] + ".dat"

def makeimg(filestring, output):
   datafile = open(filestring, "r")
   myline = datafile.readline()
   
   colormode = myline.strip().split(", ")[0].split(" = ")[1]
   pixh = int(myline.strip().split(", ")[1].split(" = ")[1])
   pixw = int(myline.strip().split(", ")[2].split(" = ")[1])
   
   dataarray = []
   for line in datafile.readlines():
      print(line)
      dataarray.append([1-int(i) for i in line.split(", ")])
   dataarray = np.array(dataarray)
   print(dataarray.shape)
   pic = im.fromarray((dataarray*255).astype('uint8'), mode = "L")
   pic.save(output)
   datafile.close()
output = "../../dat/" + sys.argv[2] + "/" + sys.argv[1] + ".png"
makeimg(filestring, output)
