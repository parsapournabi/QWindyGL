import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Item {
    id: root

    property bool mirror: false

    property alias text: labelItem.text
    property alias from: rangeSliderItem.from
    property alias to: rangeSliderItem.to
    property alias firstValue: rangeSliderItem.first.value
    property alias secondValue: rangeSliderItem.second.value
    property alias stepSize: rangeSliderItem.stepSize

    property alias first: rangeSliderItem.first
    property alias second: rangeSliderItem.second

    property alias label: labelItem
    property alias rangeSlider: rangeSliderItem

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

            text: "RangeSlider Value : "
            font.pixelSize: 13

            horizontalAlignment: Qt.AlignLeft
            verticalAlignment: Qt.AlignVCenter
        }

        RangeSlider {
            id: rangeSliderItem
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredWidth: 50

            from: 0.0
            to: 1.0
            first.value: 0.25
            second.value: 0.75
            stepSize: 0.0001
        }
    }
}
