#ifndef VISUALIZATIONANALYSISMODULE_H
#define VISUALIZATIONANALYSISMODULE_H

#include <QObject>
#include <QVector>
#include <QMap>
#include <QString>
#include <QWidget>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

//QT_CHARTS_USE_NAMESPACE
namespace Bio
{
    class VisualizationAnalysisModule : public QObject
    {
        //Q_OBJECT
    public:
        enum VisualizationType
        {
            TimeDomainPlot,
            FrequencyDomainPlot,
            FeatureComparisonPlot,
            StatisticalAnalysisPlot
        };

        explicit VisualizationAnalysisModule(QObject *parent = nullptr);
        virtual ~VisualizationAnalysisModule();

    //    QWidget* createVisualizationWidget(VisualizationType type);
    //    void updateVisualization(VisualizationType type, const QVector<double> &data);
    //    void updateVisualization(VisualizationType type, const QMap<QString, double> &features);

    //signals:
    //    void visualizationUpdated();

    //private:
    //    QChartView* createTimeDomainChart(const QVector<double> &data);
    //    QChartView* createFrequencyDomainChart(const QVector<double> &data);
    //    QChartView* createFeatureComparisonChart(const QMap<QString, double> &features);
    };
} // namespace Bio

#endif // VISUALIZATIONANALYSISMODULE_H    