// Copyright (C) 2016 The Qt Company Ltd.


#ifndef QPARALLELANIMATIONGROUP_H
#define QPARALLELANIMATIONGROUP_H

#include <QtCore/qanimationgroup.h>

QT_REQUIRE_CONFIG(animation);

QT_BEGIN_NAMESPACE

class QParallelAnimationGroupPrivate;
class Q_CORE_EXPORT QParallelAnimationGroup : public QAnimationGroup
{
    Q_OBJECT

public:
    QParallelAnimationGroup(QObject *parent = nullptr);
    ~QParallelAnimationGroup();

    int duration() const override;

protected:
    QParallelAnimationGroup(QParallelAnimationGroupPrivate &dd, QObject *parent);
    bool event(QEvent *event) override;

    void updateCurrentTime(int currentTime) override;
    void updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState) override;
    void updateDirection(QAbstractAnimation::Direction direction) override;

private:
    Q_DISABLE_COPY(QParallelAnimationGroup)
    Q_DECLARE_PRIVATE(QParallelAnimationGroup)
    Q_PRIVATE_SLOT(d_func(), void _q_uncontrolledAnimationFinished())
};

QT_END_NAMESPACE

#endif // QPARALLELANIMATIONGROUP
