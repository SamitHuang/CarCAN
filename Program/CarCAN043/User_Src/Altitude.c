#include "config.h"
#include "Altitude.h"
#include "imu.h"
 
//
nav_t nav;		//NED frame in earth
//
float z_est[3];	// estimate z Vz  Az
static float w_z_baro=0.5f;
static float w_z_acc=20.0f;
static float w_acc_bias=0.05f;

/* acceleration in NED frame */
float accel_NED[3] = { 0.0f, 0.0f, -CONSTANTS_ONE_G };
/* store error when sensor updates, but correct on each time step to avoid jumps in estimated value */
float corr_acc[] = { 0.0f, 0.0f, 0.0f };	// N E D ,  m/s2
float acc_bias[] = { 0.0f, 0.0f, 0.0f };	// body frame ,  
float corr_baro = 0.0f;					//m 
//float accb[3]={0,0,0};


//Combine Filter to correct err
void inertial_filter_predict(float dt, float x[3])
{
	x[0] += x[1] * dt + x[2] * dt * dt / 2.0f;
	x[1] += x[2] * dt;
}

void inertial_filter_correct(float e, float dt, float x[3], int i, float w)
{
	float ewdt = e * w * dt;
	x[i] += ewdt;

	if (i == 0) {
		x[1] += w * ewdt;
		x[2] += w * w * ewdt / 3.0;

	} else if (i == 1) {
		x[2] += w * ewdt;
	}
}
 
 


//timeStamp in us. Thread should be executed every 2~20ms
//MS5611_Altitude  , should be in m. (can be fixed to abs, not relative). positive above ground
//accFilted  ,should be filted .
void AltitudeCombineThread(void)
{
	static uint32_t tPre=0;
	uint32_t t;
	float dt;
	static float posZPrev=0;
	
	/* accelerometer bias correction */
	float accel_bias_corr[3] = { 0.0f, 0.0f, 0.0f };
	uint8_t i,j;


	
	
	t=micros();
  dt = (tPre>0)?((t-tPre)/1000000.0f):0;
	tPre=t;
	
		if(!paOffsetInited)	//wait baro to init its offset
			return;
		
		if(!imu.ready)
			return;
	
	//store err when sensor update 
	if(Baro_ALT_Updated)	//后面应该在sensor数值后加一个timeStamp，判断是否更新
	{
			corr_baro = 0 - MS5611_Altitude - z_est[0];		// MS5611_Altitude baro alt, is postive above offset level. not in NED. z_est is in NED frame. 
			Baro_ALT_Updated=0;
	}
 
	if(accUpdated)
	{			
			 imu.accb[0] -= acc_bias[0];
			 imu.accb[1] -= acc_bias[1];
			 imu.accb[2] -= acc_bias[2];
		
	#ifndef ASSUME_LEVEL	
			for(i=0;i<3;i++)
			{
				accel_NED[i]=0.0f;
				for(j=0;j<3;j++)
				{
						accel_NED[i]+=imu.DCMgb[j][i]* imu.accb[j];
				}
			} 
			accel_NED[2]=-accel_NED[2];
		#else
			accel_NED[2]=-accb[2];
		#endif
			
			corr_acc[2] = accel_NED[2] + CONSTANTS_ONE_G - z_est[2];
			
			accUpdated=0;
	}
	
	//correct accelerometer bias every time step 
	accel_bias_corr[2] -= corr_baro * w_z_baro * w_z_baro;

	#ifndef ASSUME_LEVEL
	//transform error vector from NED frame to body frame
		for (i = 0; i < 3; i++) 
	 {
			float c = 0.0f;

			for (j = 0; j < 3; j++) {
				c += imu.DCMgb[i][j] * accel_bias_corr[j];
			}

			acc_bias[i] += c * w_acc_bias * dt;		//accumulate bias
		} 
		
		acc_bias[2]=-acc_bias[2];

	#else
	 	{
	 	float cz= -accel_bias_corr[2];
		acc_bias[2]+=cz* w_acc_bias * dt;
	 	}
	#endif
		
		/* inertial filter prediction for altitude */
		inertial_filter_predict(dt, z_est);
		/* inertial filter correction for altitude */
		inertial_filter_correct(corr_baro, dt, z_est, 0, w_z_baro);	//0.5f
		inertial_filter_correct(corr_acc[2], dt, z_est, 2, w_z_acc);		//20.0f
		
		nav.z=z_est[0];
		nav.vz=z_est[1];
		nav.az=z_est[2];
		
}
