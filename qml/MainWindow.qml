import QtQuick 2.12
import QtQuick.Layouts 1.12
import WindGL 1.0

Rectangle {
    id: root

    clip: true
    color: "#000"

    ColumnLayout {
        anchors {
            fill: parent
            margins: 9
            bottomMargin: 5
        }
        spacing: 8

        RowLayout {
            Layout.fillWidth: true
            Layout.fillHeight: true
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
                contentItem: WindGLFbo {
                    id: windGLFbo
                    anchors.fill: parent

                    particlesParams: controlPanel.parameters
                }
            }
        }

        Footer {
            id: footer

            Layout.fillWidth: true
            Layout.preferredHeight: paintedHeight

            text: qsTr(" Developed by wearily on February, 27, 2026 ")
        }
    }
}
