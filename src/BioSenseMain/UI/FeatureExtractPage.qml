import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

Rectangle
{
    color: "transparent"
    anchors.fill: parent

    ColumnLayout
    {
        anchors.fill: parent
        anchors.margins: 30
        spacing: 30

        // 方法选择区
        RowLayout
        {
            spacing: 20
            Layout.alignment: Qt.AlignLeft

            Label {
                text: "方法:"
                font.pixelSize: 20
                color: "#006064"
                Layout.alignment: Qt.AlignVCenter
            }
            CheckBox {
                text: "统计域"
                font.pixelSize: 16
                Layout.alignment: Qt.AlignVCenter
                contentItem: Text {
                    text: parent.text
                    color: "black"
                    font.pixelSize: 16
                    verticalAlignment: Text.AlignVCenter
                    leftPadding: parent.indicator.width + parent.spacing
                }
            }
            CheckBox {
                text: "频谱"
                font.pixelSize: 16
                Layout.alignment: Qt.AlignVCenter
                contentItem: Text {
                    text: parent.text
                    color: "black"
                    font.pixelSize: 16
                    verticalAlignment: Text.AlignVCenter
                    leftPadding: parent.indicator.width + parent.spacing
                }
            }
            CheckBox {
                text: "图拉姆角场"
                font.pixelSize: 16
                Layout.alignment: Qt.AlignVCenter
                contentItem: Text {
                    text: parent.text
                    color: "black"
                    font.pixelSize: 16
                    verticalAlignment: Text.AlignVCenter
                    leftPadding: parent.indicator.width + parent.spacing
                }
            }
        }

        // 特征参量区
        Label {
            text: "特征参量"
            font.pixelSize: 18
            color: "#006064"
            Layout.alignment: Qt.AlignLeft
        }

        RowLayout
        {
            spacing: 30
            Layout.fillWidth: true
            Layout.fillHeight: true

            // 4x3复选框的大框
            Rectangle {
                color: "#f5fafd"
                border.color: "#c0def9"
                border.width: 1
                radius: 10
                Layout.fillWidth: true
                Layout.fillHeight: true
                Layout.preferredWidth: 400
                Layout.preferredHeight: 300

                GridLayout {
                    anchors.fill: parent
                    anchors.margins: 20
                    columns: 3
                    rowSpacing: 20
                    columnSpacing: 30

                    Repeater {
                        model: 12
                        CheckBox {
                            text: "参量" + (index + 1)
                            font.pixelSize: 16
                            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                            contentItem: Text {
                                text: parent.text
                                color: "black"
                                font.pixelSize: 16
                                verticalAlignment: Text.AlignVCenter
                                leftPadding: parent.indicator.width + parent.spacing
                            }
                        }
                    }
                }
            }

            // 右侧按钮区
            ColumnLayout {
                spacing: 30
                Layout.alignment: Qt.AlignVCenter

                Button {
                    text: "提取特征"
                    font.pixelSize: 16
                    width: 120
                    height: 40
                    background: Rectangle {
                        color: "#c0def9"
                        radius: 6
                        border.color: "#d0e9fd"
                        border.width: 1
                    }
                    contentItem: Text {
                        text: parent.text
                        color: "#006064"
                        font.pixelSize: 16
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.fill: parent
                    }
                }

                Button {
                    text: "保存特征文件"
                    font.pixelSize: 16
                    width: 120
                    height: 40
                    background: Rectangle {
                        color: "#c0def9"
                        radius: 6
                        border.color: "#d0e9fd"
                        border.width: 1
                    }
                    contentItem: Text {
                        text: parent.text
                        color: "#006064"
                        font.pixelSize: 16
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.fill: parent
                    }
                }
            }
        }
    }
}