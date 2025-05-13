#include "FeatureExtraction.h"

namespace Bio
{
    FeatureExtractionModule::FeatureExtractionModule(QObject* /*parent*/ /*= nullptr*/)
    {
    }

    FeatureExtractionModule::~FeatureExtractionModule()
    {
    }

    void FeatureExtractionModule::setFeatureType(FeatureType /*type*/)
    {
    }

    QMap<QString, double> FeatureExtractionModule::extractFeatures(const QVector<double>& /*signal*/)
    {
        return {};
    }
} // namespace Bio
