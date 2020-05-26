import "." as Widgets
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Widgets.Pane {
    id: registration
    title: qsTr("Registration")

    Repeater {
        id: repeater
        model: 1
        TextField {
            Layout.alignment: Qt.AlignHCenter
        }
    }

    Button {
        id: button
        Layout.alignment: Qt.AlignHCenter
        text: qsTr("Add")
        onClicked: repeater.model++
    }
}
