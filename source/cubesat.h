/*
 * cubesat.h
 *
 *  Created on: Nov 28, 2017
 *      Author: Student
 */

#ifndef SOURCE_CUBESAT_H_
#define SOURCE_CUBESAT_H_
#include "fsl_flexcan.h"

typedef struct _cs_event {
	flexcan_frame_t	canframe;
	long			timestamp;
	int				inout;
	int				sourcedest;
} cs_event;

#define FROM_PIT 0
#define FROM_CAN 1

#define EVENT_IN	0
#define	EVENT_OUT	1
#define EVENT_IF_CAN	0
#define	EVENT_IF_CAL	1

#endif /* SOURCE_CUBESAT_H_ */
