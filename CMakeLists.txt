cmake_minimum_required(VERSION 3.20.0 FATAL_ERROR)

project(face_pose_estimation)

set(CMAKE_CXX_STANDARD 20)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

include_directories(hdrs)

set(
        SOURCES
        src/CameraCalibration.cpp
        src/DrawFrame.cpp
        src/Face.cpp
        src/FaceSelector.cpp
        src/FaceStorage.cpp
        src/FaceTracker.cpp
        src/FaceTrackerBase.cpp
        src/IdentityTracker.cpp
        src/KalmanFilterWrapper.cpp
        src/Matcher.cpp
        src/OpenCVFaceDetector.cpp
        src/OpenCVFaceLandmarksDetector.cpp
        src/PnPJawPoseDetector.cpp
        src/PnPPoseDetector.cpp
        src/PoseTransformation.cpp
        src/Storage.cpp
        src/CircularBufferedDeque.cpp
        src/LinearFilter.cpp)

add_executable( ${PROJECT_NAME} main.cpp ${SOURCES})

target_link_libraries( ${PROJECT_NAME} ${OpenCV_LIBS} )