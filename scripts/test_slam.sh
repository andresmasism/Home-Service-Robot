#!/bin/sh

xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find my_robot)/worlds/andresm-2.world" &

sleep 10

xterm  -e " roslaunch my_robot view_navigation.launch" &

sleep 10

xterm  -e " rosrun gmapping slam_gmapping scan:=scan " & 

sleep 5

xterm  -e " roslaunch turtlebot_teleop keyboard_teleop.launch" &

sleep 5
