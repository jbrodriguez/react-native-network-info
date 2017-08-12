'use strict'

import { NativeModules } from 'react-native'
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

	getIPV4Address(ip) {
		RNNetworkInfo.getIPV4Address(ip)
	},

	ping(url, timeout, found) {
		RNNetworkInfo.ping(url, timeout, found)
	},

	wake(mac, ip, formattedMac) {
		RNNetworkInfo.wake(mac, ip, formattedMac)
	},
}

module.exports = { NetworkInfo }
