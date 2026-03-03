import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12

Item {
    id: root

    property bool mirror: false

    property alias text: labelItem.text

    property alias model: comboBoxItem.model
    property alias currentIndex: comboBoxItem.currentIndex
    property alias currentValue: comboBoxItem.currentValue
    property alias currentText: comboBoxItem.currentText

    property alias label: labelItem
    property alias comboBox: comboBoxItem

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

            text: "ComboBox : "
            font.pixelSize: 13

            horizontalAlignment: Qt.AlignLeft
            verticalAlignment: Qt.AlignVCenter
        }

        ComboBox {
            id: comboBoxItem
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredWidth: 50

            font.pixelSize: 12
        }
    }
}
