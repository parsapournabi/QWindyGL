import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    x: 0
    y: 0
    width: 1000
    height: 635
    visible: true
    visibility: Window.FullScreen
    title: qsTr("Hello Windy")
    color: "black"

    property string mainWindowPath: "MainWindow.qml"
    property string splashSource: "SplashScreen.qml"

    Component {
        id: compSplashScreen

        SplashScreen {
            mainFormSource: mainWindowPath
        }
    }

    Loader {
        id: appLoader
        anchors.fill: parent
        sourceComponent: compSplashScreen
        onLoaded: {
            item.start();
        }
    }

    Shortcut {
        sequence: '`'
        onActivated: appReload()
    }

    function appReload() {
        appLoader.sourceComponent = undefined;
        appLoader.source = "";
        _qmlEngine.clearCache();
        appLoader.setSource(splashSource, {
                                mainFormSource: mainWindowPath,
                                noSplashAnimation: false
                            });
    }
}
