/*
 * fsm.c
 *
 *  Created on: Nov 29, 2023
 *      Author: Nhat Khai
 */

#include "fsm.h"

#define FSM_AUTO_TASK 10
#define FSM_MANUAL_TASK 1
#define FSM_TUNNING_TASK 5

enum FSM_STATE fsmState = FSM_AUTO;
static enum TRAFFIC_STATE fsmTunningState = TRAFFIC_RED;

static uint8_t fsmAutoIDs[FSM_AUTO_TASK] = {};
static uint8_t fsmManualIDs[FSM_MANUAL_TASK] = {};
static uint8_t fsmTunningIDs[FSM_TUNNING_TASK] = {};

void fsmAutoStop(void) {
	SCH_AddTask(counterReset, 0, 0);
	SCH_AddTask(pedestrian0Off, 0, 0);
	SCH_AddTask(pedestrian1Off, 0, 0);
}

void fsmAutoProcessing(void) {
	if (buttonPressed(1)) {
		fsmAutoIDs[8] = SCH_AddTask(pedestrian0On, 0, TIMER_TICK);
	}
	if (pedestrianStates[0] == PEDESTRIAN_GREEN && pedestrianCounters[0] == 10) {
		SCH_DeleteTask(fsmAutoIDs[8]);
		SCH_AddTask(pedestrian0Off, 10, 0);
	}
	if (buttonPressed(2)) {
		fsmAutoIDs[9] = SCH_AddTask(pedestrian1On, 0, TIMER_TICK);
	}
	if (pedestrianStates[1] == PEDESTRIAN_GREEN && pedestrianCounters[1] == 10) {
		SCH_DeleteTask(fsmAutoIDs[9]);
		SCH_AddTask(pedestrian1Off, 10, 0);
	}
}

void fsmAuto(void) {
	SCH_AddTask(pedestrian0Off, 0, 0);
	SCH_AddTask(pedestrian1Off, 0, 0);
	fsmAutoIDs[0] = SCH_AddTask(fsmAutoProcessing, 10, TIMER_TICK);
	fsmAutoIDs[1] = SCH_AddTask(counterRun, 0, TIMER_TICK);
	fsmAutoIDs[2] = SCH_AddTask(traffic0Red, 0, trafficRedDuration + trafficYellowDuration + trafficGreenDuration);
	fsmAutoIDs[3] = SCH_AddTask(traffic0Green, trafficRedDuration, trafficRedDuration + trafficYellowDuration + trafficGreenDuration);
	fsmAutoIDs[4] = SCH_AddTask(traffic0Yellow, trafficRedDuration + trafficGreenDuration, trafficRedDuration + trafficYellowDuration + trafficGreenDuration);
	fsmAutoIDs[5] = SCH_AddTask(traffic1Green, 0, trafficRedDuration + trafficYellowDuration + trafficGreenDuration);
	fsmAutoIDs[6] = SCH_AddTask(traffic1Yellow, trafficGreenDuration, trafficRedDuration + trafficYellowDuration + trafficGreenDuration);
	fsmAutoIDs[7] = SCH_AddTask(traffic1Red, trafficGreenDuration + trafficYellowDuration, trafficRedDuration + trafficYellowDuration + trafficGreenDuration);
}

void fsmManualStop(void) {
	SCH_AddTask(traffic0Off, 0, 0);
	SCH_AddTask(traffic1Off, 0, 0);
	SCH_AddTask(pedestrian0Off, 0, 0);
	SCH_AddTask(pedestrian1Off, 0, 0);
}

void fsmManualProcessing(void) {
	if (buttonPressed(1)) {
		switch (trafficStates[0]) {
		case TRAFFIC_RED:
			SCH_AddTask(traffic0Green, 0, 0);
			SCH_AddTask(pedestrian0Off, 0, 0);
			break;
		case TRAFFIC_GREEN:
			SCH_AddTask(traffic0Yellow, 0, 0);
			SCH_AddTask(pedestrian0Off, 0, 0);
			break;
		case TRAFFIC_YELLOW:
			SCH_AddTask(traffic0Red, 0, 0);
			SCH_AddTask(pedestrian0On, 0, 0);
			break;
		default:
			break;
		}
	}
	if (buttonPressed(2)) {
		switch (trafficStates[1]) {
		case TRAFFIC_RED:
			SCH_AddTask(traffic1Green, 0, 0);
			SCH_AddTask(pedestrian1Off, 0, 0);
			break;
		case TRAFFIC_GREEN:
			SCH_AddTask(traffic1Yellow, 0, 0);
			SCH_AddTask(pedestrian1Off, 0, 0);
			break;
		case TRAFFIC_YELLOW:
			SCH_AddTask(traffic1Red, 0, 0);
			SCH_AddTask(pedestrian1On, 0, 0);
			break;
		default:
			break;
		}
	}
}

void fsmManual(void) {
	fsmManualIDs[0] = SCH_AddTask(fsmManualProcessing, 10, TIMER_TICK);
	SCH_AddTask(traffic0Red, 0, 0);
	SCH_AddTask(pedestrian0On, 0, 0);
	SCH_AddTask(traffic1Green, 0, 0);
}

void fsmTunningStop(void) {
	return;
}

void fsmTunningProcessing(void) {
	if (buttonPressed(1)) {
		SCH_DeleteTask(fsmTunningIDs[1]);
		SCH_DeleteTask(fsmTunningIDs[2]);
		SCH_DeleteTask(fsmTunningIDs[3]);
		SCH_DeleteTask(fsmTunningIDs[4]);
		switch (fsmTunningState) {
		case TRAFFIC_RED:
			fsmTunningIDs[1] = SCH_AddTask(traffic0Green, 0, 1000);
			fsmTunningIDs[2] = SCH_AddTask(traffic1Green, 0, 1000);
			fsmTunningIDs[3] = SCH_AddTask(traffic0Off, 500, 1000);
			fsmTunningIDs[4] = SCH_AddTask(traffic1Off, 500, 1000);
			fsmTunningState = TRAFFIC_GREEN;
			break;
		case TRAFFIC_GREEN:
			fsmTunningIDs[1] = SCH_AddTask(traffic0Yellow, 0, 1000);
			fsmTunningIDs[2] = SCH_AddTask(traffic1Yellow, 0, 1000);
			fsmTunningIDs[3] = SCH_AddTask(traffic0Off, 500, 1000);
			fsmTunningIDs[4] = SCH_AddTask(traffic1Off, 500, 1000);
			fsmTunningState = TRAFFIC_YELLOW;
			break;
		case TRAFFIC_YELLOW:
			fsmTunningIDs[1] = SCH_AddTask(traffic0Red, 0, 1000);
			fsmTunningIDs[2] = SCH_AddTask(traffic1Red, 0, 1000);
			fsmTunningIDs[3] = SCH_AddTask(traffic0Off, 500, 1000);
			fsmTunningIDs[4] = SCH_AddTask(traffic1Off, 500, 1000);
			fsmTunningState = TRAFFIC_RED;
			break;
		default:
			break;
		}
	}
	if (buttonPressed(2)) {
		switch (fsmTunningState) {
		case TRAFFIC_RED:
			if (trafficRedDuration < TRAFFIC_DURARION_MAX - TRAFFIC_DURARION_AUTO) {
				trafficRedDuration += TRAFFIC_DURARION_AUTO;
			}
			else {
				trafficRedDuration = TRAFFIC_DURARION_MAX;
			}
			break;
		case TRAFFIC_GREEN:
			if (trafficGreenDuration < TRAFFIC_DURARION_MAX - TRAFFIC_DURARION_AUTO) {
				trafficGreenDuration += TRAFFIC_DURARION_AUTO;
			}
			else {
				trafficGreenDuration = TRAFFIC_DURARION_MAX;
			}
			break;
		case TRAFFIC_YELLOW:
			if (trafficYellowDuration < TRAFFIC_DURARION_MAX - TRAFFIC_DURARION_AUTO) {
				trafficYellowDuration += TRAFFIC_DURARION_AUTO;
			}
			else {
				trafficYellowDuration = TRAFFIC_DURARION_MAX;
			}
			break;
		default:
			break;
		}
	}
	if (buttonPressed(3)) {
		switch (fsmTunningState) {
		case TRAFFIC_RED:
			if (trafficRedDuration > TRAFFIC_DURARION_MIN + TRAFFIC_DURARION_AUTO) {
				trafficRedDuration -= TRAFFIC_DURARION_AUTO;
			}
			else {
				trafficRedDuration = TRAFFIC_DURARION_MIN;
			}
			break;
		case TRAFFIC_GREEN:
			if (trafficGreenDuration > TRAFFIC_DURARION_MIN + TRAFFIC_DURARION_AUTO) {
				trafficGreenDuration -= TRAFFIC_DURARION_AUTO;
			}
			else {
				trafficGreenDuration = TRAFFIC_DURARION_MIN;
			}
			break;
		case TRAFFIC_YELLOW:
			if (trafficYellowDuration > TRAFFIC_DURARION_MIN + TRAFFIC_DURARION_AUTO) {
				trafficYellowDuration -= TRAFFIC_DURARION_AUTO;
			}
			else {
				trafficYellowDuration = TRAFFIC_DURARION_MIN;
			}
			break;
		default:
			break;
		}
	}
}

void fsmTunning(void) {
	fsmTunningIDs[0] = SCH_AddTask(fsmTunningProcessing, 10, TIMER_TICK);
	fsmTunningIDs[1] = SCH_AddTask(traffic0Red, 0, 1000);
	fsmTunningIDs[2] = SCH_AddTask(traffic1Red, 0, 1000);
	fsmTunningIDs[3] = SCH_AddTask(traffic0Off, 500, 1000);
	fsmTunningIDs[4] = SCH_AddTask(traffic1Off, 500, 1000);
}

void fsmInit(void) {
	SCH_AddTask(traffic0Off, 0, 0);
	SCH_AddTask(traffic1Off, 0, 0);
	SCH_AddTask(pedestrian0Off, 0, 0);
	SCH_AddTask(pedestrian1Off, 0, 0);
	SCH_AddTask(fsmAuto, 0, 0);
}

void fsmProcessing(void) {
	if (buttonPressed(0)) {
		switch (fsmState) {
		case FSM_AUTO:
			for (uint8_t i = 0; i < FSM_AUTO_TASK; i ++) {
				SCH_DeleteTask(fsmAutoIDs[i]);
			}
			SCH_AddTask(fsmAutoStop, 0, 0);
			SCH_AddTask(fsmManual, 10, 0);
			fsmState = FSM_MANUAL;
			break;
		case FSM_MANUAL:
			for (uint8_t i = 0; i < FSM_MANUAL_TASK; i ++) {
				SCH_DeleteTask(fsmManualIDs[i]);
			}
			SCH_AddTask(fsmManualStop, 0, 0);
			SCH_AddTask(fsmTunning, 10, 0);
			fsmState = FSM_TUNNING;
			break;
		case FSM_TUNNING:
			for (uint8_t i = 0; i < FSM_TUNNING_TASK; i ++) {
				SCH_DeleteTask(fsmTunningIDs[i]);
			}
			SCH_AddTask(fsmTunningStop, 0, 0);
			SCH_AddTask(fsmAuto, 10, 0);
			fsmState = FSM_AUTO;
			break;
		default:
			break;
		}
	}
}
