#pragma once
#include "TaskManager.h"

class BRAINEXPORT CreateFileAction : public Action
{
public:
    virtual bool Execute();
};

class BRAINEXPORT DeleteFileAction : public Action
{
public:
    virtual bool Execute();
};

class BRAINEXPORT CopyFileAction : public Action
{
public:
    virtual bool Execute();
};

class BRAINEXPORT CreateFolderAction : public Action
{
public:
    virtual bool Execute();
};

class BRAINEXPORT DeleteFolderAction : public Action
{
public:
    virtual bool Execute();
};

class BRAINEXPORT CopyFolderAction : public Action
{
public:
    virtual bool Execute();
};

class BRAINEXPORT MakeDirectoryLinkAction : public Action
{
public:
    virtual bool Execute();
};

