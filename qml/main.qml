import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    width: 640
    height: 480
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
