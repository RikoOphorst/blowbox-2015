#pragma once

#include <strsafe.h>
#include <Windows.h>
#include <map>
#include <queue>
#include <string>

#include "../memory/shared_ptr.h"
#include "../lua/lua_manager.h"

namespace blowbox
{
	enum FileType
	{
		Script,
		Shader,
		Texture
	};

	struct FileWatched
	{
		std::string path;
		FILETIME lastTime;
		FileType type;
	};

	class FileWatch
	{
	public:
		FileWatch();
		~FileWatch();

		static FileWatch* Instance();

		void Update();

		void Add(std::string& path, FileType type);
		void Remove(std::string path);

		void ReloadScript(FileWatched& file);
		void ReloadShader(FileWatched& file);
		void ReloadTexture(FileWatched& file);

		FILETIME GetTimeForFile(std::string& path, bool* failed);
	private:
		std::map<std::string, FileWatched>		files_;
		std::queue<FileWatched>					queue_;
	};
}