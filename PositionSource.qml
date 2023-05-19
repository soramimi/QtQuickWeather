import QtPositioning 5.15

PositionSource {
	id: positionSource
	active: true

	onPositionChanged: {
		var coordinate = positionSource.position.coordinate;
		console.log("Latitude:  " + coordinate.Latitude)
		console.log("Longitude: " + coordinate.Longitude)
	}
}
