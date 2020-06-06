#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    // Set up parameters
    ros::NodeHandle locations("/pick_objects");
    bool ready = false;
    bool inZone = false;
    locations.getParam("/PickupLocation", ready);

    // Set our initial shape type to be a Set upcube
    uint32_t shape = visualization_msgs::Marker::CUBE;

    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "/map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "add_markers";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;
    ROS_INFO("Marker waiting in the PickUp zone...");

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = -3.00;
    marker.pose.position.y =  9.00;
    marker.pose.position.z =  0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.2;
    marker.scale.y = 0.2;
    marker.scale.z = 0.2;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    // Duration of the marker
    marker.lifetime = ros::Duration();

    // Publish the marker
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
      sleep(1);
    }
    marker_pub.publish(marker);

    // Wait until robot reach the pickup zone
    while (!inZone) {
        locations.getParam("/PickupLocation", ready);
        inZone = ready;
        r.sleep();
    }

    // Wait 5 seconds to simulate a pickup
    sleep(5);
    ROS_INFO("Marker has been picked up...");

    //Hide the marker
    marker.action = visualization_msgs::Marker::DELETE;    
    marker_pub.publish(marker);
    inZone = false;
    ready = false;

    // Wait until robot reach the dropoff zone
    while (!inZone) {
        locations.getParam("/DropOffLocation", ready);
        inZone = ready;
        r.sleep();
    }

    //Publish marker once the robot reach the second zone
    marker.action = visualization_msgs::Marker::ADD;
    ROS_INFO("Marker is in the Drop zone...");
    marker.pose.position.x = -8.00;
    marker.pose.position.y = -4.00;    
    marker_pub.publish(marker);
    sleep(5);

    return 0;
  
}
