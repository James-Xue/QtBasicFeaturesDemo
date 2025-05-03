// Copyright (C) 2013 BlackBerry Limited. All rights reserved.


#ifndef QQNXSCREENEVENTFILTER_H
#define QQNXSCREENEVENTFILTER_H

QT_BEGIN_NAMESPACE

class QQnxScreenEventFilter
{
protected:
    ~QQnxScreenEventFilter() {}

public:
    virtual bool handleKeyboardEvent(int flags, int sym, int mod, int scan, int cap, int sequenceId) = 0;
};

QT_END_NAMESPACE

#endif
