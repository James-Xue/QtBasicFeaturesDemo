import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Rectangle
{
    color: "transparent"
    anchors.fill: parent

    Column
    {
        anchors.centerIn: parent
        spacing: 30

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
                height: 36 // 设置高度与按钮一致
                verticalAlignment: Text.AlignVCenter // 垂直居中内容
            }

            TextField
            {
                id: filePathInput
                width: 260
                height: 36 // 设置高度与按钮一致
                placeholderText: "文件路径"
                color: "#006064" // 输入内容字体颜色
                placeholderTextColor: "#6699bb" // 占位符字体颜色
                verticalAlignment: TextInput.AlignVCenter // 垂直居中内容
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
                height: 36 // 与输入框高度一致
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
                    // 这里可以添加导入文件的逻辑
                    console.log("导入文件路径:", filePathInput.text)
                    dataInput.ImportFile(filePathInput.text)
                }
            }
        }
    }
}