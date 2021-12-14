#include <chrono>
#include <memory>

#include "CameraCalibration.h"
#include "DrawFrame.h"
#include "Face.h"
#include "FaceTracker.h"
#include "IdentityTracker.h"
#include "Types.h"

int main(int argc, char** argv)
{
  cv::VideoCapture cam(0, cv::CAP_V4L2);

  cv::Mat frame;
  cam.read(frame);
  const auto width = frame.cols;
  const auto height = frame.rows;

  CameraCalibration cameraCalibration;
  if (argc == 1)
  {
    // Generate fake camera matrix.
    cameraCalibration = { width, height };
  }
  else
  {
    cv::Mat cameraMatrix, distortionCoefficients;
    const auto calibrationFilePath = "../calibration/" + std::string(argv[1]);
    cv::FileStorage fs(calibrationFilePath, cv::FileStorage::READ);
    fs["camera_matrix"] >> cameraMatrix;
    fs["distortion_coefficients"] >> distortionCoefficients;
    fs.release();
    cameraCalibration = { width, height, std::move(cameraMatrix), std::move(distortionCoefficients) };
  }

  // Initialize tracker blocks.
  FaceTracker<FaceTrackerTypes::OpenCv> faceTracker(cameraCalibration, "./resources");

  while (cam.read(frame))
  {
    const auto start = std::chrono::high_resolution_clock::now();

    const auto face = faceTracker.DetectFace(frame);

    const auto stop = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

    std::vector<Face> faces{};

    if (face)
    {
      faces.push_back(*face);
    }

    auto visualizedFrame = DrawFrame::DrawFaceBoundingBox(frame, faces);
    visualizedFrame = DrawFrame::DrawEachFaceLandmarks(visualizedFrame, faces);
    visualizedFrame = DrawFrame::DrawPose(visualizedFrame, faces, cameraCalibration);
    visualizedFrame = DrawFrame::DrawFrameRate(visualizedFrame, duration);
    cv::imshow("Face Tracking Demo", visualizedFrame);

    constexpr int escapeKeyCode = 27;
    if (cv::waitKey(1) == escapeKeyCode)
    {
      break;
    }
  }
  return 0;
}