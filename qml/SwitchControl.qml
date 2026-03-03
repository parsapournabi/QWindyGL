import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Item {
    id: root

    property bool mirror: false

    property alias text: labelItem.text
    property alias checked: switchItem.checked

    property alias label: labelItem
    property alias checkBox: switchItem

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

            text: "Switch: "
            font.pixelSize: 13

            horizontalAlignment: Qt.AlignLeft
            verticalAlignment: Qt.AlignBottom
        }

        Switch {
            id: switchItem
            Layout.fillHeight: true
            Layout.preferredWidth: 50
        }
    }
}
