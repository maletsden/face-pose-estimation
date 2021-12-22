#include "FaceStorage.h"

#include "KalmanFilterWrapper.h"
#include "PoseTransformation.h"

void FaceStorage::UpdateObjectInfo(const Face &face, std::chrono::high_resolution_clock::time_point currentTimestamp) {
  Storage<Face, FaceStorageObjectInfo>::UpdateObjectInfo(face, currentTimestamp);

  auto &faceObjectInfo = GetObjectInfo(face.Id);

  auto &kalmanFilterUpperJaw = faceObjectInfo.UpperJawFilter;
  auto &kalmanFilterLowerJaw = faceObjectInfo.LowerJawFilter;

}

void FaceStorage::SmoothObject(Face &face) {
  using DataType = KalmanFilterWrapper::DataType;

  const auto correctPose = [](PoseTransformation &pose, const cv::Mat &measurment) noexcept -> void {
    pose.RotationVector =
        (cv::Mat_<DataType>(1, 3) << measurment.at<DataType>(0, 0), measurment.at<DataType>(1,
                                                                                            0), measurment.at<DataType>(
            2, 0));
    pose.TranslationVector =
        (cv::Mat_<DataType>(1, 3) << measurment.at<DataType>(3, 0), measurment.at<DataType>(4,
                                                                                            0), measurment.at<DataType>(
            5, 0));
    pose.TransformationMatrix = PoseTransformation::CalculateTransformationMatrix(pose.RotationVector,
                                                                                  pose.TranslationVector);
  };

  auto &faceObjectInfo = GetObjectInfo(face.Id);

  auto &kalmanFilterUpperJaw = faceObjectInfo.UpperJawFilter;
  auto &kalmanFilterLowerJaw = faceObjectInfo.LowerJawFilter;

  using DataType = IFilter::DataType;

  const auto getMeasurement = [](const cv::Mat &rotationVector, const cv::Mat &translationVector) noexcept -> cv::Mat {
    return (
        cv::Mat_<DataType>(6, 1) << rotationVector.at<DataType>(0, 0),
            rotationVector.at<DataType>(0, 1),
            rotationVector.at<DataType>(0, 2),
            translationVector.at<DataType>(0, 0),
            translationVector.at<DataType>(0, 1),
            translationVector.at<DataType>(0, 2));
  };

  const auto upperJawMeasurment = getMeasurement(face.UpperJawPose.RotationVector, face.UpperJawPose.TranslationVector);
  const auto lowerJawMeasurment = getMeasurement(face.LowerJawPose.RotationVector, face.LowerJawPose.TranslationVector);

  kalmanFilterUpperJaw.Filter(upperJawMeasurment, faceObjectInfo.Timestamp);
  kalmanFilterLowerJaw.Filter(lowerJawMeasurment, faceObjectInfo.Timestamp);

  correctPose(face.UpperJawPose, kalmanFilterUpperJaw.GetCorrectedState());
  correctPose(face.LowerJawPose, kalmanFilterLowerJaw.GetCorrectedState());
}
