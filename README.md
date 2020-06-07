# Home Service Robot

Implementation of a House Service Robot to autonomously guide itself around the map to reach two different locations.

This through the utilization of mapping, localization and path planning, interfacing different **official ROS packages**.

### ROS Packages:

- **Gmapping**: to easly perform SLAM and build a map of the environment using the *gmapping_demo.launch* file.

- **Turtlebot_teleop:** to manually control the robot using the keypath commands, with the *keyboard_teleop.launch* file.

- **Turtlebot_gazebo:** to deploy a turtlebot in the gazebo environment linking the world file to it, using the *turtlebot_world.launch* file. 

A version of the *view_navigation.launch* file from **Turtlebot_rviz_launchers**, stored in the folder */my_robot/launch* is used to load a preconfigured rviz workspace.

The localization is performed using Adaptive Monte-Carlo Localization (AMCL), using a version of the *amcl_demo.launch* file from the **Turtlebot_gazebo** package, since the turtlebot has to be rotated 90° in order to have the map in rviz and the gazebo world to match correctly. 

Path planning is performed using the ROS Navigational Stack (navfn/NavfnROS , TrajectoryPlannerROS), which relies on Dijkstra's algorithm, a variant of the Uniform Cost Search algorithm.
