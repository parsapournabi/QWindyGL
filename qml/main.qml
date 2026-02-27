import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    x: 0
    y: 0
    width: 1000
    height: 635
    visible: true
    title: qsTr("Hello Windy")

    property string mainWindowPath: "MainWindow.qml"

    Component {
        id: mainWindowComp
        MainWindow {}
    }

    Loader {
        id: appLoader
        anchors.fill: parent
        sourceComponent: mainWindowComp
    }

    Shortcut {
        sequence: '`'
        onActivated: appReload()
    }

    function appReload() {
        appLoader.sourceComponent = undefined
        _qmlEngine.clearCache()
        appLoader.sourceComponent = Qt.createComponent(mainWindowPath)
    }
}
