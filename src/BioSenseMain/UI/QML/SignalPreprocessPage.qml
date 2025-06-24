import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QtCharts 2.3

Rectangle
{
    color: "transparent"
    anchors.fill: parent

    property bool allChecked: false

    ColumnLayout
    {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        // 顶部：三个复选框，居中排布
        RowLayout
        {
            spacing: 30
            Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter

            Item { Layout.fillWidth: true } // 左侧弹性占位

            CheckBox {
                text: "降噪"
                checked: allChecked
                onCheckedChanged: allChecked = checked
                font.family: "Microsoft YaHei"
                font.pixelSize: 16
                contentItem: Text {
                    text: parent.text
                    color: "black"
                    font.family: "Microsoft YaHei"
                    font.pixelSize: 16
                    verticalAlignment: Text.AlignVCenter
                    leftPadding: parent.indicator.width + parent.spacing
                }
            }
            CheckBox {
                text: "异常值识别"
                checked: allChecked
                onCheckedChanged: allChecked = checked
                font.family: "Microsoft YaHei"
                font.pixelSize: 16
                contentItem: Text {
                    text: parent.text
                    color: "black"
                    font.family: "Microsoft YaHei"
                    font.pixelSize: 16
                    verticalAlignment: Text.AlignVCenter
                    leftPadding: parent.indicator.width + parent.spacing
                }
            }
            CheckBox {
                text: "异常值剔除"
                checked: allChecked
                onCheckedChanged: allChecked = checked
                font.family: "Microsoft YaHei"
                font.pixelSize: 16
                contentItem: Text {
                    text: parent.text
                    color: "black"
                    font.family: "Microsoft YaHei"
                    font.pixelSize: 16
                    verticalAlignment: Text.AlignVCenter
                    leftPadding: parent.indicator.width + parent.spacing
                }
            }

            Item { Layout.fillWidth: true } // 右侧弹性占位
        }

        // 折线图区域（按钮在上，图在下）
        Rectangle {
            color: "transparent"
            Layout.fillWidth: true
            Layout.fillHeight: true

            ColumnLayout {
                anchors.fill: parent
                spacing: 10

                // 按钮行
                RowLayout {
                    spacing: 30
                    Layout.alignment: Qt.AlignHCenter   // 居中对齐

                    Button {
                        text: "信号预处理"
                        height: 40
                        font.family: "Microsoft YaHei"
                        font.pixelSize: 16
                        contentItem: Text {
                            text: parent.text
                            color: "#006064"
                            font.family: "Microsoft YaHei"
                            font.pixelSize: 16
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            anchors.fill: parent
                        }
                        background: Rectangle {
                            color: "#c0def9"
                            radius: 6
                            border.color: "#d0e9fd"
                            border.width: 1
                        }
                    }

                    Button {
                        text: "保存处理后文件"
                        height: 40
                        font.family: "Microsoft YaHei"
                        font.pixelSize: 16
                        contentItem: Text {
                            text: parent.text
                            color: "#006064"
                            font.family: "Microsoft YaHei"
                            font.pixelSize: 16
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            anchors.fill: parent
                        }
                        background: Rectangle {
                            color: "#c0def9"
                            radius: 6
                            border.color: "#d0e9fd"
                            border.width: 1
                        }
                    }
                }

                // 折线图
                LineChartView {
                    Layout.fillWidth: true
                    Layout.fillHeight: true
                    Layout.minimumHeight: 300
                }
            }
        }
    }
}