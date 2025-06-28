import QtQuick 6.9
import QtCharts 6.9

// 折线图视图组件，用于显示 CSV 数据
ChartView
{
    id: chartView
    anchors.left: parent.left
    anchors.right: parent.right
    height: 600                  // 图表高度
    antialiasing: true           // 抗锯齿

    // 初始 X 轴和 Y 轴的最大值
    property real initialXAxisMax: 30000 // Initial max for X-axis
    property real initialYAxisMax: 3500  // Initial max for Y-axis
    
    // X 轴设置
    ValueAxis
    {
        id: x
        min: 0
        max: initialXAxisMax
        titleText: qsTr("时间 (ms)") // X-axis title: Time (ms)
        tickCount: 10               // 刻度数量
        // 设置 X 轴标签格式为整数
        labelFormat: "%d"
    }

    // Y 轴设置
    ValueAxis
    {
        id: y
        min: 0
        max: initialYAxisMax
        titleText: qsTr("信号值") // Y-axis title: Signal Value
        tickCount: 10            // 刻度数量
        // 设置 Y 轴标签格式为整数
        labelFormat: "%d"
    }

    // 折线序列，用于显示数据
    LineSeries
    {
        id: lineSeries
        name: qsTr("CSV 数据") // Series name: CSV Data
        useOpenGL: false      // 是否使用 OpenGL 加速
        axisX: x              // 绑定 X 轴
        axisY: y              // 绑定 Y 轴
        visible: true         // 是否可见
    }

    // 更新折线数据的方法，调用 C++ 接口
    function updateSeries()
    {
        dataInput.setSeriesData(lineSeries, x, y);
    }

    // 组件加载完成时自动更新数据
    Component.onCompleted: updateSeries()

    // 监听 C++ 信号，数据变化时自动刷新
    Connections
    {
        target: dataInput
        function onChartDataChanged() { chartView.updateSeries(); }
    }
}