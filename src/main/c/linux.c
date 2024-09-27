#ifndef _WIN32

#include "us_itshighnoon_nowplaying_NowPlaying.h"

#include <jni.h>

#include <dbus/dbus.h>

JNIEXPORT jint JNICALL Java_us_itshighnoon_nowplaying_NowPlaying_get(JNIEnv *env, jclass thisInstance,
    jboolean fillImage) {
  // Set up and connect to DBus
  DBusError err;
  DBusConnection* conn;
  int rc;
  dbus_error_init(&err);
  conn = dbus_bus_get(DBUS_BUS_SESSION, &err);
  if (dbus_error_is_set(&err)) {
    printf("Connection error %s\n", err.message);
    dbus_error_free(&err);
  }
  if (conn == NULL) {
    return 0;
  }
  rc = dbus_bus_request_name(conn, "us.itshighnoon.nowplaying", DBUS_NAME_FLAG_REPLACE_EXISTING, &err);
  if (dbus_error_is_set(&err)) {
    printf("Name error %s\n", err.message);
    dbus_error_free(&err);
  }
  if (rc != DBUS_REQUEST_NAME_REPLY_PRIMARY_OWNER) {
    return 0;
  }

  dbus_connection_unref(conn);
  return 4;
}

#endif
