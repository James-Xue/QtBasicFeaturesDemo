#include "FeatureExtractionViewModel.h"

namespace Bio
{
    FeatureExtractionViewModel::FeatureExtractionViewModel(QObject *parent)
        : QObject(parent)
    {
    }

    void FeatureExtractionViewModel::extract(const QVector<double>& signal)
    {
        auto features = m_model.extractFeatures(signal);
        m_heartRate = features.value("HeartRate", 0.0);
        m_rPeakCount = features.value("RPeakCount", 0);
        emit featuresChanged();
    }

    double FeatureExtractionViewModel::heartRate() const { return m_heartRate; }
    int FeatureExtractionViewModel::rPeakCount() const { return m_rPeakCount; }
}