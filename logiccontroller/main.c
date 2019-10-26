#include <ipc.h>
#include <rng.h>
#include <tock.h>
#include <timer.h>
#include <temperature.h>

static void ipc_callback(int pid, int len, int buf, __attribute__ ((unused)) void* ud) {
  uint8_t* buffer = (uint8_t*) buf;
  int* rng;


  printf("%c,%d.%d,%d.%d\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4]);


  
  ipc_notify_client(pid);
}

// We will have methods here to write to file system or identify the directory

int main(void) {
  // Register the IPC service for this app. It is identified by the PACKAGE_NAME
  // of this app.
  ipc_register_svc(ipc_callback, NULL);


  return 0;
}
