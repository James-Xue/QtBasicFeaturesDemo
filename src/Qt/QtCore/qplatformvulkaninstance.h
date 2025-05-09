// Copyright (C) 2017 The Qt Company Ltd.


#ifndef QPLATFORMVULKANINSTANCE_H
#define QPLATFORMVULKANINSTANCE_H

//
//  W A R N I N G
//  -------------
//
// This file is part of the QPA API and is not meant to be used
// in applications. Usage of this API may make your code
// source and binary incompatible with future versions of Qt.
//

#include <QtGui/qtguiglobal.h>

#if QT_CONFIG(vulkan) || defined(Q_QDOC)

#include <qvulkaninstance.h>

QT_BEGIN_NAMESPACE

class QPlatformVulkanInstancePrivate;

class Q_GUI_EXPORT QPlatformVulkanInstance
{
    Q_DECLARE_PRIVATE(QPlatformVulkanInstance)

public:
    QPlatformVulkanInstance();
    virtual ~QPlatformVulkanInstance();

    virtual QVulkanInfoVector<QVulkanLayer> supportedLayers() const = 0;
    virtual QVulkanInfoVector<QVulkanExtension> supportedExtensions() const = 0;
    virtual QVersionNumber supportedApiVersion() const = 0;
    virtual void createOrAdoptInstance() = 0;
    virtual bool isValid() const = 0;
    virtual VkResult errorCode() const = 0;
    virtual VkInstance vkInstance() const = 0;
    virtual QByteArrayList enabledLayers() const = 0;
    virtual QByteArrayList enabledExtensions() const = 0;
    virtual PFN_vkVoidFunction getInstanceProcAddr(const char *name) = 0;
    virtual bool supportsPresent(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, QWindow *window) = 0;
    virtual void presentAboutToBeQueued(QWindow *window);
    virtual void presentQueued(QWindow *window);
    virtual void setDebugFilters(const QList<QVulkanInstance::DebugFilter> &filters);
    virtual void setDebugUtilsFilters(const QList<QVulkanInstance::DebugUtilsFilter> &filters);
    virtual void beginFrame(QWindow *window);
    virtual void endFrame(QWindow *window);

private:
    QScopedPointer<QPlatformVulkanInstancePrivate> d_ptr;
    Q_DISABLE_COPY(QPlatformVulkanInstance)
};

QT_END_NAMESPACE

#endif // QT_CONFIG(vulkan)

#if defined(Q_QDOC)
/*
  The following include file did not exist for clang-qdoc running
  in macOS, but the classes are documented in qvulkanfunctions.cpp.
  clang-qdoc must parse the class declarations in an include file,
  or else it can't find a place to put the documentation for the
  classes. Apparently these classes are created at build time if
  Vulkan is present.
 */
#ifndef QVULKANFUNCTIONS_H
#define QVULKANFUNCTIONS_H

#include <QtGui/qtguiglobal.h>

#if QT_CONFIG(vulkan) || defined(Q_QDOC)

#ifndef VK_NO_PROTOTYPES
#define VK_NO_PROTOTYPES
#endif
#include <vulkan/vulkan.h>

#include <QtCore/qscopedpointer.h>

QT_BEGIN_NAMESPACE

class QVulkanInstance;
class QVulkanFunctionsPrivate;
class QVulkanDeviceFunctionsPrivate;

class Q_GUI_EXPORT QVulkanFunctions
{
public:
    ~QVulkanFunctions();

private:
    Q_DISABLE_COPY(QVulkanFunctions)
    QVulkanFunctions(QVulkanInstance *inst);

    QScopedPointer<QVulkanFunctionsPrivate> d_ptr;
    friend class QVulkanInstance;
};

class Q_GUI_EXPORT QVulkanDeviceFunctions
{
public:
    ~QVulkanDeviceFunctions();

private:
    Q_DISABLE_COPY(QVulkanDeviceFunctions)
    QVulkanDeviceFunctions(QVulkanInstance *inst, VkDevice device);

    QScopedPointer<QVulkanDeviceFunctionsPrivate> d_ptr;
    friend class QVulkanInstance;
};

QT_END_NAMESPACE

#endif // QT_CONFIG(vulkan) || defined(Q_QDOC)
#endif // QVULKANFUNCTIONS_H;
#endif // Q_QDOC

#endif // QPLATFORMVULKANINSTANCE_H
