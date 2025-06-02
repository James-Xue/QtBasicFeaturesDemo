#include "FeatureExtractionModule.h"
#include <QtMath>
#include <algorithm>
#include <numeric>

namespace Bio
{
    static constexpr double SAMPLE_RATE = 250.0; // Hz

    FeatureExtractionModule::FeatureExtractionModule(QObject* /*parent*/)
    {
    }

    FeatureExtractionModule::~FeatureExtractionModule()
    {
    }

    void FeatureExtractionModule::setFeatureType(FeatureType type)
    {
        m_featureType = type;
    }

    QMap<QString, double> FeatureExtractionModule::extractFeatures(const QVector<double>& signal)
    {
        QMap<QString, double> features;

        if (signal.isEmpty())
            return features;

        switch (m_featureType)
        {
        case Amplitude:
        {
            // 幅值特征：最大值、最小值、峰峰值
            double maxVal = *std::max_element(signal.begin(), signal.end());
            double minVal = *std::min_element(signal.begin(), signal.end());
            features["Max"] = maxVal;
            features["Min"] = minVal;
            features["PeakToPeak"] = maxVal - minVal;
            break;
        }
        case Frequency:
        {
            // 频域特征：简单能量谱（这里只做总能量，实际可用FFT等）
            double energy = 0.0;
            for (double v : signal)
            {
                energy += v * v;
            }
            features["Energy"] = energy;
            // 实际频谱分析建议用FFT，这里仅作占位
            break;
        }
        case TimeDomain:
        {
            // 时域特征：均值、方差
            double mean = std::accumulate(signal.begin(), signal.end(), 0.0) / signal.size();
            double var = 0.0;
            for (double v : signal)
            {
                var += (v - mean) * (v - mean);
            }
            var /= signal.size();
            features["Mean"] = mean;
            features["Variance"] = var;
            break;
        }
        case Statistical:
        {
            // 统计特征：偏度、峰度
            double mean = std::accumulate(signal.begin(), signal.end(), 0.0) / signal.size();
            double m2 = 0.0, m3 = 0.0, m4 = 0.0;
            for (double v : signal)
            {
                double d = v - mean;
                m2 += d * d;
                m3 += d * d * d;
                m4 += d * d * d * d;
            }
            m2 /= signal.size();
            m3 /= signal.size();
            m4 /= signal.size();
            double skewness = m3 / qPow(m2, 1.5);
            double kurtosis = m4 / (m2 * m2);
            features["Skewness"] = skewness;
            features["Kurtosis"] = kurtosis;
            break;
        }
        case Entropy:
        {
            // 熵特征：Shannon entropy（简单实现）
            double minVal = *std::min_element(signal.begin(), signal.end());
            double maxVal = *std::max_element(signal.begin(), signal.end());
            int bins = 20;
            QVector<int> hist(bins, 0);
            for (double v : signal)
            {
                int idx = int((v - minVal) / (maxVal - minVal + 1e-8) * (bins - 1));
                hist[idx]++;
            }
            double entropy = 0.0;
            for (int h : hist)
            {
                if (h > 0)
                {
                    double p = double(h) / signal.size();
                    entropy -= p * std::log2(p);
                }
            }
            features["ShannonEntropy"] = entropy;
            break;
        }
        case HeartRate:
        {
            // 心率分析
            // 1. 简单高通滤波（去除基线漂移）
            QVector<double> filtered(signal.size());
            filtered[0] = signal[0];
            double alpha = 0.95;
            for (int i = 1; i < signal.size(); ++i)
            {
                filtered[i] = alpha * (filtered[i - 1] + signal[i] - signal[i - 1]);
            }

            // 2. 简单R波检测（阈值法）
            double mean = 0, stddev = 0;
            for (double v : filtered)
            {
                mean += v;
            }
            mean /= filtered.size();
            for (double v : filtered)
            {
                stddev += (v - mean) * (v - mean);
            }
            stddev = qSqrt(stddev / filtered.size());
            double threshold = mean + stddev * 1.0;

            QVector<int> rPeaks;
            int minDistance = int(0.25 * SAMPLE_RATE);

            for (int i = 1; i < filtered.size() - 1; ++i)
            {
                if (filtered[i] > threshold && filtered[i] > filtered[i - 1] && filtered[i] > filtered[i + 1])
                {
                    if (rPeaks.isEmpty() || (i - rPeaks.last() > minDistance))
                    {
                        rPeaks.append(i);
                    }
                }
            }

            // 3. 计算心率
            if (rPeaks.size() > 1)
            {
                QVector<double> rrIntervals;
                for (int i = 1; i < rPeaks.size(); ++i)
                {
                    rrIntervals.append((rPeaks[i] - rPeaks[i - 1]) / SAMPLE_RATE);
                }

                double avgRR = std::accumulate(rrIntervals.begin(), rrIntervals.end(), 0.0) / rrIntervals.size();
                double heartRate = 60.0 / avgRR;

                features["HeartRate"] = heartRate;
                features["RPeakCount"] = rPeaks.size();
            }
            else
            {
                features["HeartRate"] = 0.0;
                features["RPeakCount"] = rPeaks.size();
            }
            break;
        }
        default:
            break;
        }

        return features;
    }
} // namespace Bio
