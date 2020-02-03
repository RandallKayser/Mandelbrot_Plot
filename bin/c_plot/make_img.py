import PIL
import PIL.Image as im
import numpy as np
import sys

if(len(sys.argv)!=3):
   print("usage: python make_img.py, plotfolder, runnum\n")

filestring = "../../dat/" + sys.argv[1] + "/" + sys.argv[2] + ".dat"
def makelinelist(instr):
   low, high = [int(i) for i in instr.split("-")]
   re
def strtotriple(s):
   return [int(i) for i in s[1:-1].split(" ")]

def makeimg(filestring, output):
   datafile = open(filestring, "r")
   myline = datafile.readline()
   
   colormode = myline.strip().split(", ")[0].split(" = ")[1]
   pixh = int(myline.strip().split(", ")[1].split(" = ")[1])
   pixw = int(myline.strip().split(", ")[2].split(" = ")[1])
   
   dataarray = []
   for line in datafile.readlines():
      dataarray.append([strtotriple(i) for i in line.strip().split(", ")])
   dataarray = np.array(dataarray)
   print(dataarray.shape)
   pic = im.fromarray((dataarray).astype('uint8'), mode = "RGB")
   pic.save(output)
   datafile.close()
output = "../../dat/" + sys.argv[1] + "/" + sys.argv[2] + ".png"
makeimg(filestring, output)
