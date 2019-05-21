#include "ros/ros.h"
#include "math.h"
//include message types
// for bot , z pointing up , x pointing forward

#define kp_s 0
#define ki_s 0
#define kd_s 0

#define kp_p 0
#define ki_p 0
#define kd_p 0

#define kp_y 0
#define ki_y 0
#define kd_y 0

int req_vel[3];

int prev_s_err = 0 , prev_p_err = 0 , prev_y_err = 0;
int sum_s_err = 0 , sum_p_err = 0 , sum_y_err = 0 ; 
int tol; //tolerance for pid
int main(int argc , char **argv)
{
	int curr_pos_w[3] , curr_pos_b[3] , goal_pos_w[3] , goal_pos_b[3];
	curr_pos_b[3] = transform(curr_pos_w[3]); 
	goal_pos_b[3] = transform(goal_pos_w[3]); //transforming from world frame to bot frame
	surge_goal = goal_pos_b[0];
	pitch_goal = atan(goal_pos_b[2]/goal_pos_b[0]);  //getting goals in surge , pitch and yaw
	yaw_goal = atan(goal_pos_b[1]/goal_pos_b[0]);
	velocity_controller(surge_goal , pitch_goal , yaw_goal); 
	//publish req_vel in the corresponding topic to control thrusters
}


void velocity_controller(surge_g , pitch_g , yaw_g )
{
	int req_linvel , req_p_angvel , req_y_angvel , req_vel[3];
	req_linvel = surge(surge_g , curr_pos_b[0] , tol);
	req_p_angvel = pitch(pitch_g , curr_p_avel , tol);
	req_y_angvel = yaw(yaw_g , curr_y_avel , tol);
	req_vel[3] ={req_linvel , req_p_angvel , req_y_angvel};
	return ;
}




int surge(int surge_g , int curr_pos)
{
	int goal_lvel , req_lvel;	
	if(sqrt((surge_g - curr_pos)^2) <= tol)
	{
		req_lvel = 0;
		return req_lvel;
	}	
	goal_lvel = pid_s(surge_g , curr_pos , );   
	req_lvel = pid_s(goal_lvel , curr_lvel , );
	return req_lvel;
}

int pitch(int pitch_g ,int curr_p_avel)
{
	int goal_p_avel , req_p_avel;	
	if(pitch_g <= tol)
	{
		req_p_avel = 0;
		return req_p_avel;
	}	
	goal_p_avel = pid_p(pitch_g, 0 ,);  // 0 because current frame is fixed to bot so current angular position is always 0
	req_p_avel = pid_p(goal_p_avel , curr_p_avel , );
	return req_p_avel;
}

int yaw(int yaw_g , int curr_y_avel)
{
	int goal_y_avel , req_y_avel;		
	if(yaw_g <= tol)
	{
		req_y_avel = 0;
		return req_y_avel;
	}
	goal_y_avel = pid_y(yaw_g ,0 ,);    // since frame is fixed to the bot goal keeps continuosly changing in bot frame
	req_y_avel = pid_y(goal_y_avel , curr_y_avel); //first pid to position to get goal velocity and then pid between goal and curr to get req

	return req_y_avel;
}

int pid_s(x , y)
{
	int pid_res , err_curr;
	err_curr = x - y;
	sum_s_err += err_curr;	
	pid_res = kp_s*err_curr + ki_s*sum_s_err  + kd_s*(err_curr - prev_s_err);
	return pid_res
}


int pid_p(x , y)
{
	int pid_res , err_curr;
	err_curr = x - y;
	sum_p_err += err_curr;	
	pid_res = kp_p*err_curr + ki_p*sum_p_err  + kd_p*(err_curr - prev_p_err);
	return pid_res
}


int pid_y(x , y)
{
	int pid_res , err_curr;
	err_curr = x - y;
	sum_y_err += err_curr;	
	pid_res = kp_y*err_curr + ki_y*sum_y_err  + kd_y*(err_curr - prev_y_err);
	return pid_res
}


