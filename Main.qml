import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls 2.15
import QtQuick.Dialogs

Window {

    width: 840
    height: 580
    visible: true
    title: qsTr("Hello World")

    property url imageUrl: ""
    property string paperColor: "#FFFFFF"
    property string inkColor: RisoColors.risoColors[0].toString()

    Page {

        anchors.fill: parent

        ColumnLayout {

            anchors.fill: parent

            RowLayout {
                Layout.fillHeight: true
                Layout.fillWidth: true


                Image {
                    id: imageDisplay
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    fillMode: Image.PreserveAspectFit
                    source: yo.outputImage == "" ? imageUrl : "image://renders/output"
                }

                Pane {
                    Layout.fillHeight: true
                    Layout.preferredWidth: 100
                    visible: imageUrl != ""
                    Layout.rightMargin: 20

                    ColumnLayout {
                        Layout.fillHeight: true
                        Layout.fillWidth: true

                        Rectangle {
                            width: 100
                            height: 50
                            color: paperColor

                            border.width: 1
                            border.color: Qt.black

                            MouseArea {
                                anchors.fill: parent

                                onClicked: {
                                    colorDialog.open()
                                }
                            }
                        }
//                        Rectangle {
//                            width: 100
//                            height: 50
//                            color: inkColor

//                            border.width: 1
//                            border.color: Qt.black

//                            MouseArea {
//                                anchors.fill: parent

//                                onClicked: {
//                                    colorDialog.open()
//                                }
//                            }
//                        }

                        GridLayout {
                            columns: 4

                            Repeater {

                                model: RisoColors.risoColors

                                Rectangle {
                                    Layout.fillWidth: true
                                    height: 20
                                    color: modelData.hex

                                    border.width: modelData.hex.toString() === inkColor ? 1 : 0
                                    border.color: "white"
                                    MouseArea {
                                        anchors.fill: parent

                                        onClicked: {
                                            inkColor = modelData.hex.toString()
                                        }
                                    }

                                }
                            }
                        }

                        Button {
                            text: "Run"
                            onClicked: {
                                yo.run(paperColor, inkColor, imageUrl)
                                imageDisplay.source = ""
                                imageDisplay.source = "image://renders/image"
                            }
                        }
                    }

                }

            }

            Button  {
                text: "Ouvrir une image"
                Layout.alignment: Qt.AlignHCenter

                onClicked: {
                    fileDialog.open()
                }

            }
        }
    }


    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        onAccepted: {
            console.log("You chose: " + selectedFile)
            imageUrl = selectedFile
        }
        onRejected: {
            console.log("Canceled")
        }
    }

    ColorDialog {
        id: colorDialog
        title: "Please choose a color"
        onAccepted: {
            paperColor = selectedColor
        }

    }
}
