import QtQuick 2.12

Rectangle {
    id: root

    property ParticlesParams particleParams

    property alias title: title
    default property alias contentItem: contentItem.data

    clip: true
    color: "#333"
    radius: 10

    CusLabel {
        id: title
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            margins: 15
        }
        height: paintedHeight

        font.pixelSize: 16

        text: "%1 %2 %3 %4 %5".arg(particleParams.numParticles).arg(
                  particleParams.fadeOpacity).arg(
                  particleParams.speedFactor).arg(particleParams.dropRate).arg(
                  particleParams.dropRateBump)
    }

    Item {
        id: parentContentItem
        anchors {
            top: title.bottom
            left: parent.left
            right: parent.right
            bottom: parent.bottom
            margins: 15
        }

        Item {
            id: contentItem
            anchors.fill: parent
        }
    }
}
