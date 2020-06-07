#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the pick objects node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  // Set up locations parameters
  ros::NodeHandle locations;
  locations.setParam("/PickupLocation",  false);
  locations.setParam("/DropOffLocation", false);

  // Define the positions the goals for the robot to reach
  double first_goal_x = -3.0;
  double first_goal_y =  9.0;
  double first_goal_w =  1.00;

  double second_goal_x = -8.0;
  double second_goal_y = -4.0;
  double second_goal_w =  1.00;

  // Set up the frame parameters
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp    = ros::Time::now();

  // Define a position and orientation for the robot to reach first
  goal.target_pose.pose.position.x    = first_goal_x;
  goal.target_pose.pose.position.y    = first_goal_y;
  goal.target_pose.pose.orientation.w = first_goal_w;

   // Send the goal position and orientation for the robot to reach first
  ROS_INFO("Sending first goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the robot get to the pickup zone");
  else
    ROS_INFO("The robot failed to get to the pickup zone");

  // Create a flag to indicate the robot reached the pickup position
  locations.setParam("/PickupLocation", true);

  // Pause 5 seconds after reaching the pickup zone
  sleep(5);

  // Define a position and orientation for the robot to reach second
  goal.target_pose.pose.position.x    = second_goal_x;
  goal.target_pose.pose.position.y    = second_goal_y;
  goal.target_pose.pose.orientation.w = second_goal_w;

   // Send the goal position and orientation for the robot to reach second
  ROS_INFO("Sending second goal");
  ac.sendGoal(goal);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    ROS_INFO("Hooray, the robot reach the goal");
  else
    ROS_INFO("The robot failed to reach the goal");

  // Create a flag to indicate the robot reached the goal position
  locations.setParam("/DropOffLocation", true);

//  sleep(5);

  return 0;
}
