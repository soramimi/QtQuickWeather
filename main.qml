import QtQuick 2.15
import QtQuick.Controls 2.15
import QtPositioning 5.15
import com.example.weather 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480

	property int ser: 0

	Text {
		id: text1
		x: 20
		y: 20
	}

	Text {
		id: text2
		x: 20
		y: 50
	}

	Text {
		id: text3
		x: 20
		y: 80
	}

	Text {
		id: text4
		x: 20
		y: 110
	}

	function updateWeather(city, temp, humi, pres) {
		temp = Math.floor(temp * 10 + 0.5) / 10
		console.log("City:        " + city)
		console.log("Temperature: " + temp);
		console.log("Humidity:    " + humi);
		console.log("Pressure:    " + pres);
		text1.text = city
		text2.text = "" + temp
		text3.text = "" + humi
		text4.text = "" + pres
	}

	function requestWeatherData1() {
		ser++;
		var xhr = new XMLHttpRequest();
		var appid = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"
		var url = "http://api.openweathermap.org/data/2.5/weather?zip=227-0062,JP&appid=" + appid + "&mode=json&_dummy_=" + ser
		xhr.open("GET", url, true);
		xhr.onreadystatechange = function () {
			if (xhr.readyState === XMLHttpRequest.DONE) {
				if (xhr.status === 200) {
					var response = JSON.parse(xhr.responseText);
					updateWeather(response.name, response.main.temp - 273, response.main.humidity, response.main.pressure)
				} else {
					console.log("HTTP request failed. Status: " + xhr.status);
				}
			}
		}
		xhr.send();
	}

	WeatherData {
		id: weatherData
		onDataChanged: {
			updateWeather(weatherData.cityName, weatherData.temperature - 273, weatherData.humidity, weatherData.pressure)
		}
	}

	function requestWeatherData2() {
		weatherData.updateWeatherData()
	}

	Timer {
		interval: 10000
		running: true
		repeat: true
		triggeredOnStart: true
		onTriggered: {
//			requestWeatherData1()
			requestWeatherData2()
		}
	}
}
