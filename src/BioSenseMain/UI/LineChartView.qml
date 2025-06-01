import QtQuick
import QtCharts

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
        useOpenGL: true
        axisX: x
        axisY: y
        visible: true
    }

    function updateSeries()
    {
        lineSeries.clear();
        var maxXValue = initialXAxisMax;
        var maxYValue = initialYAxisMax;
        for (var i = 0; i < dataInput.chartData.length; ++i)
        {
            var pt = dataInput.chartData[i];
            var currentX = Number(pt.x);
            var currentY = Number(pt.y);         
            lineSeries.append(pt.x, pt.y);

            if (currentX > maxXValue) 
            {
                maxXValue = currentX;
            }
            if (currentY > maxYValue) 
            {
                maxYValue = currentY;
            }
        }
        x.max = maxXValue * 1.05;
        y.max = maxYValue * 1.05;
    }

    Component.onCompleted: updateSeries()

    Connections
    {
        target: dataInput
        function onChartDataChanged() { chartView.updateSeries(); }
    }
}