/**
 * Copyright (c) 2014-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#pragma once

#ifdef __cplusplus
#define YG_EXTERN_C_BEGIN extern "C" {
#define YG_EXTERN_C_END }
#else
#define YG_EXTERN_C_BEGIN
#define YG_EXTERN_C_END
#endif

#ifdef _WINDLL
#define WIN_EXPORT __declspec(dllexport)
#else
#define WIN_EXPORT
#endif

#ifndef FB_ASSERTIONS_ENABLED
#define FB_ASSERTIONS_ENABLED 0
#endif

#if FB_ASSERTIONS_ENABLED
#define YG_ABORT() abort()
#else
#define YG_ABORT()
#endif

#ifndef YG_ASSERT
#define YG_ASSERT(X, message)              \
  if (!(X)) {                              \
    YGLog(YGLogLevelError, "%s", message); \
    YG_ABORT();                            \
  }
#endif
