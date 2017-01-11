function [ leftLegCOM, leftKneeNext, leftAnkleNext ] = LeftLeg( leftLegQuaternionData, leftHipPrevious, leftKneePrevious, leftAnklePrevious )
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

qCalibrationforLeftShank = angle2quat(147.3, 91, 0, 'xyz');
qCalibrationforLeftThigh = angle2quat(147.3, 91, 0, 'xyz');

qLeftShank = leftLegQuaternionData(1, :);
qLeftThigh = leftLegQuaternionData(2, :);

vectorLeftShank = leftAnklePrevious - leftKneePrevious;
vectorLeftThigh = leftKneePrevious - leftHipPrevious;

vectorLeftShank_afterRotate = quatrotate(quatmultiply(qLeftShank, qCalibrationforLeftShank), vectorLeftShank);
vectorLeftThigh_afterRotate = quatrotate(quatmultiply(qLeftThigh, qCalibrationforLeftThigh), vectorLeftThigh);

leftKneeNext = leftHipPrevious + vectorLeftThigh_afterRotate;
leftAnkleNext = leftKneeNext + vectorLeftShank_afterRotate;

COMLeftThigh = 0.433 * leftHipPrevious + 0.567 * leftKneeNext;
COMLeftShank = 0.433 * leftKneeNext + 0.567 * leftAnkleNext;

leftLegCOM = COMLeftThigh*0.1 + COMLeftShank*0.0465;


end

