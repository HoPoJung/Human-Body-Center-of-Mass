
%% Initial joint coordinate

rightAnkle = [0, 0, 9.4];   % right ankle
rightKnee = [0, 0, 54.4];  % right knee
rightHip = [0, 0, 100.4]; % right hip
leftHip = [14, 0, 100.4];   % left hip
leftKnee = [14, 0, 54.4];    % left knee
leftAnkle = [14, 0, 9.4];     % left ankle
rightShoulder = [-13, 0, 149];   % right shoulder
leftShoulder = [27, 0, 149.2];   %left shoulder
shoulderCenter = (rightShoulder + leftShoulder)/2;
%% quaternion data
quaternion_filename = uigetfile({'*.csv'}, 'COM quaternion data');
quaternion = load(quaternion_filename);
q_leftThigh = cat(2, quaternion(:, 1), quaternion(:, 4), quaternion(:, 2), quaternion(:, 3));
q_leftShank = cat(2, quaternion(:, 9), quaternion(:, 12), quaternion(:, 10), quaternion(:, 11));
q_rightThigh = cat(2, quaternion(:, 5), quaternion(:, 8), -quaternion(:, 6), quaternion(:, 7));
q_rightShank = cat(2, quaternion(:, 13), quaternion(:, 16), -quaternion(:, 14), quaternion(:, 15));

q_leftLeg = cat(3, q_leftThigh, q_leftShank);
q_rightLeg = cat(3, q_rightThigh, q_rightShank);
q_trunk = cat(2, quaternion(:, 17), quaternion(:, 18), quaternion(:, 20), quaternion(:, 19));

%% calculate center of mass
for i = 1: size(quaternion, 1)
    [rightLegCOM, rightKnee_next, rightAnkle_next] = RightLeg(cat(1, q_rightLeg(i, :, 1), q_rightLeg(i, :, 1)), rightHip, rightKnee, rightAnkle);
    [leftLegCOM, leftKnee_next, leftAnkle_next] = LeftLeg(cat(1, q_leftLeg(i, :, 1), q_leftLeg(i, :, 2)), leftHip, leftKnee, leftAnkle);
    [hipCenter, shoulder_next, trunkCOM] = Trunk(leftHip, rightHip, shoulderCenter, q_trunk(i, :));
    
    line_rightShank = [rightKnee_next; rightAnkle_next];
    line_rightThigh = [rightHip; rightKnee_next];
    line_leftShank = [leftKnee_next; leftAnkle_next];
    line_leftThigh = [leftHip; leftKnee_next];
    line_hip = [leftHip; rightHip];
    line_trunk = [hipCenter; shoulder_next];
    
    % all the points of the human joint
    joints = [rightAnkle_next; rightKnee_next; rightHip; leftHip; leftKnee_next; leftAnkle_next; (leftHip + rightHip)/2; shoulder_next];
    
    % draw skeletal limb and joint
    plot3(line_rightShank(:, 1), line_rightShank(:, 2), line_rightShank(:, 3));
    hold on;
    plot3(line_rightThigh(:, 1), line_rightThigh(:, 2), line_rightThigh(:, 3));
    hold on;
    plot3(line_hip(:, 1), line_hip(:, 2), line_hip(:, 3));
    hold on; 
    plot3(line_leftThigh(:, 1), line_leftThigh(:, 2), line_leftThigh(:, 3));
    hold on;
    plot3(line_leftShank(:, 1), line_leftShank(:, 2), line_leftShank(:, 3));
    hold on;
    plot3(line_trunk(:, 1), line_trunk(:, 2), line_trunk(:, 3));
    hold on;
    plot3(joints(:, 1), joints(:, 2), joints(:, 3), 'ro');
    hold on;
    
    % calculate body center of mass
    COM = 0.678*trunkCOM + 0.1465* rightLegCOM + 0.1465* leftLegCOM; 
    
    % draw body center of mass 
    plot3(COM(:, 1), COM(:, 2), COM(:, 3), 'b*');
    hold off;
    
    % refresh human joint position
    leftAnkle = leftAnkle_next;
    leftKnee = leftKnee_next;
    rightAnkle = leftAnkle_next;
    rightKnee = rightKnee_next;
    shoulderCenter = shoulder_next;
    
    % render parameters
    axis([-100 100 -100 120 -90 160]);
    view(20, 30);
    pause(1);
    
end

