import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Dialogs

Rectangle
{
    color: "transparent"
    anchors.fill: parent

    FileDialog
    {
        id: fileDialog
        title: "请选择要导入的CSV文件"
        nameFilters: ["CSV 文件 (*.csv)"]
        onAccepted:
        {
            var url = fileDialog.currentFile;
            var localPath = url.toLocalFile ? url.toLocalFile() : url.toString().replace("file:///", "");
            filePathInput.text = localPath;
            dataInput.ImportFile(fileDialog.currentFile);
        }
    }

    Column
    {
        anchors.fill: parent
        spacing: 20

        // 顶部控件
        Column
        {
            spacing: 30
            anchors.left: parent.left
            anchors.right: parent.right

            Label
            {
                text: "数据导入页面"
                font.pixelSize: 28
                color: "#006064"
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }

            Row
            {
                spacing: 10
                anchors.horizontalCenter: parent.horizontalCenter

                Label
                {
                    text: "请选择要导入的文件："
                    font.pixelSize: 18
                    color: "#006064"
                    height: 36
                    verticalAlignment: Text.AlignVCenter
                }

                TextField
                {
                    id: filePathInput
                    width: 260
                    height: 36
                    placeholderText: "文件路径"
                    color: "#006064"
                    placeholderTextColor: "#6699bb"
                    verticalAlignment: TextInput.AlignVCenter
                    background: Rectangle
                    {
                        color: "#daeefd"
                        radius: 6
                        border.color: "#c0def9"
                        border.width: 1
                    }
                }

                Button
                {
                    text: "导入文件"
                    height: 36
                    background: Rectangle
                    {
                        color: "#c0def9"
                        radius: 6
                        border.color: "#d0e9fd"
                        border.width: 1
                    }
                    contentItem: Text
                    {
                        text: "导入文件"
                        color: "#006064"
                        font.pixelSize: 16
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.fill: parent
                    }
                    onClicked:
                    {
                        fileDialog.open()
                    }
                }
            }
        }

        // 下方折线图
        LineChartView
        {
            anchors.left: parent.left
            anchors.right: parent.right
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}