import QtQuick 2.12
import QtQuick.Layouts 1.12

Rectangle {
    id: root

    clip: true
    color: "#000"

    RowLayout {
        anchors {
            fill: parent
            margins: 8
        }
        spacing: 8

        ControlPanel {
            id: controlPanel
            Layout.fillHeight: true
            Layout.preferredWidth: 235
        }

        MainPanel {
            id: mainPanel
            Layout.fillHeight: true
            Layout.fillWidth: true

            particleParams: controlPanel.parameters
        }
    }
}
