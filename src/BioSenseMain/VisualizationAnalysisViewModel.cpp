#include "VisualizationAnalysisViewModel.h"

namespace Bio
{
    VisualizationAnalysisViewModel::VisualizationAnalysisViewModel(QObject *parent)
        : QObject(parent)
    {
    }

    void VisualizationAnalysisViewModel::updateChart()
    {
        //m_chartData = m_model.getChartData();
        emit chartDataChanged();
    }

    QVariant VisualizationAnalysisViewModel::chartData() const
    {
        return m_chartData;
    }
}