/*
 * State graph:
 *           
 *           ---                    ---
 *          | 1 | --- event 1----> | 2 |
 *           ---                    ---
 *            \                      /
 *             \                    /
 *              \                  /
 *              event3           event2
 *                 \            /
 *                  \          /
 *                   \        /
 *                    \      /
 *                    \/    \/
 *                       ---
 *                      | 3 |
 *                       ---
 *
 */

#include <stdio.h>

#include "fsm_engine.h"

#define STATE1 1
#define STATE2 2
#define STATE3 3

#define EVENT1 1
#define EVENT2 2
#define EVENT3 3

void state1Event1Fun(void* pFsm)
{
	fsm_moveState((FSM_T*)pFsm, STATE2);
	printf("Act: %s\n", __func__);
	return;
}

void state1Event3Fun(void* pFsm)
{
	fsm_moveState((FSM_T*)pFsm, STATE3);
	printf("Act: %s\n", __func__);
	return;
}

void state2Event2Fun(void* pFsm)
{
	fsm_moveState((FSM_T*)pFsm, STATE3);
	printf("Act: %s\n", __func__);
	return;
}

ACT_TABLE_T state1ActTable[] = {
	{EVENT1, &state1Event1Fun},
	{EVENT3, &state1Event3Fun},
};

ACT_TABLE_T state2ActTable[] = {
	{EVENT2, &state2Event2Fun},
};

STATE_TABLE_T FsmTable[] = {
	{STATE1, state1ActTable},
	{STATE2, state2ActTable},
	//{STATE3, state3ActTable},
};

int main(int argc, char* argv[])
{
	FSM_T fsm;
	size_t state_num = 3;
	printf("State num: %zu\n", state_num);

	fsm_register(&fsm, FsmTable, state_num);
	fsm_moveState(&fsm, STATE1);
	fsm_eventHandle(&fsm, EVENT1);
	fsm_eventHandle(&fsm, EVENT2);

	return 0;
}
