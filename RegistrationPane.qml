import "." as Widgets
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Widgets.Pane {
    id: registration

    readonly property size fieldSize: "200x40" //"width x height"
    property alias meetingEditZone: meetingEditZone

    title: qsTr("Registration")

    RowLayout {
        id: meetingEditZone
        property int meetingID: UNDEFINED_ID
        property alias name: meetingName.text

        Layout.alignment: Qt.AlignHCenter
        TextField {
            id: meetingName
            font { pointSize: 20}
            placeholderText: qsTr("Enter meeting name")
            height: fieldSize.height
            width: fieldSize.width
            onEditingFinished: {
                if (meetingEditZone.meetingID === UNDEFINED_ID)
                    meetingEditZone.meetingID = SpeakingTimeRecorder.createNewMeeting(text)
                else
                    SpeakingTimeRecorder.renameMeeting(meetingEditZone.meetingID, text)
            }
        }
    }

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

    ColumnLayout {
        id: profileLayout
        Layout.fillHeight: true
        Layout.preferredWidth: registration.width

        Repeater {
            id: repeater
            model: 1
            onItemAdded: item.focus = true
            GroupBox {
                id: participantEditZone
                property int participantID: UNDEFINED_ID
                property alias firstName: firstNameField.text
                property alias lastName: lastNameField.text
                RowLayout {
                    anchors.fill: parent
                    TextField {
                        id: firstNameField
                        height: fieldSize.height
                        width: fieldSize.width
                        onEditingFinished: focus = false
                        placeholderText: qsTr("Enter first name")
                    }
                    TextField {
                        id: lastNameField
                        height: fieldSize.height
                        width: fieldSize.width
                        onEditingFinished: focus = false
                        placeholderText: qsTr("Enter last name")
                    }
                    Button {
                        id: validateButton
                        text: qsTr("OK")
                        onClicked: {
                            if (participantEditZone.participantID === UNDEFINED_ID)
                                participantEditZone.participantID = SpeakingTimeRecorder.addParticipant(firstName.text,
                                                                                                        lastName.text)
                            else
                                participantEditZone.participantID = SpeakingTimeRecorder.renameParticipant(participantEditZone.participantID,
                                                                                                           participantEditZone.firstName,
                                                                                                           participantEditZone.lastName);
                        }
                    }
                }
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
