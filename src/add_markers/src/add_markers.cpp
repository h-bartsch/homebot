#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>

ros::Publisher marker_pub;

visualization_msgs::Marker marker;
visualization_msgs::Marker marker2;

float pickup_xy[2] = {2.0, 5.0};
float dropoff_xy[2] = {2.0, -5.0};

bool notPickedUp = true;

void odomCallback(const nav_msgs::Odometry::ConstPtr& pos){
  if(notPickedUp){
    marker_pub.publish(marker);
  }

  if(abs(pickup_xy[0] - pos->pose.pose.position.x) + abs(pickup_xy[1] - pos->pose.pose.position.y) < 1){
    sleep(5);
    
    marker.action = visualization_msgs::Marker::DELETE; //'pick up' marker
    marker_pub.publish(marker);
    
    notPickedUp = false;

  } else if(abs(dropoff_xy[0] - pos->pose.pose.position.x) + abs(dropoff_xy[1] - pos->pose.pose.position.y) < 1){
    sleep(5);
    
    marker2.action = visualization_msgs::Marker::ADD; //'drop off' marker
    marker_pub.publish(marker2);
  }
}


int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
    
  ros::Subscriber marker_sub = n.subscribe("/odom",800,odomCallback);
  
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time::now();

  marker.ns = "add_markers";
  marker.id = 0;
  marker.type = visualization_msgs::Marker::CUBE;

  marker.action = visualization_msgs::Marker::ADD;
  
  marker.scale.x = 0.25;
  marker.scale.y = 0.25;
  marker.scale.z = 0.25;
  
  marker.color.r = 0.0f;
  marker.color.g = 1.0f;
  marker.color.b = 1.0f;
  marker.color.a = 1.0;
  
  marker.lifetime = ros::Duration();

  marker.pose.position.x = pickup_xy[0];
  marker.pose.position.y = pickup_xy[1];

  marker2 = marker;
  marker2.id = 1;
  marker2.pose.position.x = dropoff_xy[0];
  marker2.pose.position.y = dropoff_xy[1];
  
  marker_pub.publish(marker);


  while(ros::ok()){
    ros::spinOnce();
    r.sleep();
  }

}