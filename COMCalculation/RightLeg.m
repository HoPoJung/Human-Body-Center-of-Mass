function [ rightLegCOM, rightKneeNext, rightAnkleNext ] = RightLeg(rightLegQuaternionData, rightHipPrevious, rightKneePrevious, rightAnklePrevious)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here

qCalibrationforRightShank = angle2quat(147.3, 91, 0, 'xyz');
qCalibrationforRightThigh = angle2quat(147.3, 91, 0, 'xyz');

qRightShank = rightLegQuaternionData(1, :);
qRightThigh = rightLegQuaternionData(2, :);

vectorRightShank = rightAnklePrevious - rightKneePrevious;
vectorRightThigh = rightKneePrevious - rightHipPrevious;

vectorRightShank_afterRotate = quatrotate(quatmultiply(qRightShank, qCalibrationforRightShank), vectorRightShank);
vectorRightThigh_afterRotate = quatrotate(quatmultiply(qRightThigh, qCalibrationforRightThigh), vectorRightThigh);

rightKneeNext = rightHipPrevious + vectorRightThigh_afterRotate;
rightAnkleNext = rightKneeNext + vectorRightShank_afterRotate;

COMRightThigh = 0.433 * rightHipPrevious + 0.567 * rightKneeNext;
COMRightShank = 0.433 * rightKneeNext + 0.567 * rightAnkleNext;

rightLegCOM = COMRightThigh*0.1 + COMRightShank*0.0465;

end

