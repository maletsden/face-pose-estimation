# Head Pose Estimation

Head Pose Estimation (HPE) is the task of estimating the pose that consists of 6 degrees-of-freedom (DOF) from imagesor video. Head pose estimation is often used in virtual and augmented reality solution, marker-less motion capture for3D facial alignment, face orientation estimation, and 3D face modeling from the single camera

# Method

This project will review the method for head pose estimation described in the WithTeeth article and analyze advantagesand disadvantages of the approach proposed bu the authors

## Face Feature Extraction

Face Feature Extraction is one of the main problem that need to be solved for the head pose estimation. One of thepossible approaches for extracting face features from the input image is to use Haar Cascade Classifier. Haar feature-based cascade classifiers is an object detection method for finding features in the image by applying Haar-features tothe analyzing image, but previously grouping Haar-features in the cascade to reduce expensive computational costs.The main disadvantages of this method is that it is working with limited scene conditions (head should be directedtowards the camera with only limited rotation radius) with still high computation cost that is not suitable for lesspowerful devices.The results of applying this method to the input image is a set of 2D image points (UV coordinates) that corresponds tomajor face features.

## Solving Perspective-n-Point Problem

Perspective-n-Point Problem is the problem of estimating pose of some 3D object of interest.  The solution to thisproblems is the algorithm that estimates the transformationβ∈IR6from 3D world object (set of world pointsai∈IR3,in the terms of this report - the 3D canonical face model) to 2D image landmarks (set of image pointsbi∈IR2, in theterms of this report - 2D face features extracted on the previous stage).
