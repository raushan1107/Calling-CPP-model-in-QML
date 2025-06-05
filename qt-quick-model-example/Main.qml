import QtQuick
Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    ListView {
        width: 500
        height: 300
        model: _myModel
        delegate: Rectangle {
            x: 10
            y: 10
            color: Qt.rgba(0.9,0.9,0.9)
            height: childrenRect.height
            width: 400

            Image {
                id: image
                source: model.flag
                width: 64
                height: 64
                fillMode: Image.PreserveAspectFit

                anchors.left: parent
            }
            Text {
                text: model.name + "\n" +"population: " + model.population.toFixed(3) + " millions."
                anchors { left:image.right; verticalCenter: image.verticalCenter; leftMargin: 5 }
            }
            MouseArea {
                anchors.fill: parent
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                onDoubleClicked: {
                    if (mouse.button === Qt.LeftButton) {
                        _myModel.duplicateData(model.index);
                    } else if (mouse.button === Qt.RightButton) {
                        _myModel.removeData(model.index);
                    }
                }
            }
        }
    }
}
