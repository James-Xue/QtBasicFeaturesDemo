#ifndef SIGNALPREPROCESSORMODULE_H
#define SIGNALPREPROCESSORMODULE_H

#include <QObject>
#include <QVector>

namespace Bio
{
    class SignalPreprocessModule : public QObject
    {
        //Q_OBJECT
    public:
        enum ProcessingType
        {
            Filtering,
            Normalization,
            Denoising,
            BaselineCorrection
        };

        explicit SignalPreprocessModule(QObject *parent = nullptr);
        virtual ~SignalPreprocessModule();

    //    void setProcessingType(ProcessingType type);
    //    QVector<double> preprocessSignal(const QVector<double> &signal);

    //signals:
    //    void preprocessingComplete(const QVector<double> &processedSignal);
    //    void preprocessingFailed(const QString &errorMsg);

    //private:
    //    ProcessingType m_processingType;
    //    QVector<double> applyFilter(const QVector<double> &signal);
    //    QVector<double> normalize(const QVector<double> &signal);
    };
} // namespace Bio

#endif // SIGNALPREPROCESSORMODULE_H    