'use strict';

var RNNetworkInfo = require('react-native').NativeModules.RNNetworkInfo;

var NetworkInfo = {
  getSSID(ssid) {
    RNNetworkInfo.getSSID(ssid);
  },

  getIPAddress(ip) {
    RNNetworkInfo.getIPAddress(ip);
  },

  ping(url, found) {
  	RNNetworkInfo.ping(url, found);
  },

  wake(mac, ip, formattedMac) {
  	RNNetworkInfo.wake(mac, ip, formattedMac)
  }  
};

module.exports = NetworkInfo;
