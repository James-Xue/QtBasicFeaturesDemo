import QtQuick
import QtCharts

ChartView
{
    id: chartView
    anchors.left: parent.left
    anchors.right: parent.right
    height: 300
    antialiasing: true

    LineSeries
    {
        id: lineSeries
        name: "CSV数据"
        useOpenGL: true
    }

    function updateSeries()
    {
        lineSeries.clear();
        for (var i = 0; i < dataInput.chartData.length; ++i)
        {
            var pt = dataInput.chartData[i];
            lineSeries.append(pt.x, pt.y);
        }
    }

    Component.onCompleted: updateSeries()

    Connections
    {
        target: dataInput
        function onChartDataChanged() { chartView.updateSeries(); }
    }
}