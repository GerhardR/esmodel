esmodel
=======

A tool to estimate the homography between to images using template tracking. It uses only function from libcvd.

data exchange
-------------

The output of the program is simple data in space separated columns. The first line is a header describing the
individual columns. Here is a short explanation of the columns:

H1 - H9 :  the 3x3 homography in row major form, mapping pixels from the following frame to the current frame
err^2   :  the total squared error after the optimization
pixels  :  number of valid pixels after the optimization
RMSE    :  RMSE error
delta   :  size of the last update step
iterations  : number of iterations

To read the data into matlab use:

    data = dlmread('data.txt', ' ', 1, 0)
