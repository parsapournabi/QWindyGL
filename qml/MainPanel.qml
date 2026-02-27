import QtQuick 2.12

Rectangle {
    id: root

    property ParticlesParams particleParams

    property alias title: title

    clip: true
    color: "#333"
    radius: 10

    CusLabel {
        id: title
        anchors {
            fill: parent
            margins: 15
        }

        font.pixelSize: 16

        text: "%1 %2 %3 %4 %5".arg(particleParams.numParticles).arg(
                  particleParams.fadeOpacity).arg(
                  particleParams.speedFactor).arg(particleParams.dropRate).arg(
                  particleParams.dropRateBump)
    }
}
