#ifndef FSM_ENGINE_H
#define FSM_ENGINE_H

typedef void (* ActFun) (void*);

typedef struct act_table_t {
	int event;
	ActFun eventActFun;
} ACT_TABLE_T;

typedef struct state_table_t {
	int state;
	ACT_TABLE_T* act_table;
} STATE_TABLE_T;

typedef struct fsm_t{
	STATE_TABLE_T* FsmTable;
	int curState;
	unsigned int state_num;
} FSM_T;

void fsm_register(FSM_T* pFsm, STATE_TABLE_T* pStateTable, unsigned int state_num);
	
void fsm_moveState(FSM_T* pFsm, int state);
	
void fsm_eventHandle(FSM_T* pFsm, int state);

ACT_TABLE_T* fsm_getActTable(FSM_T* pFsm);




#endif
