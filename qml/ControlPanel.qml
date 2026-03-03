import QtQuick 2.12
import QtQuick.Layouts 1.12
import WindGL 1.0

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
            Layout.preferredHeight: 15

            text: "ControlPanel"
            font.pixelSize: 16
        }

        ComboBoxControl {
            id: cBoxWindData
            Layout.fillWidth: true
            Layout.preferredHeight: 35

            text: "Wind Data:"
            model: _datasetNames
        }

        SwitchControl {
            id: colorRamp
            Layout.fillWidth: true
            Layout.preferredHeight: 15

            text: "colorRamp:"
            checked: true
        }

        SliderControl {
            id: numParticles
            Layout.fillWidth: true
            Layout.preferredHeight: 15

            slider.live: false

            text: "numParticles:"
            to: 589824
            value: 64 * 64
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
            value: 0.71
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

        RangeSliderControl {
            id: windURange
            Layout.fillWidth: true
            Layout.preferredHeight: 15

            text: "wind U Range:"
            from: -100.0
            to: 100.0
            firstValue: -21.32
            secondValue: 26.8
        }

        RangeSliderControl {
            id: windVRange
            Layout.fillWidth: true
            Layout.preferredHeight: 15

            text: "wind V Range:"
            from: -100.0
            to: 100.0
            firstValue: -21.57
            secondValue: 21.42
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
        windMin: Qt.vector2d(windURange.firstValue, windVRange.firstValue)
        windMax: Qt.vector2d(windURange.secondValue, windVRange.secondValue)
        windDataIndex: cBoxWindData.currentIndex
        colorRampActive: colorRamp.checked
    }
}
