#include "file_watch.h"

namespace blowbox
{
	FileWatch::FileWatch() 
	{

	};

	FileWatch::~FileWatch() 
	{

	};

	FileWatch* FileWatch::Instance()
	{
		static SharedPtr<FileWatch> ptr(new FileWatch());
		return ptr.get();
	}

	void FileWatch::Update()
	{
		while (!queue_.empty())
		{
			auto it = queue_.front();
			files_.emplace(it.path, it);
			queue_.pop();
		}

		for (auto& pair = files_.begin(); pair != files_.end(); ++pair)
		{
			auto& it = pair->second;

			bool failed = false;
			FILETIME lastTime = GetTimeForFile(it.path, &failed);
			if (!failed)
			{
				if (CompareFileTime(&it.lastTime, &lastTime) != 0)
				{
					switch (it.type)
					{
					case FileType::Script:
						ReloadScript(it);
						break;
					case FileType::Shader:
						ReloadShader(it);
						break;
					case FileType::Texture:
						ReloadTexture(it);
						break;
					}
					it.lastTime = lastTime;
					break;
				}
			}
		}
	}

	void FileWatch::Add(std::string& path, FileType type) 
	{
		if (files_.find(path) == files_.end())
		{
			FileWatched file;
			file.path = path;
			bool failed = false;
			file.lastTime = GetTimeForFile(path, &failed);
			file.type = type;

			while (failed)
			{
				file.lastTime = GetTimeForFile(path, &failed);
			}

			queue_.push(file);
		}
	}

	void FileWatch::ReloadScript(FileWatched& file)
	{
		LuaManager::Instance()->LoadScript(file.path, true);
		BLOW_LOG("Hot reloaded a script: " + file.path)
	}

	void FileWatch::ReloadTexture(FileWatched& file)
	{
		ContentManager::Instance()->LoadTexture(file.path);
		BLOW_LOG("Hot reloaded a texture: " + file.path);
	}

	void FileWatch::ReloadShader(FileWatched& file)
	{
		ContentManager::Instance()->LoadShader(file.path);
		BLOW_LOG("Hot reloaded a shader: " + file.path);
	}

	FILETIME FileWatch::GetTimeForFile(std::string& path, bool* failed)
	{
		FILETIME creationTime;
		FILETIME lastAccessTime;
		FILETIME lastWriteTime;

		HANDLE file = CreateFileA(path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

		if (file == INVALID_HANDLE_VALUE)
		{
			*failed = true;
			LPTSTR msg = nullptr;
			DWORD err = GetLastError();
			FormatMessage(
				FORMAT_MESSAGE_ALLOCATE_BUFFER |
				FORMAT_MESSAGE_FROM_SYSTEM |
				FORMAT_MESSAGE_IGNORE_INSERTS,
				NULL,
				err,
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				(LPTSTR)&msg,
				0, NULL);

			LocalFree(msg);
			FILETIME error = {};
			return error;
		}

		BOOL result = GetFileTime(file, &creationTime, &lastAccessTime, &lastWriteTime);
		BLOW_ASSERT(result == TRUE, "Couldn't read time for file: " + path);

		CloseHandle(file);
		return lastWriteTime;
	}
}