import QtQuick 6.9
import QtCharts 6.9

// 折线图视图组件，用于显示CSV数据
ChartView
{
    id: chartView
    anchors.left: parent.left
    anchors.right: parent.right
    height: 600                  // 图表高度
    antialiasing: true           // 抗锯齿

    // 初始X轴和Y轴的最大值
    property real initialXAxisMax: 30000 // Initial max for X-axis
    property real initialYAxisMax: 3500  // Initial max for Y-axis
    
    // X轴设置
    ValueAxis 
    {
        id: x
        min: 0
        max: initialXAxisMax
        titleText: "X"
        labelFormat: "%d" 
    }

    // Y轴设置
    ValueAxis 
    {
        id: y
        min: 0
        max: initialYAxisMax
        titleText: "Y"
        labelFormat: "%d"
    }

    // 折线序列，用于显示数据
    LineSeries
    {
        id: lineSeries
        name: "CSV数据"         // 系列名称
        useOpenGL: false        // 是否使用OpenGL加速
        axisX: x                // 绑定X轴
        axisY: y                // 绑定Y轴
        visible: true           // 是否可见
    }

    // 更新折线数据的方法，调用C++接口
    function updateSeries()
    {
        dataInput.setSeriesData(lineSeries, x, y);
    }

    // 组件加载完成时自动更新数据
    Component.onCompleted: updateSeries()

    // 监听C++信号，数据变化时自动刷新
    Connections
    {
        target: dataInput
        function onChartDataChanged() { chartView.updateSeries(); }
    }
}