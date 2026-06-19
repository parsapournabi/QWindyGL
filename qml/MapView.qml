import QtQuick 2.0
import QtLocation 5.6
import QtPositioning 5.6

Item {
    id: root

    property alias zoomLevel: map.zoomLevel
    property alias center: map.center

    /** Projection Properties **/
    readonly property alias projection: projection

    default property alias contentItem: contentItem.data

    Plugin {
        id: mapPlugin
        name: "osm" // "mapboxgl", "esri", ...
    }

    Map {
        id: map
        anchors.fill: parent
        plugin: mapPlugin
        minimumZoomLevel: 3

        center: QtPositioning.coordinate(0.0, 0.0)
        zoomLevel: 3

        // MapItem
        Item {
            id: contentItem
            anchors.fill: parent
        }

        QtObject {
            id: privateMap

            // false -> leftToRight, true -> rightToLeft
            property bool panDirection: false

            property bool isManualCenterEvent: false
        }

        // updating projection Imperative (Declerative doesn't support in this case).
        onZoomLevelChanged: {
            updateLimits();
            projection.updateProject();
        }
        onCenterChanged: {
            if (privateMap.isManualCenterEvent) {
                projection.updateProject();
                privateMap.isManualCenterEvent = false;
            } else {
                privateMap.isManualCenterEvent = true;
                updateLimits();
            }
        }

        function updateLimits() {
            const minLonLimit = -180.0 + 1e-06;
            const maxLonLimit = 180 - 1e-06;
            const georect = getPositionRect();

            const minLon = georect.topLeft.longitude;
            const maxLon = georect.bottomRight.longitude;
            const minLat = georect.bottomRight.latitude;
            const maxLat = georect.topLeft.latitude;

            // console.log("onCenterChanged: ", privateMap.isManualCenterEvent, map.center.longitude, minLon, maxLon, (
            //                 maxLon + minLon) / 2);

            if (minLon > maxLon)

                // // left direction should block
                // const point = map.fromCoordinate(QtPositioning.coordinate(
                //                                      0.0, minLonLimit))
                // const point1 = map.fromCoordinate(QtPositioning.coordinate(
                //                                       0.0, maxLonLimit))
                // console.warn("Left Block: ", point.x, point1.x)
                // // pan(point.x, 0)
            {}

            var center = map.center;

            var lon = center.longitude;
            var lat = center.latitude;

            // Clamp
            lon = Math.min(110, Math.max(-110, lon));

            center.longitude = lon;

            map.center = center;
        }

        function getPositionRect() {
            return QtPositioning.rectangle(map.toCoordinate(Qt.point(0, 0)), map.toCoordinate(Qt.point(width, height)));
        }

        function pan(dx, dy) {
            var centerPoint = Qt.point(width / 2 + dx, height / 2 + dy);
            var centerGeo = map.toCoordinate(centerPoint, false);
            console.log("Center Point: ", centerPoint);
            map.center = centerGeo;
        }
    }

    QtObject {
        id: projection
        readonly property double left: georect.topLeft.longitude
        readonly property double right: georect.bottomRight.longitude
        readonly property double bottom: georect.bottomRight.latitude
        readonly property double top: georect.topLeft.latitude

        property variant georect: map.getPositionRect()

        function updateProject() {
            georect = map.getPositionRect();
        }
    }
}
