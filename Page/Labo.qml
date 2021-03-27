/*
logger
5f7f439ec0bc4a7d736a9277
f2d3029c7d53310cc820612318081d97be9f8596f2d43f1c1304f1781086adaf
*/


import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.15
import Controls 1.0
import IMT.IoTLabsWS 1.0
// Styling imports
import QtQuick.Controls.Material 2.12


Item {
	id: rootItem

	// Material.theme: Material.Dark
	// Material.accent: Material.Orange
	// Material.background: Material.Red
	// Material.primary: Material.Red
	// Material.primary: Material.Dark
	Material.foreground: Material.Grey


	IoTLabsWS {
		id: client
		host: "wss://imt-iotlabs.net"
		// host: "ws://192.168.0.9"
		appID: "60594c0039b8130447cd841f"
		apiKey: "5bd87b923ccd0389449092cb980cb49f7ba75f5a2597f4969555e4784363986a"
	
		Component.onCompleted: {
			connectServer()
		}
	
		onConnectionEstablished: {
			console.log("Connection established")
		}
	
		onCredentialsRejected: {
			console.log("Provided credentials were rejected by the server")
		}
	
		onMessageRecieved: {
			let parsedMessage = JSON.parse(message)
			let topic = parsedMessage.topic;
			let payload = parsedMessage.message;

			console.log(`topic: ${topic}`)
			console.log(`payload: ${payload}`)
		}
	}

	Joystick {
		id: joystick
		// width: parent.height > parent.width? parent.width / 2 : parent.height / 2
		// height: parent.height > parent.width? parent.width / 2 : parent.height / 2
		width: 350
		height: 350

		anchors.centerIn: parent

		// get current position every 13.33[ms] or 10[Hz]
		pollingRate: 1000
		// pollingRate: 1000

		onPositionReleased: {
			console.log(`out: (${joyX}, ${joyY})`)
			client.publish("iotlabs/lab1/joystick_X", joyX);
			client.publish("iotlabs/lab1/joystick_Y", joyY);
			// ball.x += joyX
			// ball.y += joyY
		}
	}


	// Rectangle {
	// 	id: ball
	// 	width: 50
	// 	height: 50
	// 	radius: 25

	// 	x: 100
	// 	y: 100

	// 	color: 'red'

	// }
}