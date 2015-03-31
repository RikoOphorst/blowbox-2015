#pragma once

#include <map>
#include <string>
#include <Windows.h>
#include <queue>

namespace blowbox
{
	/**
	* @enum blowbox::WATCH_FILE_TYPES
	* @brief The type of a watched file
	*/
	enum WATCH_FILE_TYPES
	{
		WATCH_FILE_SHADER,
		WATCH_FILE_TEXTURE,
		WATCH_FILE_SCRIPT
	};

	/**
	* @struct blowbox::WatchedFile
	* @brief A struct that holds the data of a file that's being watched
	*/
	struct WatchedFile
	{
		std::string path;
		FILETIME last_changed;
		WATCH_FILE_TYPES type;
	};
	
	class FileWatch
	{
	public:
		/**
		* @brief Default FileWatch constructor
		*/
		FileWatch();

		/**
		* @brief Default FileWatch destructor
		*/
		~FileWatch();

		/**
		* @brief Retrieves the FileWatch instance
		*/
		static FileWatch* Instance();

		/**
		* @brief Does a check on all files that are watched and reloads them when necessary
		*/
		void Update();

		/**
		* @brief Adds a file to the watch
		* @param[in] path (const std::string&) the path to the file
		* @param[in] type (const WATCH_FILE_TYPES&) the type of the file
		*/
		void Add(const std::string& path, const WATCH_FILE_TYPES& type);

		/**
		* @brief Removes a file from the watch
		* @param[in] path (const std::string&) the path to the file
		*/
		void Remove(const std::string& path);

		/**
		* @brief Gets the last-edited time of a file
		* @param[in] path (const std::string&) the path to the file
		* @param[out] failed (bool&) did the filetime fail?
		*/
		FILETIME GetTime(const std::string& path, bool& failed);
	private:
		std::map<std::string, WatchedFile> files_;
		std::queue<WatchedFile> add_queue_;
		std::queue<WatchedFile> remove_queue_;
	};
}