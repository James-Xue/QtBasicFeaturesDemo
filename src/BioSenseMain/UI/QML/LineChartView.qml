import QtQuick 6.9
import QtCharts 6.9

ChartView
{
    id: chartView
    anchors.left: parent.left
    anchors.right: parent.right
    height: 300
    antialiasing: true

    property real initialXAxisMax: 30000 // Initial max for X-axis
    property real initialYAxisMax: 3500  // Initial max for Y-axis
    
    ValueAxis 
    {
        id: x
        min: 0
        max: initialXAxisMax
        titleText: "X"
        labelFormat: "%d" 
    }

    ValueAxis 
    {
        id: y
        min: 0
        max: initialYAxisMax
        titleText: "Y"
        labelFormat: "%d"
    }

    LineSeries
    {
        id: lineSeries
        name: "CSV数据"
        useOpenGL: false
        axisX: x
        axisY: y
        visible: true
    }

    function updateSeries()
    {
        dataInput.setSeriesData(lineSeries,x,y);
    }

    Component.onCompleted: updateSeries()

    Connections
    {
        target: dataInput
        function onChartDataChanged() { chartView.updateSeries(); }
    }
}