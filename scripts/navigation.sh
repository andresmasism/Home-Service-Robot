#!/bin/sh

export TURTLEBOT_GAZEBO_MAP_FILE=/home/workspace/catkin_ws/src/map/map.yaml


xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find my_robot)/worlds/andresm-2.world" &

sleep 10

xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch" & 

sleep 10

xterm  -e  " roslaunch  my_robot view_navigation.launch" &

