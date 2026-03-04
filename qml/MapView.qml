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

        // updating projection Imperative (Declerative doesn't support in this case).
        onZoomLevelChanged: projection.updateProject()
        onCenterChanged: projection.updateProject()

        function getPositionRect() {
            return QtPositioning.rectangle(map.toCoordinate(Qt.point(0, 0)),
                                           map.toCoordinate(Qt.point(width,
                                                                     height)))
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
            georect = map.getPositionRect()
        }
    }
}
