function [ hipCenter, shoulderCenterNext, trunkCOM ] = Trunk( leftHip, rightHip, shoulderCenterPrevious, trunkQuaternionData )
%UNTITLED4 Summary of this function goes here
%   Detailed explanation goes here

qCalibrationforTrunk = angle2quat(147.3, 91, 0, 'xyz');

hipCenter = (leftHip + rightHip)/2;

vectorTrunk = shoulderCenterPrevious - hipCenter;

vectorTrunk_afterRotate = quatrotate(quatmultiply(trunkQuaternionData, qCalibrationforTrunk), vectorTrunk);

shoulderCenterNext = hipCenter + vectorTrunk_afterRotate;

trunkCOM = 0.678* (0.626 * hipCenter + 0.374 * shoulderCenterNext);

end

