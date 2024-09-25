package us.itshighnoon.nowplaying;

public class NowPlaying {
  static {
    System.loadLibrary("nowplaying-natives");
  }
  
  public static native int get(boolean fillImage);
}
