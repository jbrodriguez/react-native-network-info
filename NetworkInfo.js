'use strict'

const { NativeModules } = require('react-native')
const { RNNetworkInfo } = NativeModules

const NetworkInfo = {
	getSSID(ssid) {
		RNNetworkInfo.getSSID(ssid)
	},

	getBSSID(bssid) {
		RNNetworkInfo.getBSSID(bssid)
	},

	getIPAddress(ip) {
		RNNetworkInfo.getIPAddress(ip)
	},

	ping(url, timeout, found) {
		RNNetworkInfo.ping(url, timeout, found)
	},

	wake(mac, ip, formattedMac) {
		RNNetworkInfo.wake(mac, ip, formattedMac)
	},
}

module.exports = { NetworkInfo }
