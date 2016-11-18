import matplotlib.pyplot as plt
import math
import random
import pylab as pl
if __name__ == '__main__':
	x=[]
	y=[]
	for i in range(1,3000):
		# degree=random.randint(0, 360)
		# r=random.randint(0, 50)
		# x.append(r*math.cos(degree))
		# y.append(r*math.sin(degree))
		# x=random.randint(-50, 50)
		# y=random.randint(-50, 50)
		# if x*x+y*y<2500:
		# 	pl.plot(x, y,'r.')
		# x=random.randint(0, 7)
		# y=random.randint(0, 7)
		# y=(x*y)%10
		# pl.plot(x, y,'r.')
		#degree=random.randint(0, 360)
		#r=math.sqrt(random.randint(0, 2500))
		x=random.randint(0,100)
		y=random.randint(0,100)
		if x>y and y<(100-x):
			pl.plot(x, y,'r.')
		
	# use pylab to plot x and y
	plt.axis([0,100,0,100])
	pl.show()# show the plot on the screen