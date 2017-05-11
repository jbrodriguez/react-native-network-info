'use strict';

const { NativeModules } = require('react-native');
const { RNNetworkInfo } = NativeModules;

const NetworkInfo = {
  getSSID(ssid) {
    RNNetworkInfo.getSSID(ssid);
  },

  getBSSID(bssid) {
    RNNetworkInfo.getBSSID(bssid);
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
}

module.exports = { NetworkInfo }
