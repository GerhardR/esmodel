esmodel
=======

A tool to estimate the homography between to images using template tracking. It uses only function from libcvd.

Build instructions
------------------

esmodel only requires a working libcvd and TooN installation. Any input libraries linked into libcvd can be used to read files. Typically, these are libpng, libjpeg and more. To support videos, libcvd should be compiled with ffmpeg support.

Options
-------

esmodel expects a video input string used by libcvd. It then computes the homography matrix from one frame to the next. For N frames it will output N-1 matrices.

minimal example:

    esmodel file://test.mp4

other possible inputs:

    files:[on_end=unset_pending]//*png      all files in the current directory with ending png
    file://../../data/test.mp4              video file in another directory

Some parameters can be set on the command line

    m   [3,4,6,8]   degrees of freedom used for the homography,
                    3 is 2D translation + rotation
                    4 is uniform scale, rotation, 2D translation
                    6 is full affine model
                    8 is full perspective model
    a	[0,1,2]      the type of appearance model
                    0 constant appearance
                    1 constant + offset appearance
                    2 blur model
    d	1e-05       threshold for the minimal update step before stopping
    i	40          maximal number of iterations
    r	0.01        threshold for maximal RSME before stopping
    p   [0,1]       flag to parameterize around the center of the image (1) or not (0)

This works as
    
    esmodel [-option value []] input

Output
------

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
