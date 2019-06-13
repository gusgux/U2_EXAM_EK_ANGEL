/*
 * File:          U2_EXAM_EK_ANGEL.c
 * Date:
 * Description:
 * Author:
 * Modifications:
 */

/*
 * You may need to add include files like <webots/distance_sensor.h> or
 * <webots/differential_wheels.h>, etc.
 */
 #include <webots/robot.h>
 #include <webots/motor.h>
 #include <webots/keyboard.h>
 #include <webots/distance_sensor.h>
 #include <webots/position_sensor.h>

 #include <stdio.h>
 #include <stdlib.h>
 /*
  * You may want to add macros here.
  */
 #define TIME_STEP 80
 #define VELOCITY -2
 #define VMAX -40
 #define VLOW -1.3333
 #define PI 3.141592
 #define DW .15
 /*
  * This is the main program.
  * The arguments of the main function can be specified by the
  * "controllerArgs" field of the Robot node
  */
 //VARIABLES FOR ALL KEYBOARD
   int KEY,x,y;
   float L_key,R_key,new_velocity=VELOCITY;
   float LW_key,RW_key;


 int main(int argc, char **argv)
 {
   /* necessary to initialize webots stuff */
   wb_robot_init();
   wb_keyboard_enable(TIME_STEP);

   /**WHEEL VARIABLES*/

    double ds_value;
    double encoder1_value;
    double encoder2_value;
   /*
    * You should declare here WbDeviceTag variables for storing
    * robot devices like this:
    *  WbDeviceTag my_sensor = wb_robot_get_device("my_sensor");
    *  WbDeviceTag my_actuator = wb_robot_get_device("my_actuator");
    */
    //motor devices
    WbDeviceTag wheel_right = wb_robot_get_device("motor_right");
    WbDeviceTag wheel_left = wb_robot_get_device("motor_left");
    WbDeviceTag encoder_1 = wb_robot_get_device("encoder1");
    WbDeviceTag encoder_2 = wb_robot_get_device("encoder2");


    wb_motor_set_position(wheel_right,INFINITY);
    wb_motor_set_position(wheel_left,INFINITY);
    //sensor devices
    WbDeviceTag dist_sensor= wb_robot_get_device("distance_sensor");
    wb_distance_sensor_enable(dist_sensor,TIME_STEP);
    wb_position_sensor_enable(encoder_1,TIME_STEP);
    wb_position_sensor_enable(encoder_2,TIME_STEP);



   /* main loop
    * Perform simulation steps of TIME_STEP milliseconds
    * and leave the loop when the simulation is over
    */
   while (wb_robot_step(TIME_STEP) != -1) {

     /*
      * Read the sensors :
      * Ente
      r here functions to read sensor data, like:
      *  double val = wb_distance_sensor_get_value(my_sensor);
      */


      ds_value=wb_distance_sensor_get_value(dist_sensor);
      encoder1_value=wb_position_sensor_get_value(encoder_1);

      encoder2_value=wb_position_sensor_get_value(encoder_2);
     // printf("Distance sensor:%lf\n",ds_value);
      encoder1_value=(encoder2_value/(2*PI))*0.15*PI;
      encoder2_value=(encoder2_value/(2*PI))*0.15*PI;

      //rintf("lineal velocity for wheel right:%lf \n",encoder2_value);
      //printf("lineal velocity for wheel left:%lf\n",encoder1_value);



     /* Process sensor data here */

     /*
      * Enter here functions to send actuator commands, like:
      * wb_differential_wheels_set_speed(100.0,100.0);
      */
      KEY=wb_keyboard_get_key();

      switch (KEY) {
         case WB_KEYBOARD_LEFT:{

           L_key=new_velocity;
           L_key=-L_key;
         }
         break;
         case WB_KEYBOARD_RIGHT:{
           R_key=new_velocity;
           R_key=-R_key;
         }
         break;
         case WB_KEYBOARD_UP:{
           L_key=VMAX;
           R_key=VMAX;
           y=0;
           x=1;
         }
         break;
         case WB_KEYBOARD_DOWN:{
           L_key=VLOW;
           R_key=VLOW;
           x=0;
           y=1;

         }
         break;

       }


      if (KEY==-1) {
        if (x==1) {
          L_key=VMAX;
          R_key=VMAX;
          new_velocity=VMAX;
        }
        else if (y==1) {
          L_key=-VLOW;
          R_key=-VLOW;
          new_velocity=-VLOW;
        }
        else {
          L_key=VELOCITY;
          R_key=VELOCITY;
          new_velocity=VELOCITY;
        }


       }

      RW_key=(R_key/(2*PI))*DW*PI;
     LW_key=(L_key/(2*PI))*DW*PI;

      printf("valor rueda derecha = %f m/s \n",RW_key);
      printf("valor rueda izquierda = %f m/s \n",LW_key);
    //printf("valor key = %i \n",KEY);

    wb_motor_set_velocity(wheel_right,R_key);
    wb_motor_set_velocity(wheel_left,L_key);
   };

   /* Enter your cleanup code here */

   /* This is necessary to cleanup webots resources */
   wb_robot_cleanup();

   return 0;
 }
