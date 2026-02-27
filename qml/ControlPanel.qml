import QtQuick 2.12
import QtQuick.Layouts 1.12

Rectangle {
    id: root

    property alias title: title

    readonly property alias parameters: parameters

    clip: true
    color: "#222"
    radius: 10

    ColumnLayout {
        anchors {
            fill: parent
            margins: 10
            topMargin: 15
            bottomMargin: 15
        }
        spacing: 25

        CusLabel {
            id: title
            Layout.fillWidth: true

            text: "ControlPanel"
            font.pixelSize: 16
        }

        SliderControl {
            id: numParticles
            Layout.fillWidth: true
            Layout.preferredHeight: 15

            text: "numParticles:"
            to: 589824
            value: 65536
            stepSize: 1
        }

        SliderControl {
            id: fadeOpacity
            Layout.fillWidth: true
            Layout.preferredHeight: 15

            text: "fadeOpacity:"
            value: 0.996
        }

        SliderControl {
            id: speedFactor
            Layout.fillWidth: true
            Layout.preferredHeight: 15

            text: "speedFactor:"
        }

        SliderControl {
            id: dropRate
            Layout.fillWidth: true
            Layout.preferredHeight: 15

            text: "dropRate:"
            to: 0.1
            value: 0.003
        }

        SliderControl {
            id: dropRateBump
            Layout.fillWidth: true
            Layout.preferredHeight: 15

            text: "dropRateBump:"
            to: 0.2
            value: 0.01
        }

        // Spacer
        Item {
            Layout.fillHeight: true
            Layout.fillWidth: true
        }
    }

    ParticlesParams {
        id: parameters

        numParticles: numParticles.value
        fadeOpacity: fadeOpacity.value
        speedFactor: speedFactor.value
        dropRate: dropRate.value
        dropRateBump: dropRateBump.value
    }
}
