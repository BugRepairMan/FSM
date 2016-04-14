/*
 * From: http://www.cnblogs.com/chencheng/archive/2012/06/25/2562660.html
 *
 */
#include <stdio.h>

#include "fsm_engine.h"

#define MAX_ACT_NUM 6

void fsm_register(FSM_T* pFsm, STATE_TABLE_T* pStateTable, unsigned int state_num)
{
	pFsm->FsmTable = pStateTable;
	pFsm->curState = 0;
	pFsm->state_num = state_num;
	printf("FSM register SUCCEEDED!\n");
	return;
}

void fsm_moveState(FSM_T* pFsm, int state)
{
	int preState = pFsm->curState;
	pFsm->curState = state;
	printf("State: %d ==>> State: %d\n", preState, pFsm->curState); 
	return;
}

void fsm_eventHandle(FSM_T* pFsm, int event)
{
	printf("Coming Event: %d\n", event);
	ACT_TABLE_T* pActTable = (void*)0;
	ActFun eventActFun = (void*)0;
	
	pActTable = fsm_getActTable(pFsm);

	for(int i = 0; i < MAX_ACT_NUM; i++) {
		if(event == pActTable[i].event) {
			eventActFun = pActTable[i].eventActFun;
			break;
		}
	}

	if(eventActFun) {
		eventActFun(pFsm);
	}
}

ACT_TABLE_T* fsm_getActTable(FSM_T* pFsm)
{
	int curState = pFsm->curState;
	STATE_TABLE_T* FsmTable= pFsm->FsmTable;
	//ACT_TABLE_T* cur_act_table =(void *) 0;
	unsigned int state_num = pFsm->state_num;

	for(int i = 0; i < state_num; i++) {
		if(curState == FsmTable[i].state) {
			return FsmTable[i].act_table;
		}
	}

	printf("Error: ActTable not found\n");
	return 0;	
}
