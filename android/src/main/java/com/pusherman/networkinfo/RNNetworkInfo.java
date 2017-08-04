package com.pusherman.networkinfo;

import android.content.Context;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.util.Log;

import com.facebook.react.bridge.Callback;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import java.net.InetAddress;
import java.net.Inet4Address;
import java.net.UnknownHostException;
import java.net.SocketException;
import java.nio.ByteOrder;
import java.util.Map;
import java.util.Enumeration;
import java.net.NetworkInterface;
import java.lang.Runtime;
import java.lang.InterruptedException;
import java.io.IOException;

import net.mafro.android.wakeonlan.MagicPacket;

public class RNNetworkInfo extends ReactContextBaseJavaModule {
  WifiManager wifi;
  InetAddress inet;

  public static final String TAG = "RNNetworkInfo";

  public RNNetworkInfo(ReactApplicationContext reactContext) {
    super(reactContext);

    wifi = (WifiManager)reactContext.getApplicationContext()
            .getSystemService(Context.WIFI_SERVICE);
  }

  @Override
  public String getName() {
    return TAG;
  }

  @ReactMethod
  public void getSSID(final Callback callback) {
    WifiInfo info = wifi.getConnectionInfo();

    // This value should be wrapped in double quotes, so we need to unwrap it.
    String ssid = info.getSSID();
    if (ssid.startsWith("\"") && ssid.endsWith("\"")) {
      ssid = ssid.substring(1, ssid.length() - 1);
    }

    callback.invoke(ssid);
  }

  @ReactMethod
  public void getBSSID(final Callback callback) {
    callback.invoke(wifi.getConnectionInfo().getBSSID());
  }

  @ReactMethod
  public void getIPAddress(final Callback callback) {
    String ipAddress = null;

    try {
      for (Enumeration<NetworkInterface> en = NetworkInterface.getNetworkInterfaces(); en.hasMoreElements();) {
        NetworkInterface intf = en.nextElement();
        for (Enumeration<InetAddress> enumIpAddr = intf.getInetAddresses(); enumIpAddr.hasMoreElements();) {
          InetAddress inetAddress = enumIpAddr.nextElement();
          if (!inetAddress.isLoopbackAddress()) {
            ipAddress = inetAddress.getHostAddress();
          }
        }
      }
    } catch (Exception ex) {
      Log.e(TAG, ex.toString());
    }

    callback.invoke(ipAddress);
  }

  @ReactMethod
  public void ping(final String url, final Integer timeout, final Callback callback) {
      boolean found = false;

      Runtime runtime = Runtime.getRuntime();
      try
      {

          String command = String.format("/system/bin/ping -c1 -W %d %s", timeout / 1000, url);
          Process  mIpAddrProcess = java.lang.Runtime.getRuntime().exec(command);
          int returnVal = mIpAddrProcess.waitFor();
          found = (returnVal==0);
      }
      catch (InterruptedException ignore)
      {
          ignore.printStackTrace();
          System.out.println(" Exception:"+ignore);
      }
      catch (IOException e)
      {
          e.printStackTrace();
          System.out.println(" Exception:"+e);
      }

      callback.invoke(found);
  }

  @ReactMethod
  public void wake(final String mac, final String ip, final Callback callback) {
    String formattedMac = null;

    try {
      formattedMac = MagicPacket.send(mac, ip);

    } catch(IllegalArgumentException iae) {
      Log.e(TAG, iae.getMessage());
    } catch(Exception e) {
      Log.e(TAG, e.getMessage());
    }

    callback.invoke(formattedMac);
  }
}
