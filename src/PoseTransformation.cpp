#include "PoseTransformation.h"

Pose PoseTransformation::CalculateTransformationMatrix(const cv::Mat& rotationVector, const cv::Mat& translationVector)
{
    cv::Mat rotationMatrix;
    cv::Rodrigues(rotationVector, rotationMatrix);

    cv::Mat transformationMatrix;
    cv::hconcat(rotationMatrix, cv::Mat(translationVector.t()), transformationMatrix);

    cv::Mat translationMatrixLastRow = (cv::Mat_<double>(1, 4) << 0, 0, 0, 1);
    cv::vconcat(transformationMatrix, translationMatrixLastRow, transformationMatrix);

    return transformationMatrix;
}
