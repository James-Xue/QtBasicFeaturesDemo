import QtQml
import QtQuick.Window
import QtQuick.Controls
import QtQuick.Layouts

Window
{
    id: mainWindow
    width: 800
    height: 600
    visible: true
    title: "BioSense Main Window"
    color: "#dae8f9" // 主背景色 RGB(218,232,249)

    // 顶部区域：大字标题 + 搜索框
    Rectangle
    {
        id: topBarBg
        color: "#daeefd" // 顶部栏背景色 RGB(218,238,253)
        height: 60
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top

        Row
        {
            id: topBar
            spacing: 20
            anchors.fill: parent
            anchors.margins: 20

            Text
            {
                text: "生理评估软件"
                font.pixelSize: 32
                font.bold: true
                color: "#006064"
                anchors.verticalCenter: parent.verticalCenter
            }

            Rectangle
            {
                width: 300
                height: 36
                radius: 6
                color: "#ffffff"
                border.color: "transparent"
                border.width: 0
                anchors.verticalCenter: parent.verticalCenter

                Row
                {
                    anchors.fill: parent
                    spacing: 5

                    Image
                    {
                        source: "qrc:/UI/search_icon.png"
                        width: 20
                        height: 20
                        anchors.verticalCenter: parent.verticalCenter
                        fillMode: Image.PreserveAspectFit
                    }

                    Text
                    {
                        text: "搜索..."
                        color: "#999999"
                        font.pixelSize: 18
                        verticalAlignment: Text.AlignVCenter
                        anchors.verticalCenter: parent.verticalCenter
                    }
                }
            }
        }
    }

    // 主体区域：左侧竖直页签 + 右侧内容
    RowLayout
    {
        anchors.top: topBarBg.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.margins: 20
        spacing: 20

        // 竖直页签
        Column
        {
            id: verticalTabs
            spacing: 16
            Layout.preferredWidth: 180
            Layout.fillHeight: true

            property int currentIndex: 0

            Repeater
            {
                model: [
                    "数据导入",
                    "信号预处理",
                    "特征提取",
                    "可视化分析",
                    "状态评估",
                    "数据保存"
                ]
                delegate: Button
                {
                    text: modelData
                    checkable: true
                    checked: verticalTabs.currentIndex === index
                    onClicked: verticalTabs.currentIndex = index
                    width: parent.width
                    height: 56
                    font.pixelSize: 22
                    background: Rectangle
                    {
                        color: checked ? "#c0def9" : "#d0e9fd" // 选中/未选中颜色已交换
                        radius: 8
                    }
                    contentItem: Text
                    {
                        text: modelData
                        color: checked ? "#006064" : "#006064"
                        font.pixelSize: 22
                        horizontalAlignment: Text.AlignHCenter
                        verticalAlignment: Text.AlignVCenter
                        anchors.fill: parent
                    }
                }
            }
        }

        // 右侧内容区
        Rectangle
        {
            color: "#ffffff"
            radius: 12
            border.color: "#d0e9fd" // 内容区边框
            border.width: 1
            Layout.fillWidth: true
            Layout.fillHeight: true

            StackLayout
            {
                id: stack
                anchors.fill: parent
                currentIndex: verticalTabs.currentIndex

                Loader { source: "DataImportPage.qml" }
                Loader { source: "SignalPreprocessPage.qml" }
                Loader { source: "FeatureExtractPage.qml" }
                Loader { source: "VisualizationPage.qml" }
                Loader { source: "StatusAssessmentPage.qml" }
                Loader { source: "DataSavePage.qml" }
            }
        }
    }

    // 关闭事件
    onClosing:
    {
        console.log("BioSense application is closing")
    }
}
