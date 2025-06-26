import QtQuick
import QtQuick.Layouts

// 侧边栏组件，包含竖直排列的页签按钮
ColumnLayout
{
    id: verticalTabs

    // 是否折叠侧边栏
    property bool collapsed: false

    // 当前选中的页签索引
    property int currentIndex: 0

    // 页签名称列表，支持多语言
    property var tabList:
    [
        qsTr("数据导入"),        // Data Import
        qsTr("信号预处理"),      // Signal Preprocessing
        qsTr("特征提取"),        // Feature Extraction
        qsTr("可视化分析"),      // Visualization Analysis
        qsTr("状态评估"),        // Status Assessment
        qsTr("数据保存")         // Data Save
    ]

    // 关键：加上 preferredWidth
    Layout.preferredWidth: collapsed ? 40 : 180
    Layout.fillWidth: false        // 关键：不允许横向拉伸
    Layout.fillHeight: true
    spacing: 16

    // 动态生成页签按钮
    Repeater
    {
        model: verticalTabs.tabList
        delegate: TabButton
        {
            // 折叠时不显示文字
            label: verticalTabs.collapsed ? "" : modelData
            // 是否为当前选中
            checked: (verticalTabs.currentIndex === index)
            // 点击切换当前选中页签
            onClicked: verticalTabs.currentIndex = index
            Layout.fillWidth: true
        }
    }
}