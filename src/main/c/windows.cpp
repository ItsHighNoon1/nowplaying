#ifdef _WIN32

#include "us_itshighnoon_nowplaying_NowPlaying.h"

#include <chrono>
#include <ratio>

#include <jni.h>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Media.h>
#include <winrt/Windows.Media.Control.h>

using namespace winrt;

JNIEXPORT jint JNICALL Java_us_itshighnoon_nowplaying_NowPlaying_get(JNIEnv *env, jclass thisInstance,
    jboolean fillImage) {
  // Get control structures from WinRT
  winrt::init_apartment();
  auto asyncRequest = Windows::Media::Control::GlobalSystemMediaTransportControlsSessionManager::RequestAsync();
  Windows::Media::Control::GlobalSystemMediaTransportControlsSessionManager sessionManager = asyncRequest.get();
  Windows::Media::Control::GlobalSystemMediaTransportControlsSession session { sessionManager.GetCurrentSession() };
  Windows::Media::Control::GlobalSystemMediaTransportControlsSessionPlaybackInfo playbackInfo =
      session.GetPlaybackInfo();
  Windows::Media::Control::GlobalSystemMediaTransportControlsSessionTimelineProperties timelineProperties =
      session.GetTimelineProperties();
  Windows::Media::Control::GlobalSystemMediaTransportControlsSessionMediaProperties mediaProperties =
      session.TryGetMediaPropertiesAsync().get();

  // Extract fields we care about
  bool shuffle = winrt::unbox_value_or<bool>(playbackInfo.IsShuffleActive(), false);
  double rate = winrt::unbox_value_or<double>(playbackInfo.PlaybackRate(), -1.0);
  std::chrono::milliseconds startTime = std::chrono::duration_cast<std::chrono::milliseconds>(
      timelineProperties.StartTime());
  std::chrono::milliseconds currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
      timelineProperties.Position());
  std::chrono::milliseconds endTime = std::chrono::duration_cast<std::chrono::milliseconds>(
      timelineProperties.EndTime());
  std::chrono::milliseconds minSeek = std::chrono::duration_cast<std::chrono::milliseconds>(
      timelineProperties.MinSeekTime());
  std::chrono::milliseconds maxSeek = std::chrono::duration_cast<std::chrono::milliseconds>(
      timelineProperties.MaxSeekTime());
  printf("%d %d\n", maxSeek.count(), endTime.count());

  return 4;
}

#endif
