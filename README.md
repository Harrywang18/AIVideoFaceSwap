# AIVideoFaceSwap
### Original Goal
This is about to input a given video and two human faces(A and B), swap all face A in the video to B.

### Preparations
#### Convert a list of images to a video
* Use cv::VideoWriter to convert the images to a video
* The file names of the images are based on the ascending-sequence: 1.png 2.png ... 500.png 
* By using glob to acquire the filename list, the filenames are sorted by the alphabetical order.
* Re-sort the filenames by the number ascending order
* Generate the results to test.avi
