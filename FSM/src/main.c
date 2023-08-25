/**
 * 有限状态机实现电梯控制
 */
#include <stdio.h>
//#include <windows.h> //windows
#include <unistd.h>  //linux

// 定义电梯运行状态
enum {
  ELEVATOR_UP = 1,
  ELEVATOR_DOWN,
  ELEVATOR_STOP,
  ELEVATOR_OPEN,
  ELEVATOR_CLOSE,
  ELEVATOR_IDLE,
  ELEVATOR_ERROR,
  ELEVATOR_MAX,
};

// 定义电梯事件
enum {
  ELEVATOR_EVENT_UP = 1,
  ELEVATOR_EVENT_DOWN,
  ELEVATOR_EVENT_STOP,
  ELEVATOR_EVENT_OPEN,
  ELEVATOR_EVENT_CLOSE,
  ELEVATOR_EVENT_IDLE,
  ELEVATOR_EVENT_ERROR,
  ELEVATOR_EVENT_MAX,
};

// 定义某个状态下的事件处理函数

// 电梯上行状态下的事件处理函数
void elevator_up_event_handler(int event) {
  switch (event) {
    case ELEVATOR_EVENT_UP:
      printf("电梯上行中...\n");
      break;
    case ELEVATOR_EVENT_DOWN:
      printf("电梯上行中，不能下行...\n");
      break;
    case ELEVATOR_EVENT_STOP:
      printf("电梯上行中，不能停止...\n");
      break;
    case ELEVATOR_EVENT_OPEN:
      printf("电梯上行中，不能开门...\n");
      break;
    case ELEVATOR_EVENT_CLOSE:
      printf("电梯上行中，不能关门...\n");
      break;
    case ELEVATOR_EVENT_IDLE:
      printf("电梯上行中，不能空闲...\n");
      break;
    case ELEVATOR_EVENT_ERROR:
      printf("电梯上行中，不能故障...\n");
      break;
    default:
      printf("电梯上行中，不能处理该事件...\n");
      break;
  }
}

// 电梯下行状态下的事件处理函数
void elevator_down_event_handler(int event) {
  switch (event) {
    case ELEVATOR_EVENT_UP:
      printf("电梯下行中，不能上行...\n");
      break;
    case ELEVATOR_EVENT_DOWN:
      printf("电梯下行中...\n");
      break;
    case ELEVATOR_EVENT_STOP:
      printf("电梯下行中，不能停止...\n");
      break;
    case ELEVATOR_EVENT_OPEN:
      printf("电梯下行中，不能开门...\n");
      break;
    case ELEVATOR_EVENT_CLOSE:
      printf("电梯下行中，不能关门...\n");
      break;
    case ELEVATOR_EVENT_IDLE:
      printf("电梯下行中，不能空闲...\n");
      break;
    case ELEVATOR_EVENT_ERROR:
      printf("电梯下行中，不能故障...\n");
      break;
    default:
      printf("电梯下行中，不能处理该事件...\n");
      break;
  }
}

// 电梯停止状态下的事件处理函数
void elevator_stop_event_handler(int event) {
  switch (event) {
    case ELEVATOR_EVENT_UP:
      printf("电梯停止中，不能上行...\n");
      break;
    case ELEVATOR_EVENT_DOWN:
      printf("电梯停止中，不能下行...\n");
      break;
    case ELEVATOR_EVENT_STOP:
      printf("电梯停止中...\n");
      break;
    case ELEVATOR_EVENT_OPEN:
      printf("电梯停止中，开门...\n");
      break;
    case ELEVATOR_EVENT_CLOSE:
      printf("电梯停止中，关门...\n");
      break;
    case ELEVATOR_EVENT_IDLE:
      printf("电梯停止中，不能空闲...\n");
      break;
    case ELEVATOR_EVENT_ERROR:
      printf("电梯停止中，不能故障...\n");
      break;
    default:
      printf("电梯停止中，不能处理该事件...\n");
      break;
  }
}

// 电梯开门状态下的事件处理函数
void elevator_open_event_handler(int event) {
  switch (event) {
    case ELEVATOR_EVENT_UP:
      printf("电梯开门中，不能上行...\n");
      break;
    case ELEVATOR_EVENT_DOWN:
      printf("电梯开门中，不能下行...\n");
      break;
    case ELEVATOR_EVENT_STOP:
      printf("电梯开门中，不能停止...\n");
      break;
    case ELEVATOR_EVENT_OPEN:
      printf("电梯开门中...\n");
      break;
    case ELEVATOR_EVENT_CLOSE:
      printf("电梯开门中，关门...\n");
      break;
    case ELEVATOR_EVENT_IDLE:
      printf("电梯开门中，不能空闲...\n");
      break;
    case ELEVATOR_EVENT_ERROR:
      printf("电梯开门中，不能故障...\n");
      break;
    default:
      printf("电梯开门中，不能处理该事件...\n");
      break;
  }
}

// 电梯关门状态下的事件处理函数
void elevator_close_event_handler(int event) {
  switch (event) {
    case ELEVATOR_EVENT_UP:
      printf("电梯关门中，不能上行...\n");
      break;
    case ELEVATOR_EVENT_DOWN:
      printf("电梯关门中，不能下行...\n");
      break;
    case ELEVATOR_EVENT_STOP:
      printf("电梯关门中，不能停止...\n");
      break;
    case ELEVATOR_EVENT_OPEN:
      printf("电梯关门中，开门...\n");
      break;
    case ELEVATOR_EVENT_CLOSE:
      printf("电梯关门中...\n");
      break;
    case ELEVATOR_EVENT_IDLE:
      printf("电梯关门中，不能空闲...\n");
      break;
    case ELEVATOR_EVENT_ERROR:
      printf("电梯关门中，不能故障...\n");
      break;
    default:
      printf("电梯关门中，不能处理该事件...\n");
      break;
  }
}

// 电梯空闲状态下的事件处理函数
void elevator_idle_event_handler(int event) {
  switch (event) {
    case ELEVATOR_EVENT_UP:
      printf("电梯空闲中，上行...\n");
      break;
    case ELEVATOR_EVENT_DOWN:
      printf("电梯空闲中，下行...\n");
      break;
    case ELEVATOR_EVENT_STOP:
      printf("电梯空闲中，不能停止...\n");
      break;
    case ELEVATOR_EVENT_OPEN:
      printf("电梯空闲中，不能开门...\n");
      break;
    case ELEVATOR_EVENT_CLOSE:
      printf("电梯空闲中，不能关门...\n");
      break;
    case ELEVATOR_EVENT_IDLE:
      printf("电梯空闲中...\n");
      break;
    case ELEVATOR_EVENT_ERROR:
      printf("电梯空闲中，不能故障...\n");
      break;
    default:
      printf("电梯空闲中，不能处理该事件...\n");
      break;
  }
}

// 电梯故障状态下的事件处理函数
void elevator_error_event_handler(int event) {
  switch (event) {
    case ELEVATOR_EVENT_UP:
      printf("电梯故障中，不能上行...\n");
      break;
    case ELEVATOR_EVENT_DOWN:
      printf("电梯故障中，不能下行...\n");
      break;
    case ELEVATOR_EVENT_STOP:
      printf("电梯故障中，不能停止...\n");
      break;
    case ELEVATOR_EVENT_OPEN:
      printf("电梯故障中，不能开门...\n");
      break;
    case ELEVATOR_EVENT_CLOSE:
      printf("电梯故障中，不能关门...\n");
      break;
    case ELEVATOR_EVENT_IDLE:
      printf("电梯故障中，不能空闲...\n");
      break;
    case ELEVATOR_EVENT_ERROR:
      printf("电梯故障中...\n");
      break;
    default:
      printf("电梯故障中，不能处理该事件...\n");
      break;
  }
}

// 定义电梯状态机的状态转换表结构
typedef struct FsmTable_s {
  int event;              //事件
  int CurState;           //当前状态
  void (*eventActFun)();  //函数指针
  int NextState;          //下一个状态
} FsmTable_t;

// 定义电梯状态机的状态转换表
FsmTable_t FsmTable[] = {
    //{到来的事件，当前的状态，将要要执行的函数，下一个状态}
    {ELEVATOR_EVENT_UP, ELEVATOR_UP, elevator_up_event_handler, ELEVATOR_UP},
    {ELEVATOR_EVENT_UP, ELEVATOR_DOWN, elevator_up_event_handler, ELEVATOR_UP},
    {ELEVATOR_EVENT_UP, ELEVATOR_STOP, elevator_up_event_handler, ELEVATOR_UP},
    {ELEVATOR_EVENT_UP, ELEVATOR_OPEN, elevator_up_event_handler, ELEVATOR_UP},
    {ELEVATOR_EVENT_UP, ELEVATOR_CLOSE, elevator_up_event_handler, ELEVATOR_UP},
    {ELEVATOR_EVENT_UP, ELEVATOR_IDLE, elevator_up_event_handler, ELEVATOR_UP},
    {ELEVATOR_EVENT_UP, ELEVATOR_ERROR, elevator_up_event_handler, ELEVATOR_UP},

    {ELEVATOR_EVENT_DOWN, ELEVATOR_UP, elevator_down_event_handler,
     ELEVATOR_DOWN},
    {ELEVATOR_EVENT_DOWN, ELEVATOR_DOWN, elevator_down_event_handler,
     ELEVATOR_DOWN},
    {ELEVATOR_EVENT_DOWN, ELEVATOR_STOP, elevator_down_event_handler,
     ELEVATOR_DOWN},
    {ELEVATOR_EVENT_DOWN, ELEVATOR_OPEN, elevator_down_event_handler,
     ELEVATOR_DOWN},
    {ELEVATOR_EVENT_DOWN, ELEVATOR_CLOSE, elevator_down_event_handler,
     ELEVATOR_DOWN},
    {ELEVATOR_EVENT_DOWN, ELEVATOR_IDLE, elevator_down_event_handler,
     ELEVATOR_DOWN},
    {ELEVATOR_EVENT_DOWN, ELEVATOR_ERROR, elevator_down_event_handler,
     ELEVATOR_DOWN},

    {ELEVATOR_EVENT_STOP, ELEVATOR_UP, elevator_stop_event_handler,
     ELEVATOR_STOP},
    {ELEVATOR_EVENT_STOP, ELEVATOR_DOWN, elevator_stop_event_handler,
     ELEVATOR_STOP},
    {ELEVATOR_EVENT_STOP, ELEVATOR_STOP, elevator_stop_event_handler,
     ELEVATOR_STOP},
    {ELEVATOR_EVENT_STOP, ELEVATOR_OPEN, elevator_stop_event_handler,
     ELEVATOR_STOP},
    {ELEVATOR_EVENT_STOP, ELEVATOR_CLOSE, elevator_stop_event_handler,
     ELEVATOR_STOP},
    {ELEVATOR_EVENT_STOP, ELEVATOR_IDLE, elevator_stop_event_handler,
     ELEVATOR_STOP},
    {ELEVATOR_EVENT_STOP, ELEVATOR_ERROR, elevator_stop_event_handler,
     ELEVATOR_STOP},

    {ELEVATOR_EVENT_OPEN, ELEVATOR_UP, elevator_open_event_handler,
     ELEVATOR_UP},
    {ELEVATOR_EVENT_OPEN, ELEVATOR_DOWN, elevator_open_event_handler,
     ELEVATOR_DOWN},
    {ELEVATOR_EVENT_OPEN, ELEVATOR_STOP, elevator_open_event_handler,
     ELEVATOR_STOP},
    {ELEVATOR_EVENT_OPEN, ELEVATOR_OPEN, elevator_open_event_handler,
     ELEVATOR_OPEN},
    {ELEVATOR_EVENT_OPEN, ELEVATOR_CLOSE, elevator_open_event_handler,
     ELEVATOR_CLOSE},
    {ELEVATOR_EVENT_OPEN, ELEVATOR_IDLE, elevator_open_event_handler,
     ELEVATOR_EVENT_OPEN},
    {ELEVATOR_EVENT_OPEN, ELEVATOR_ERROR, elevator_open_event_handler,
     ELEVATOR_ERROR},

    {ELEVATOR_EVENT_CLOSE, ELEVATOR_UP, elevator_close_event_handler,
     ELEVATOR_UP},
    {ELEVATOR_EVENT_CLOSE, ELEVATOR_DOWN, elevator_close_event_handler,
     ELEVATOR_DOWN},
    {ELEVATOR_EVENT_CLOSE, ELEVATOR_STOP, elevator_close_event_handler,
     ELEVATOR_STOP},
    {ELEVATOR_EVENT_CLOSE, ELEVATOR_OPEN, elevator_close_event_handler,
     ELEVATOR_OPEN},
    {ELEVATOR_EVENT_CLOSE, ELEVATOR_CLOSE, elevator_close_event_handler,
     ELEVATOR_CLOSE},
    {ELEVATOR_EVENT_CLOSE, ELEVATOR_IDLE, elevator_close_event_handler,
     ELEVATOR_IDLE},
    {ELEVATOR_EVENT_CLOSE, ELEVATOR_ERROR, elevator_close_event_handler,
     ELEVATOR_ERROR},

    {ELEVATOR_EVENT_IDLE, ELEVATOR_UP, elevator_idle_event_handler,
     ELEVATOR_UP},
    {ELEVATOR_EVENT_IDLE, ELEVATOR_DOWN, elevator_idle_event_handler,
     ELEVATOR_DOWN},
    {ELEVATOR_EVENT_IDLE, ELEVATOR_STOP, elevator_idle_event_handler,
     ELEVATOR_STOP},
    {ELEVATOR_EVENT_IDLE, ELEVATOR_OPEN, elevator_idle_event_handler,
     ELEVATOR_OPEN},
    {ELEVATOR_EVENT_IDLE, ELEVATOR_CLOSE, elevator_idle_event_handler,
     ELEVATOR_EVENT_IDLE},
    {ELEVATOR_EVENT_IDLE, ELEVATOR_IDLE, elevator_idle_event_handler,
     ELEVATOR_IDLE},
    {ELEVATOR_EVENT_IDLE, ELEVATOR_ERROR, elevator_idle_event_handler,
     ELEVATOR_ERROR},

    {ELEVATOR_EVENT_ERROR, ELEVATOR_UP, elevator_error_event_handler,
     ELEVATOR_ERROR},
    {ELEVATOR_EVENT_ERROR, ELEVATOR_DOWN, elevator_error_event_handler,
     ELEVATOR_ERROR},
    {ELEVATOR_EVENT_ERROR, ELEVATOR_STOP, elevator_error_event_handler,
     ELEVATOR_ERROR},
    {ELEVATOR_EVENT_ERROR, ELEVATOR_OPEN, elevator_error_event_handler,
     ELEVATOR_ERROR},
    {ELEVATOR_EVENT_ERROR, ELEVATOR_CLOSE, elevator_error_event_handler,
     ELEVATOR_ERROR},
    {ELEVATOR_EVENT_ERROR, ELEVATOR_IDLE, elevator_error_event_handler,
     ELEVATOR_ERROR},
    {ELEVATOR_EVENT_ERROR, ELEVATOR_ERROR, elevator_error_event_handler,
     ELEVATOR_ERROR},

};

// 定义一个状态机结构，表示一个状态机
typedef struct FSM_s {
  FsmTable_t *FsmTable;  //状态转换表
  int CurState;          //当前状态
} FSM_t;

// 初始化状态机
void FSM_Regist(FSM_t *fsm, FsmTable_t *fsm_table, int state) {
  fsm->FsmTable = fsm_table;
  fsm->CurState = state;
}

// 状态机处理事件
void FSM_EventHandle(FSM_t *fsm, int event) {
  FsmTable_t *pActTable = fsm->FsmTable;
  void (*eventActFun)() = NULL;
  int NextState;
  for (int i = 0; i < ELEVATOR_EVENT_MAX; i++) {
    if (event == pActTable[i].event) {
      eventActFun = pActTable[i].eventActFun;
      NextState = pActTable[i].NextState;
      break;
    }
  }
  if (eventActFun) {
    eventActFun();
    fsm->CurState = NextState;
  } else {
    printf("当前事件没有对应的处理函数！\n");
  }
}

// 状态迁移函数
void FSM_StateTransfer(FSM_t *fsm, int state) { fsm->CurState = state; }

int main() {
  FSM_t fsm;
  FSM_Regist(&fsm, FsmTable, ELEVATOR_IDLE);
  while (1) {
    int event;
    printf("请输入事件：");
    scanf("%d", &event);
    FSM_EventHandle(&fsm, event);
    sleep(1);
  }
  return 0;
}

// TODO
// 模拟带楼层时的电梯状态机
// 考虑电梯人数限制
