import PIL
import PIL.Image as im
import numpy as np
import sys

if(len(sys.argv)!=3):
   print("usage: python make_img.py, plotfolder, num,  runnum\n")
   print("usage: python make_img.py, filepaths\n")
def makelinelist(instr):
   result = []
   for j in instr:
      if( j.find("-") != -1 ):
         low, high = [int(i) for i in j.split("-")]
         result.extend([str(i) for i in range(low, high+1)])
      else:
         result.append(j)
   return result

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
   pic = im.fromarray((dataarray).astype('uint8'), mode = "RGB")
   pic.save(output)
   datafile.close()

if(sys.argv[2]=="num"):
   linelist = makelinelist(sys.argv[3:])
   filelist = ["../../dat/" + sys.argv[1] + "/" + i + ".dat" for i in linelist]
   outputlist = ["../../dat/" + sys.argv[1] + "/" + i  + ".png" for i in linelist]

   for i in range(len(filelist)):
      makeimg(filelist[i], outputlist[i])
else:
   filelist = sys.argv[1:]
   outputlist = [i[:-4] + ".png" for i in filelist]
   for i in range(len(filelist)):
      makeimg(filelist[i], outputlist[i])
