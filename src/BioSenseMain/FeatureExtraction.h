#ifndef FEATUREEXTRACTION_H
#define FEATUREEXTRACTION_H

#include <QObject>
#include <QVector>
#include <QMap>
#include <QString>

namespace Bio
{
    // 特征提取助手类
    class FeatureExtraction : public QObject
    {
        //Q_OBJECT
    public:
        // 特征类型枚举，表示不同的特征提取方式
        enum FeatureType
        {
            Amplitude,      // 幅值特征
            Frequency,      // 频域特征
            TimeDomain,     // 时域特征
            Statistical,    // 统计特征
            Entropy,        // 熵特征
            HeartRate       // 心率分析
        };

        explicit FeatureExtraction(QObject *parent = nullptr);
        virtual ~FeatureExtraction();

        void setFeatureType(FeatureType type);
        QMap<QString, double> extractFeatures(const QVector<double> &signal);

    private:
        FeatureType m_featureType;

        // 新增：心率分析相关静态参数和方法声明
        static constexpr double SAMPLE_RATE = 250.0;
    };
} // namespace Bio

#endif // FEATUREEXTRACTION_H
