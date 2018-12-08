/**
 * This file is part of CubeSLAM.
 *
 * Copyright (C) 2018, Carnegie Mellon University
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LANDMARK_H
#define LANDMARK_H

#include <opencv2/opencv.hpp>

namespace ORB_SLAM2 {

struct LandmarkDimension {
    float height{};   // Corresponding to vanishing point 3.
    float edge13{};   // Corresponding to vanishing point 1.
    float edge12{};   // Corresponding to vanishing point 2.

    LandmarkDimension() { }
    LandmarkDimension(float height_, float edge13_, float edge12_)
            :height(height_), edge13(edge13_), edge12(edge12_) { }
};

class Landmark {
public:
    void SetDimension(const LandmarkDimension& dimension);
    LandmarkDimension GetDimension();
    void SetPose(const cv::Mat& Tlw_);
    cv::Mat GetPose();
    cv::Mat GetPoseInverse();
    cv::Mat GetLandmarkCenter();
    cv::Mat GetRotation();
    cv::Mat GetTranslation();
    cv::Point2f GetProjectedCenter(const cv::Mat& Tcw);
    std::unordered_map<int, cv::Point2f> bboxCenter;
public:
    int classIdx;
    int landmarkID;
private:
    // SE3 Pose.
    cv::Mat Tlw;
    cv::Mat Twl;
    // Landmark center.
    cv::Mat Lw;
    // Landmark dimension.
    LandmarkDimension mDimension;

    std::mutex mMutexPose;
};

}

#endif //LANDMARK_H
