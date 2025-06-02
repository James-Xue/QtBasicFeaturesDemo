#ifndef STATEEVALUATIONMODULE_H
#define STATEEVALUATIONMODULE_H

#include <QObject>
#include <QMap>
#include <QString>

namespace Bio
{
    class StateEvaluationModule : public QObject
    {
        //Q_OBJECT
    public:
        enum EvaluationMethod
        {
            ThresholdBased,
            MachineLearningBased,
            StatisticalModeling,
            RuleBased
        };

        explicit StateEvaluationModule(QObject *parent = nullptr);
        virtual ~StateEvaluationModule();

    //    void setEvaluationMethod(EvaluationMethod method);
    //    QString evaluateState(const QMap<QString, double> &features);

    //signals:
    //    void stateEvaluated(const QString &state);
    //    void evaluationFailed(const QString &errorMsg);

    //private:
    //    EvaluationMethod m_evaluationMethod;
    //    QString evaluateByThreshold(const QMap<QString, double> &features);
    //    QString evaluateByMachineLearning(const QMap<QString, double> &features);
    };
} // namespace Bio

#endif // STATEEVALUATIONMODULE_H    