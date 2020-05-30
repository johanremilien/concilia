import "." as Widgets
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Widgets.Pane {
    id: registration

    readonly property size profileSize: "200 x 40" //"width x height"

    title: qsTr("Registration")

    RowLayout {
        Layout.alignment: Qt.AlignHCenter
        Text {
            font { pointSize: 20; underline: true }
            text: qsTr("Number of participants:")
        }
        TextInput {
            id: profileNumber
            font { pointSize: 20}
            text: repeater.count
            inputMethodHints: Qt.ImhDigitsOnly
            validator: IntValidator{bottom: 0; top: 99}
            onEditingFinished: repeater.model = parseInt(text) //dummy -> loop add new profile
        }
    }

    GridLayout {
        id: profileLayout
        rows: Math.round(height / (profileSize.height + columnSpacing))
        columns: Math.round(width / (profileSize.width + rowSpacing))
        Layout.fillHeight: true
        Layout.preferredWidth: registration.width
        Component.onCompleted: console.log(columns, rows)
        onWidthChanged: console.log(width)

        Repeater {
            id: repeater
            model: 0
            onItemAdded: item.focus = true
            TextField {
                id: profile
                Layout.alignment: Qt.AlignHCenter
                height: profileSize.height
                width: profileSize.width
                onEditingFinished: focus = false
                onPressAndHold: repeater.model--// dummy -> remove current item
            }
        }
    }

    Button {
        id: button
        Layout.alignment: Qt.AlignHCenter
        text: qsTr("Add")
        onClicked: repeater.model++ //dummy -> add new item
    }
}
