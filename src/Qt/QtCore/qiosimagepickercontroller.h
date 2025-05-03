// Copyright (C) 2017 The Qt Company Ltd.


#import <UIKit/UIKit.h>

#include "../../qiosfiledialog.h"

@interface QIOSImagePickerController : UIImagePickerController <UIImagePickerControllerDelegate, UINavigationControllerDelegate>
- (instancetype)initWithQIOSFileDialog:(QIOSFileDialog *)fileDialog;
@end
