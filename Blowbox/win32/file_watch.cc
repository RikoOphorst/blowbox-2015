#include "../../blowbox/win32/file_watch.h"

#include "../../blowbox/memory/shared_ptr.h"
#include "../../blowbox/lua/lua_wrapper.h"
#include "../../blowbox/console/console.h"
#include "../../blowbox/content/content_manager.h"

namespace blowbox
{
	//------------------------------------------------------------------------------------------------------
	FileWatch::FileWatch()
	{

	}

	//------------------------------------------------------------------------------------------------------
	FileWatch::~FileWatch()
	{

	}

	//------------------------------------------------------------------------------------------------------
	FileWatch* FileWatch::Instance()
	{
		static SharedPtr<FileWatch> ptr(new FileWatch());
		return ptr.get();
	}

	//------------------------------------------------------------------------------------------------------
	void FileWatch::Update()
	{
		while (!add_queue_.empty())
		{
			auto it = add_queue_.front();
			files_.emplace(it.path, it);
			add_queue_.pop();
		}

		while (!remove_queue_.empty())
		{
			auto it = remove_queue_.front();
			files_.erase(it.path);
			remove_queue_.pop();
		}

		for (auto& pair = files_.begin(); pair != files_.end(); ++pair)
		{
			auto& it = pair->second;

			bool failed = false;
			FILETIME last_changed = GetTime(it.path, failed);
			if (!failed)
			{
				if (CompareFileTime(&it.last_changed, &last_changed) != 0)
				{
					switch (it.type)
					{
					case WATCH_FILE_TYPES::WATCH_FILE_SCRIPT:
						LuaWrapper::Instance()->CompileFromFile(LuaState::Instance()->Get(), it.path, true);
						Console::Instance()->Log(std::string("[FILEWATCH] Reloaded a script: ") + it.path, LOG_COLOR_TYPES::LOG_COLOR_NOTICE);
						break;
					case WATCH_FILE_TYPES::WATCH_FILE_SHADER:
						ContentManager::Instance()->LoadShader(it.path);
						Console::Instance()->Log(std::string("[FILEWATCH] Reloaded a shader: ") + it.path, LOG_COLOR_TYPES::LOG_COLOR_NOTICE);
						break;
					case WATCH_FILE_TYPES::WATCH_FILE_TEXTURE:
						ContentManager::Instance()->LoadTexture(it.path);
						Console::Instance()->Log(std::string("[FILEWATCH] Reloaded a texture: ") + it.path, LOG_COLOR_TYPES::LOG_COLOR_NOTICE);
						break;
					}
					it.last_changed = last_changed;
					break;
				}
			}
		}
	}

	//------------------------------------------------------------------------------------------------------
	void FileWatch::Add(const std::string& path, const WATCH_FILE_TYPES& type)
	{
		if (files_.find(path) == files_.end())
		{
			WatchedFile file;
			ZeroMemory(&file, sizeof(file));

			file.path = path;
			file.type = type;

			bool failed = false;
			file.last_changed = GetTime(path, failed);

			while (failed)
			{
				file.last_changed = GetTime(path, failed);
			}

			add_queue_.push(file);
		}
	}

	//------------------------------------------------------------------------------------------------------
	void FileWatch::Remove(const std::string& path)
	{
		if (files_.find(path) != files_.end())
		{
			remove_queue_.push(files_.find(path)->second);
		}
	}

	//------------------------------------------------------------------------------------------------------
	FILETIME FileWatch::GetTime(const std::string& path, bool& failed)
	{
		FILETIME creationTime;
		FILETIME lastAccessTime;
		FILETIME lastWriteTime;

		HANDLE file = CreateFileA(path.c_str(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

		if (file == INVALID_HANDLE_VALUE)
		{
			failed = true;
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