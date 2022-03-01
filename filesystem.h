#pragma once
#include <string>
#include <cstdlib>
#include <windows.h>

class FileSystem {
private:
	typedef std::string(*Builder) (const std::string& path);
public:
	static std::string getPath(const std::string& path) {
		static std::string(*pathBuilder)(std::string const&) = getPathBuilder();
		return (*pathBuilder)(path);
	}

public:
	static std::string const& getRoot() {
		
		//hard code, need to change 
		//char* logl_root = _getcwd(NULL, 0);
		char* buffer;
		
		
		//static char const * envRoot = _dupenv_s("LOGL_ROOT_PATH");
		//static char const* givenRoot = (envRoot != nullptr ? envRoot : logl_root);
		//static std::string root = (givenRoot != nullptr ? givenRoot : "");
		//return root;
		return _getcwd(NULL, 0);
	}

	static Builder getPathBuilder() {
		if (getRoot() != "") {
			return &FileSystem::getPathRelativeRoot;
		}
		else {
			return &FileSystem::getPathRelativeBinary;
		}
	}

	static std::string getPathRelativeRoot(const std::string& path)
	{
		return getRoot() + std::string("/") + path;
	}

	static std::string getPathRelativeBinary(const std::string& path)
	{
		return "../../../" + path;
	}
};
