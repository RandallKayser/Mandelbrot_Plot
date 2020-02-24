import matplotlib as mp
import numpy as np
import matplotlib.pyplot as pp
import scipy as sp
import scipy.optimize as opt
import sys

if(len(sys.argv)!=3):
   print("usage: python vislogv.py, plotdir, runnum\n")

thisfile = "../../dat/" + sys.argv[1] + "/" + sys.argv[2] + ".logv"
def power(x, a, b, c):
   return a*x**b+c

def plotlogv(filestring):
   datafile = open(thisfile, "r")
   logvlist = []

   for i in datafile.readlines():
      logvlist.extend(([float(j) for j in i.strip().split(", ") if j!=""]))
   X = np.linspace(0.01, 1.0, num=len(logvlist))
   logvlist.sort()
   a, b, c = opt.curve_fit(power, X, logvlist, bounds=([-np.inf, -np.inf, -np.inf],[np.inf, 0.01, np.inf]))[0]
   print(a,b,c)
   pp.plot(X, logvlist, 'r-')
   pp.plot(X, power(X, a, b, c), 'b-')
   pp.show()

plotlogv(thisfile)
