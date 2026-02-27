import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Item {
    id: root

    property bool mirror: false

    property alias text: labelItem.text
    property alias from: sliderItem.from
    property alias to: sliderItem.to
    property alias value: sliderItem.value
    property alias stepSize: sliderItem.stepSize

    property alias label: labelItem
    property alias slider: sliderItem

    RowLayout {
        anchors {
            fill: parent
        }
        spacing: 5
        layoutDirection: root.mirror ? Qt.RightToLeft : Qt.LeftToRight

        CusLabel {
            id: labelItem
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredWidth: 50

            text: "Slider Value : "
            font.pixelSize: 13

            horizontalAlignment: Qt.AlignLeft
            verticalAlignment: Qt.AlignVCenter
        }

        Slider {
            id: sliderItem
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredWidth: 50

            from: 0.0
            to: 1.0
            value: 0.25
            stepSize: 0.0001
        }
    }
}
