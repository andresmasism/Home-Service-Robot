#!/bin/sh

xterm  -e  " roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find my_robot)/worlds/andresm-2.world" &

sleep 5

xterm  -e  " roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find my_robot)/maps/map.yaml" &  

sleep 10

xterm  -e " roslaunch  my_robot view_navigation.launch" &

sleep 30

xterm  -e " rosrun add_markers add_markers" & 

sleep 5

