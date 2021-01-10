#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers_cp");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  uint32_t shape = visualization_msgs::Marker::CUBE;

  
  visualization_msgs::Marker marker;
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();

  marker.ns = "add_markers_cp";
  marker.id = 0;

  marker.type = shape;

  marker.action = visualization_msgs::Marker::ADD;

  marker.pose.position.x = 2.0;
  marker.pose.position.y = 5.0;

  marker.scale.x = 0.25;
  marker.scale.y = 0.25;
  marker.scale.z = 0.25;

  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 1.0f;
  marker.color.a = 1.0;

  marker.lifetime = ros::Duration();

  while (marker_pub.getNumSubscribers() < 1)
  {
    if (!ros::ok())
    {
      return 0;
    }
    ROS_WARN_ONCE("Please create a subscriber to the marker");
    sleep(1);
  }
  
  ROS_INFO("Adding marker...");
  marker_pub.publish(marker);
  marker.action = visualization_msgs::Marker::ADD;
  ros::Duration(5.0).sleep();
  
  ROS_INFO("Removing marker...");
  marker.action = visualization_msgs::Marker::DELETE;
  marker_pub.publish(marker);
  ros::Duration(5.0).sleep();
  
  ROS_INFO("Adding second marker...");
  marker.action = visualization_msgs::Marker::ADD;
  marker.pose.position.x = 2.0;
  marker.pose.position.y = -5.0; 
  marker_pub.publish(marker);
  ros::Duration(5.0).sleep();
  
  ROS_INFO("Done.");
  return 0;
  r.sleep();
  
}