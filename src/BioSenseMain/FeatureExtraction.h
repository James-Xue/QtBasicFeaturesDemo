#ifndef FEATUREEXTRACTIONMODULE_H
#define FEATUREEXTRACTIONMODULE_H

#include <QObject>
#include <QVector>
#include <QMap>
#include <QString>

namespace Bio
{
    // 特征提取助手类
    class FeatureExtractionModule : public QObject
    {
        //Q_OBJECT
    public:
        enum FeatureType
        {
            Amplitude,
            Frequency,
            TimeDomain,
            Statistical,
            Entropy
        };

        explicit FeatureExtractionModule(QObject *parent = nullptr);
        virtual ~FeatureExtractionModule();

        void setFeatureType(FeatureType type);
        QMap<QString, double> extractFeatures(const QVector<double> &signal);

    //signals:
    //    void featuresExtracted(const QMap<QString, double> &features);
    //    void featureExtractionFailed(const QString &errorMsg);

    private:
        FeatureType m_featureType;
        //QMap<QString, double> calculateTimeDomainFeatures(const QVector<double> &signal);
        //QMap<QString, double> calculateFrequencyDomainFeatures(const QVector<double> &signal);
    };
} // namespace Bio

#endif // FEATUREEXTRACTIONMODULE_H    