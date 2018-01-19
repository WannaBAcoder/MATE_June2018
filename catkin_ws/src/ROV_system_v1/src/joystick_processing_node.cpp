/*
 * Author: Vinnie Marco, Tamara Spivey, and the Most Honorable Christian Upschulte: President of S&T URT
 * Email: vgmcn3@mst,edu
 * Date: 01-18-2018
 * 
 * This file handles data from the joystick
 */

#include "joystick_processing_node.h"

/*This is our main function
 *Pre: None
 *Post: Necessary publishers and subscribers are created to read controller data
 */
int main(int argc, char **argv)
{
  //necessary ros things
  ros::init(argc, argv,"joystick_processing_node");//set up node named
  ros::NodeHandle n;//create node handle instance
  
  //set up subscriptions
  ros::Subscriber joystic_topic = n.subscribe("joystick_topic", 1000, joystick_callback);//subscribe to joystick values

  //set up publishers
  ros::Publisher joystick_x_pub = n.advertise<std_msgs::Float32>("magnitude_topic", 1000);
  ros::Publisher joystick_y_pub = n.advertise<std_msgs::Float32>("angle_topic", 1000);
  ros::Publisher joystick_rotation_pub = n.advertise<std_msgs::Float32>("joystick_rotation_topic", 1000);
  ros::Publisher trigger_pub = n.advertise<std_msgs::Bool>("trigger_topic", 1000);
  ros::Publisher button_pinky_trigger_pub = n.advertise<std_msgs::Bool>("button_pinky_trigger_topic", 1000);

  ros::Rate loop_wait(30);//this is needed
 
  while(ros::ok()) //ctr-c makes ok() return false, thus ending the program
  {  
   //publish everything once per loop
   joystick_x_pub.publish(magnitude_value);   
   joystick_y_pub.publish(angle_value);
   joystick_rotation_pub.publish(axis_stick_rotation_value);
 
   trigger_pub.publish(button_trigger_state);
   button_pinky_trigger_pub.publish(button_pinky_trigger_state);

   ros::spinOnce();
   loop_wait.sleep();//wait some
  }
  return 0;
}


/* joystick_callback handles data recieved from the joystick topic
 * Pre: Joystick topic has to be initalized
 * Post: Any variables are updated to their current values for each itteration
 */
void joystick_callback(const sensor_msgs::Joy &joy)
{
  angle_value.data = atan2(joy.axes[axis_stick_y],  joy.axes[axis_stick_x]*-1);
  magnitude_value.data = sqrt(pow(joy.axes[axis_stick_y],2) + pow(joy.axes[axis_stick_x],2));
  axis_stick_rotation_value.data = joy.axes[axis_stick_rotation];

  angle_value.data *= 180/M_PI; //built in value for Pi

  if(angle_value.data < 0) //conversion to positive degree value
  {
    angle_value.data += 360;
  }

  if(magnitude_value.data > 1.0) //magnitude is a scale of our speed, from [0,1]
  {
    magnitude_value.data = 1.0; //mapped to one to match our scale
  }
  if(magnitude_value.data < 0.0)
  {
    magnitude_value.data = 0.0; //mapped to zero to match our scale 
  }

  button_trigger_state.data = joy.buttons[button_trigger]; //Gets value from button trigger
  button_pinky_trigger_state.data = joy.buttons[button_pinky_trigger];


/*
FIX ME PLEASE look like ^
 //buttons are stored in joy.buttons[]
  //axes are stored in joy.axis[]


  if(joy.buttons[button_a] == 1)
  { 
    ROS_INFO("Button A pressed");
    button_a_state.data = 1;
  }
  else
    button_a_state.data = 0;


  if(joy.buttons[button_b] == 1)
  {
    ROS_INFO("Button B pressed");
    button_b_state.data = 1;
  }
  else
    button_b_state.data = 0;

  if(joy.buttons[button_c] == 1)
  {
    ROS_INFO("Button C pressed");
    button_c_state.data = 1;
  }
  else
    button_c_state.data = 0;

  if(joy.buttons[button_d] == 1)
  {
    ROS_INFO("Button D pressed");
    button_d_state.data = 1;
  }
  else
    button_d_state.data = 0;


  if(joy.buttons[button_h1_up] == 1)
  {
    ROS_INFO("Button h1 up pressed");
    button_h1_up_state.data = 1;
  }
  else
    button_h1_up_state.data = 0;

  if(joy.buttons[button_h1_right] == 1)
  {
    ROS_INFO("Button h1 right pressed");
    button_h1_right_state.data = 1;
  }
  else
    button_h1_right_state.data = 0;

  if(joy.buttons[button_h1_down] == 1)
  {
    ROS_INFO("Button h1 down pressed");
    button_h1_down_state.data = 1;
  }
  else
    button_h1_down_state.data = 0;

  if(joy.buttons[button_h1_left] == 1)
  {
    ROS_INFO("Button h1 left pressed");
    button_h1_left_state.data = 1;
  }
  else
    button_h1_left_state.data = 0;


  if(joy.buttons[button_h2_up] == 1)
  {
    ROS_INFO("Button h2 up pressed");
    button_h2_up_state.data = 1;
  }
  else
    button_h2_up_state.data = 0;

  if(joy.buttons[button_h2_right] == 1)
  {
    ROS_INFO("Button h2 right pressed");
    button_h2_right_state.data = 1;
  }
  else
    button_h2_right_state.data = 0;

  if(joy.buttons[button_h2_down] == 1)
  {
    ROS_INFO("Button h2 down pressed");
    button_h2_down_state.data = 1;
  }
  else
    button_h2_down_state.data = 0;

  if(joy.buttons[button_h2_left] == 1)
  {
    ROS_INFO("Button h2 left pressed");
    button_h2_left_state.data = 1;
  }
  else
    button_h2_left_state.data = 0;

  axis_pov_x_value.data = joy.axes[axis_pov_x];
  axis_pov_y_value.data = joy.axes[axis_pov_y];
*/
}


