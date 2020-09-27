import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.VirtualKeyboard 2.4

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Concilia")

    //minimumHeight: swipeView.implicitHeight
    //minimumWidth: swipeView.implicitWidth

    SwipeView {
        id: swipeView
        width: window.width
        height: window.height
        RegistrationPane { id: registration; title: qsTr("Registration") }
        RecordingPane { id: recording; title: qsTr("Recording") }
        AnalysisPane { id: analysis; title: qsTr("Analysis") }
        ReportPanel { id: report; title: qsTr("Report") }
    }

    InputPanel {
        id: inputPanel
        z: 99
        x: 0
        y: window.height
        width: window.width

        states: State {
            name: "visible"
            when: inputPanel.active
            PropertyChanges { target: inputPanel; y: window.height - inputPanel.height }
            PropertyChanges { target: swipeView; height: window.height - inputPanel.height }
        }

        transitions: Transition {
            from: ""
            to: "visible"
            reversible: true
            ParallelAnimation {
                NumberAnimation {
                    target: inputPanel
                    property: "y"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
                NumberAnimation {
                    target: swipeView
                    property: "height"
                    duration: 250
                    easing.type: Easing.InOutQuad
                }
            }
        }
    }
}
