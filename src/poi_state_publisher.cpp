#include <vector>
#include <math.h>
#include "ros/ros.h"
#include "people_msgs/PositionMeasurementArray.h"
#include "people_msgs/PositionMeasurement.h"
#include "geometry_msgs/Quaternion.h"

ros::Publisher pub;

void poiCallback(const people_msgs::PositionMeasurementArray& msg)
{
  // extract people
  std::vector<people_msgs::PositionMeasurement> p = msg.people ;

  // store value in quadrants (front left, front right, back right, back left)
  geometry_msgs::Quaternion poi ;
  double poi_value = 1.0 ;

  // loop through all observed legs
  for (unsigned int i =0; i < p.size(); i++){
    // extract (x,y) locations of legs
    double px = p[i].pos.x ;
    double py = p[i].pos.y ;
    double dist = sqrt(pow(px,2)+pow(py,2)) ;
    double val = poi_value/dist ;
    if (px >= 0 && py >= 0){ // front left
      poi.x += val ;
    }
    else if (px >= 0 && py < 0){ // front right
      poi.y += val ;
    }
    else if (px < 0 && py < 0){ // back right
      poi.z += val ;
    }
    else{ // if (px < 0 && py >= 0){ // back left
      poi.w += val ;
    }
  }

  // if legs were observed, publish new state
  if (p.size() > 0){
    //publish the message
    pub.publish(poi);
  }
  //else keep old poi state (this is dodgy but is within reason if there are always legs about)
  
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "poi_state_publisher") ;

  ros::NodeHandle nHandle1 ;
  ros::NodeHandle nHandle2 ;
  
  pub = nHandle2.advertise<geometry_msgs::Quaternion>("poi_state", 50) ;
  ros::Subscriber sub = nHandle1.subscribe("/leg_tracker_measurements", 10, &poiCallback) ;
  
  ros::spin() ;
  return 0 ;
}


