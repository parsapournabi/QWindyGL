import QtQuick 2.12
import QtQuick.Layouts 1.12

Rectangle {
    id: root

    property alias title: title

    clip: true
    color: "#222"
    radius: 10

    ColumnLayout {
        anchors {
            fill: parent
            margins: 5
            topMargin: 15
            bottomMargin: 15
        }
        spacing: 25

        CusLabel {
            id: title
            Layout.fillWidth: true

            text: "ControlPanel"
            font.pixelSize: 15
        }

        // Spacer
        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }
}
