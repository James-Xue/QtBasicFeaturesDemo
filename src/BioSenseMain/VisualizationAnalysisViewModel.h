#pragma once
#include <QObject>
#include "VisualizationAnalysisModule.h"

namespace Bio
{
    class VisualizationAnalysisViewModel : public QObject
    {
        Q_OBJECT
        Q_PROPERTY(QVariant chartData READ chartData NOTIFY chartDataChanged)
    public:
        explicit VisualizationAnalysisViewModel(QObject *parent = nullptr);

        Q_INVOKABLE void updateChart();

        QVariant chartData() const;

    signals:
        void chartDataChanged();

    private:
        VisualizationAnalysisModule m_model;
        QVariant m_chartData;
    };
}