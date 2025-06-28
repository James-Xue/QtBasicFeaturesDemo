import QtQuick 6.9
import QtQuick.Controls 6.9
import QtQuick.Layouts 6.9
import QtQuick.Dialogs 6.9

// 数据导入页面
Rectangle
{
    color: "transparent"      // 背景透明
    anchors.fill: parent      // 填充父项

    // 文件选择对话框
    FileDialog
    {
        id: fileDialog
        title: qsTr("请选择要导入的CSV文件")     // Please select the CSV file to import
        nameFilters: [qsTr("CSV 文件 (*.csv)")] // CSV File (*.csv)

        // 文件选择后回调
        onAccepted:
        {
            var url = fileDialog.currentFile;
            var localPath =
                url.toLocalFile ? url.toLocalFile() : url.toString().replace("file:///", "");
            filePathInput.text = localPath;               // 显示文件路径
            dataInput.ImportFile(fileDialog.currentFile); // 调用C++导入接口
        }
    }

    // 顶部控件区域
    Column
    {
        anchors.fill: parent
        spacing: 20

        // 顶部控件区域（包含标题和文件选择行）
        Column
        {
            spacing: 30
            anchors.left: parent.left
            anchors.right: parent.right

            // 页面标题
            Label
            {
                text: qsTr("数据导入页面") // Data Import Page
                font.pixelSize: 28
                color: "#006064"
                horizontalAlignment: Text.AlignHCenter
                anchors.horizontalCenter: parent.horizontalCenter
            }

            // 文件选择行（包含标签、输入框和按钮）
            Row
            {
                spacing: 10
                anchors.horizontalCenter: parent.horizontalCenter

                // 文件路径标签
                Label
                {
                    text: qsTr("请选择要导入的文件：") // Please select the file to import:
                    font.pixelSize: 18
                    color: "#006064"
                    height: 36
                    verticalAlignment: Text.AlignVCenter
                }

                // 文件路径输入框，显示选中的文件路径
                TextField
                {
                    id: filePathInput
                    width: 380
                    height: 36
                    placeholderText: qsTr("文件路径") // File path
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

                // 导入文件按钮，点击后弹出文件选择对话框
                Button
                {
                    text: qsTr("导入文件") // Import File
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
                        text: qsTr("导入文件") // Import File
                        color: "#006064"
                        font.pixelSize: 16
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.fill: parent
                    }
                    onClicked:
                    {
                        fileDialog.open() // 打开文件选择对话框
                    }
                }
            }
        }

        // 下方折线图区域，显示导入数据的可视化
        LineChartView
        {
            anchors.left: parent.left
            anchors.right: parent.right
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}