#include <ipc.h>
#include <rng.h>
#include <tock.h>
#include <temperature.h>
#include <ambient_light.h>
#include <stdlib.h>

int _notifier_service = -1;
//int _humi_service = -1;

// We use a 64 byte buffer to communicate with classifier
char _notifier_buf[64] __attribute__((aligned(64)));

bool _done = false;
uint8_t _number_of_leds = 0;

int _alert_threshold = 50;


// For this simple example, the callback only need set the yield variable.
static void ipc_callback(__attribute__ ((unused)) int pid,
                         __attribute__ ((unused)) int len,
                         __attribute__ ((unused)) int arg2,
                         __attribute__ ((unused)) void* ud) {
  _done = true;
}


int classifier(int s){
  if (s >= 20){
    return 20;
  }
  else
    return 80;
}

int main(void) {
  // Register the IPC service for this app. It is identified by the PACKAGE_NAME
  // of this app.

  // Register for the notification service
  _notifier_service = ipc_discover("org.tockos.tutorials.babymonitor.logiccontroller");
  

  ipc_register_client_cb(_notifier_service, ipc_callback, NULL);
  ipc_share(_notifier_service, _notifier_buf, 64);
  ipc_register_svc(ipc_callback, NULL);

  _notifier_buf[0] = 't';

  int i = 0;

  //
  while(1) {
    int temp;
    temperature_read_sync(&temp);
    temp = temp/100;
    // printf("temperature is: %d\n", temp);

    int score = classifier(temp);
    
    if(score<=_alert_threshold){
      _notifier_buf[1] = score;
      _notifier_buf[2] = 0;
      _notifier_buf[3] = temp;
      _notifier_buf[4] = temp-(temp/100)*100 + rand()%100;

      _done = false;
      ipc_notify_svc(_notifier_service);
      yield_for(&_done);
    }


    delay_ms(1000);
    i += 1;
  }

  return 0;
}