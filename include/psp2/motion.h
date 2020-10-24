#ifndef _DOLCESDK_PSP2_MOTION_H_
#define _DOLCESDK_PSP2_MOTION_H_

#include <psp2/types.h>

#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
extern "C" {
#endif	/* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#define SCE_MOTION_MAX_NUM_STATES	64				/* Maximum number of states in the state buffer */

#define SCE_MOTION_MAGNETIC_FIELD_UNSTABLE		0	/* Unstable magnetic field, reliability of NED matrix is very low */
#define SCE_MOTION_MAGNETIC_FIELD_STABLE		1	/* Currently Not In Use*/
#define SCE_MOTION_MAGNETIC_FIELD_VERYSTABLE	2	/* Magnetic field is very stable and NED matrix can be used */

#define SCE_MOTION_FORCED_STOP_POWER_CONFIG_CHANGE	(1<<0)		/* Forced stop due to power configuration change */

/* Data Types */

/* Struct to hold the current state as calculated by libMotion */
typedef struct SceMotionState {

	SceUInt32							timestamp;				/* Device Local Timestamp */
	SceFVector3							acceleration;			/* Stores the accelerometer readings */
	SceFVector3							angularVelocity;		/* Stores the angular velocity readings */

	SceUInt8							reserve1[12];			/* Reserved data */

	SceFQuaternion						deviceQuat;				/* Device orientation as a Quaternion <x,y,z,w> */
	SceUMatrix4							rotationMatrix;			/* Device orientation as a rotation matrix */
	SceUMatrix4							nedMatrix;				/* Magnetic North rotation matrix Col0: North Col1: East Col2: Down */

	SceUInt8							reserve2[4];			/* Reserved data */

	SceFVector3							basicOrientation;		/*Basic orientation of the device*/
	SceUInt64							hostTimestamp;			/*Time at which the sampled data packet is received from the device*/

	SceUInt8							reserve3[36];			/* Reserved data */

	SceUInt8							magnFieldStability;		/* Stability of the Magnetic North output */

	SceUInt8							dataInfo;				/* Information on the current data */
																/* Bit:0 - Determine if the motion data has been forcibly stopped*/

	SceUInt8							reserve4[2];			/* Reserved data */

} SceMotionState;

/* Stuct to hold raw sensor data */
typedef struct SceMotionSensorState {

	SceFVector3							accelerometer;			/* Stores the accelerometer readings */
	SceFVector3							gyro;					/* Stores the angular velocity readings */

	SceUInt8							reserve1[12];			/* Reserved data */

	SceUInt32							timestamp;				/* Sensor Packet Timestamp */
	SceUInt32							counter;				/* A counter to identify state */

	SceUInt8							reserve2[4];			/* Reserved data */

	SceUInt64							hostTimestamp;			/*Time at which the sampled data packet is received from the device*/

	SceUInt8							dataInfo;				/* Information on the current data */
																/* Bit:0 - Determine if the motion data has been forcibly stopped*/
	SceUInt8							reserve3[7];			/* Reserved data */


} SceMotionSensorState;

/* Physical Location of Motion Sensors */
typedef struct SceMotionDeviceLocation{
	SceFVector3 accelerometer;
	SceFVector3	gyro;
	SceUInt8    reserve[24];
}SceMotionDeviceLocation;

/* Functions */

/*
 * Calculate and update the new motion states
 * @param *motionState : State Pointer to save data into
 * @retval SCE_OK success
 *			<SCE_OK Error
 */

int sceMotionGetState(SceMotionState *motionState);

/*
 * Retrieve the new raw motion data states
 * @param *sensorState : Struct to hold the sensor data
 * @param numRecords Number of records to pull from buffer
 * @retval  SCE_OK success
 *			<SCE_OK Error
 */

int sceMotionGetSensorState(SceMotionSensorState *sensorState, int numRecords);

/*
 * Retrieve the basic orientation of the device in reference to gravity.
 * @retval SCE_OK success
 *			<SCE_OK Error
 */

int sceMotionGetBasicOrientation(SceFVector3 *basicOrientation);

/*
 * Rotate only along the yaw axis.
 * @param radians : Angle in radians to rotate.
 * @retval SCE_OK
 */

int sceMotionRotateYaw(const float radians);

/*
 * Retrieve the status of tilt correction filter settings
 * @retval  SCE_TRUE = Tilt Correction Enabled
 *			SCE_FALSE = Tilt Correction Disabled
 */

SceBool	sceMotionGetTiltCorrection(void);

/*
 * Set the tilt correction filter settings
 * @param setValue SCE_TRUE = Enable Tilt Correction
 *				   SCE_FALSE = Disable Tilt Correction
 * @retval  SCE_OK
 */

int sceMotionSetTiltCorrection(SceBool setValue);

/*
 * Retrieve the status of deadband filter mode
 * @retval  SCE_TRUE = Deadband Enabled
 *			SCE_FALSE = Deadband Disabled
 */

SceBool	sceMotionGetDeadband(void);

/*
 * Set the deadbanding filter mode
 * @param setValue SCE_TRUE = Enable Deadbanding
 *				   SCE_FALSE = Disable Deadbanding
 * @retval  SCE_OK
 */

int sceMotionSetDeadband(SceBool setValue);

/*
 * Set the range of angles for basic orientation calculation
 * @param angle
 * @retval SCE_OK success
 *			<SCE_OK Error
 */

int sceMotionSetAngleThreshold(const float angle);

/*
 * Get the angle threshold values for basic orientation calculation
 * @retval float value representing the angle threshold
 */

float sceMotionGetAngleThreshold(void);

/*
 * Reset the device posture and filter settings.
 * @retval  SCE_OK success
 *			<SCE_OK Error
 */

int sceMotionReset(void);

/*
 * Turn on sampling for the magnetometer.
 * @retval  SCE_OK success
 *			<SCE_OK Error
 */

int sceMotionMagnetometerOn(void);

/*
 * Turn off sampling for the magnetometer.
 * @retval  SCE_OK success
 *			<SCE_OK Error
 */

int sceMotionMagnetometerOff(void);

/*
 * Return the state of the magnetometer sampling.
 * @retval  SCE_TRUE = Sampling ON
 *			SCE_FALSE = Sampling OFF
 */

SceBool sceMotionGetMagnetometerState(void);

/*
 * Begin sampling data.
 * @retval SCE_OK success
 *			<SCE_OK Error
 */

int sceMotionStartSampling(void);

/*
 * Stop sampling data.
 * @retval SCE_OK success
 *			<SCE_OK Error
 */
int sceMotionStopSampling(void);

/*
 * Receive the physical location of the sensor device(s).
 * @retval  SCE_OK success
 *			<SCE_OK Error
 */

int sceMotionGetDeviceLocation(SceMotionDeviceLocation *devLocation);

/*
 * Retrieve the status of automatic gyro bias correction
 * @retval  SCE_TRUE = Gyro Bias Correction Enabled
 *			SCE_FALSE = Gyro Bias Correction Disabled
 */

SceBool	sceMotionGetGyroBiasCorrection(void);

/*
 * Turn on/off automatic gyro bias correction
 * @param setValue SCE_TRUE =  Enable Gyro Bias Correction
 *				   SCE_FALSE = Disable Gyro Bias Correction
 * @retval  SCE_OK
 */

int sceMotionSetGyroBiasCorrection(SceBool setValue);

/*
 * Error number definition
 */

/**
 * @e Invalid Data @ee
 */
#define SCE_MOTION_ERROR_DATA_INVALID			-2143944192	/* 0x80360200 */

/**
 * @e Read Error @ee
 */
#define SCE_MOTION_ERROR_READING				-2143944191	/* 0x80360201 */

/**
 * @e Init Error @ee
 */
#define SCE_MOTION_ERROR_NON_INIT_ERR			-2143944190	/* 0x80360202 */

/**
 * @e Invalid State @ee
 */
#define SCE_MOTION_ERROR_STATE_INVALID			-2143944189	/* 0x80360203 */

/**
 * @e Error Reading Calibration @ee
 */
#define SCE_MOTION_ERROR_CALIB_READ_FAIL		-2143944188	/* 0x80360204 */

/**
 * @e Out of Bounds @ee
 */
#define SCE_MOTION_ERROR_OUT_OF_BOUNDS			-2143944187	/* 0x80360205 */

/**
 * @e Sampling not started @ee
 */
#define SCE_MOTION_ERROR_NOT_SAMPLING			-2143944186	/* 0x80360206 */

/**
 * @e Memory Free Failure @ee
 */
#define SCE_MOTION_ERROR_ALREADY_SAMPLING		-2143944185	/* 0x80360207 */

/**
 * @e Library Already Initialized @ee
 */
#define SCE_MOTION_ERROR_MEM_IN_USE				-2143944184	/* 0x80360208 */

/**
 * @e Null Pointer Used as Parameter @ee
 */
#define SCE_MOTION_ERROR_NULL_PARAMETER			-2143944183	/* 0x80360209 */

/**
 * @e Set angle is above 45 degrees or below 0 @ee
 */
#define SCE_MOTION_ERROR_ANGLE_OUT_OF_RANGE		-2143944182	/* 0x8036020A */

/**
 * @e Invalid Argument @ee
 */
#define SCE_MOTION_ERROR_INVALID_ARG			-2143944181	/* 0x8036020B */


#if defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus)
}
#endif  /* defined(_LANGUAGE_C_PLUS_PLUS)||defined(__cplusplus)||defined(c_plusplus) */

#endif /* _DOLCESDK_PSP2_MOTION_H_ */


