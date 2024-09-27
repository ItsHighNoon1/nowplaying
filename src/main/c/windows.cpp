#ifdef _WIN32

#include "us_itshighnoon_nowplaying_NowPlaying.h"

#include <chrono>
#include <iostream>
#include <ratio>

#include <jni.h>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Media.h>
#include <winrt/Windows.Media.Control.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.UI.Xaml.Media.Imaging.h>
#include <winrt/Windows.Graphics.Imaging.h>

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Media::Control;
using namespace Windows::Storage::Streams;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::Graphics::Imaging;

JNIEXPORT jint JNICALL Java_us_itshighnoon_nowplaying_NowPlaying_get(JNIEnv *env, jclass thisInstance,
    jboolean fillImage) {
  // Get control structures from WinRT
  init_apartment();
  auto asyncRequest = GlobalSystemMediaTransportControlsSessionManager::RequestAsync();
  GlobalSystemMediaTransportControlsSessionManager sessionManager = asyncRequest.get();
  GlobalSystemMediaTransportControlsSession session { sessionManager.GetCurrentSession() };
  if (!session) {
    return 0;
  }
  GlobalSystemMediaTransportControlsSessionPlaybackInfo playbackInfo =
      session.GetPlaybackInfo();
  GlobalSystemMediaTransportControlsSessionTimelineProperties timelineProperties =
      session.GetTimelineProperties();
  GlobalSystemMediaTransportControlsSessionMediaProperties mediaProperties =
      session.TryGetMediaPropertiesAsync().get();

  // Extract fields we care about
  bool playing = playbackInfo.PlaybackStatus() == GlobalSystemMediaTransportControlsSessionPlaybackStatus::Playing;
  bool shuffle = unbox_value_or<bool>(playbackInfo.IsShuffleActive(), false);
  double rate = unbox_value_or<double>(playbackInfo.PlaybackRate(), -1.0);
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
  std::string title = to_string(mediaProperties.Title());
  std::string subtitle = to_string(mediaProperties.Subtitle());
  std::string artist = to_string(mediaProperties.Artist());
  std::string album = to_string(mediaProperties.AlbumArtist());
  int trackNum = mediaProperties.TrackNumber();
  int trackCount = mediaProperties.AlbumTrackCount();
  std::cout << title << std::endl;
  std::cout << subtitle << std::endl;
  std::cout << artist << std::endl;
  std::cout << album << std::endl;
  std::cout << trackNum << std::endl;
  std::cout << trackCount << std::endl;
  std::cout << rate << std::endl;
  if (fillImage) {
    auto asyncStream = mediaProperties.Thumbnail().OpenReadAsync();
    std::cout << "1" << std::endl;
    IRandomAccessStreamWithContentType stream = asyncStream.get();
    std::cout << "2" << std::endl;
    Uri* uri = new Uri( L"Test" );
    std::cout << "3" << std::endl;
    std::cout << "4" << std::endl;
    std::cout << "5" << std::endl;
  }

  return 4;
}

#endif
