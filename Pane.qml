import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Pane {
    id: pane
    property string title
    default property alias content: layout.children
    background: Rectangle { color: Qt.rgba(Math.random(), Math.random(), Math.random()) }

    ColumnLayout {
        id: layout
        anchors.fill: parent
        Text {
            Layout.alignment: Qt.AlignTop | Qt.AlignHCenter
            text: title
            color: "white"
            font.pointSize: 35
            style: Text.Outline;
            styleColor: "black"
        }
    }
}
