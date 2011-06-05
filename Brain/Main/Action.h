#pragma once
#include "TaskManager.h"

class BRAINEXPORT ComplexAction : public Action
{
public:
	BEHAVIOR_CLASS_DECLARE(ComplexAction);

	virtual bool Execute();
};

class BRAINEXPORT CreateFileAction : public Action
{
public:
	BEHAVIOR_CLASS_DECLARE(CreateFileAction);

    virtual bool Execute();
};

class BRAINEXPORT DeleteFileAction : public Action
{
public:
	BEHAVIOR_CLASS_DECLARE(DeleteFileAction);

	virtual bool Execute();
};

class BRAINEXPORT CopyFileAction : public Action
{
public:
	BEHAVIOR_CLASS_DECLARE(CopyFileAction);

	virtual bool Execute();
};

class BRAINEXPORT CreateFolderAction : public Action
{
public:
	BEHAVIOR_CLASS_DECLARE(CreateFolderAction);

	virtual bool Execute();
};

class BRAINEXPORT DeleteFolderAction : public Action
{
public:
	BEHAVIOR_CLASS_DECLARE(DeleteFolderAction);

	virtual bool Execute();
};

class BRAINEXPORT CopyFolderAction : public Action
{
public:
	BEHAVIOR_CLASS_DECLARE(CopyFolderAction);

	virtual bool Execute();
};

class BRAINEXPORT MakeDirectoryLinkAction : public Action
{
public:
	BEHAVIOR_CLASS_DECLARE(MakeDirectoryLinkAction);

	virtual bool Execute();
};

