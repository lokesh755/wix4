#pragma once
// Copyright (c) .NET Foundation and contributors. All rights reserved. Licensed under the Microsoft Reciprocal License. See LICENSE.TXT file in the project root for full license information.


#ifdef __cplusplus
extern "C" {
#endif


enum GENERIC_EXECUTE_MESSAGE_TYPE
{
    GENERIC_EXECUTE_MESSAGE_NONE,
    GENERIC_EXECUTE_MESSAGE_ERROR,
    GENERIC_EXECUTE_MESSAGE_PROGRESS,
    GENERIC_EXECUTE_MESSAGE_NETFX_FILES_IN_USE,
};

typedef struct _APPLY_AUTHENTICATION_REQUIRED_DATA
{
    BURN_USER_EXPERIENCE* pUX;
    LPCWSTR wzPackageOrContainerId;
    LPCWSTR wzPayloadId;
} APPLY_AUTHENTICATION_REQUIRED_DATA;

typedef struct _GENERIC_EXECUTE_MESSAGE
{
    GENERIC_EXECUTE_MESSAGE_TYPE type;
    DWORD dwUIHint;

    union
    {
        struct
        {
            DWORD dwErrorCode;
            LPCWSTR wzMessage;
        } error;
        struct
        {
            DWORD dwPercentage;
        } progress;
        struct
        {
            DWORD cFiles;
            LPCWSTR* rgwzFiles;
        } filesInUse;
    };
} GENERIC_EXECUTE_MESSAGE;


typedef int (*PFN_GENERICMESSAGEHANDLER)(
    __in GENERIC_EXECUTE_MESSAGE* pMessage,
    __in LPVOID pvContext
    );


void ApplyInitialize();
void ApplyUninitialize();
HRESULT ApplySetVariables(
    __in BURN_VARIABLES* pVariables
    );
void ApplyReset(
    __in BURN_USER_EXPERIENCE* pUX,
    __in BURN_PACKAGES* pPackages
    );
HRESULT ApplyLock(
    __in BOOL fPerMachine,
    __out HANDLE* phLock
    );
HRESULT ApplyRegister(
    __in BURN_ENGINE_STATE* pEngineState
    );
HRESULT ApplyUnregister(
    __in BURN_ENGINE_STATE* pEngineState,
    __in BOOL fFailed,
    __in BOOL fSuspend,
    __in BOOTSTRAPPER_APPLY_RESTART restart
    );
HRESULT ApplyCache(
    __in HANDLE hSourceEngineFile,
    __in BURN_USER_EXPERIENCE* pUX,
    __in BURN_VARIABLES* pVariables,
    __in BURN_PLAN* pPlan,
    __in HANDLE hPipe,
    __in BURN_APPLY_CONTEXT* pContext
    );
void ApplyCacheRollback(
    __in BURN_USER_EXPERIENCE* pUX,
    __in BURN_PLAN* pPlan,
    __in HANDLE hPipe,
    __in BURN_APPLY_CONTEXT* pContext
    );
HRESULT ApplyExecute(
    __in BURN_ENGINE_STATE* pEngineState,
    __in BURN_APPLY_CONTEXT* pApplyContext,
    __out BOOL* pfSuspend,
    __out BOOTSTRAPPER_APPLY_RESTART* pRestart
    );
void ApplyClean(
    __in BURN_USER_EXPERIENCE* pUX,
    __in BURN_PLAN* pPlan,
    __in HANDLE hPipe
    );


#ifdef __cplusplus
}
#endif
