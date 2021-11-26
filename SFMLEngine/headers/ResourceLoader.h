#pragma once
#include <map>
#include <vector>
#include <string>

namespace SFENG {
	/// <summary>
	/// Tempalte class used to handle the resouces.
	/// </summary>
	/// <typeparam name="Resource"></typeparam>
	template<class Resource>
	class ResourceLoader {
	public:
		ResourceLoader(const std::string& failedPath)
			: m_FailedPath(failedPath)
		{}
		Resource& Get(const std::string& savedName)
		{
			if (Exists(savedName))
				return *m_Resources[savedName];
			else
				return Add(m_FailedPath, savedName);
		}
		Resource& Add(const std::string& filePath, const std::string& name)
		{
			Resource* r = new Resource;
			if (!Exists(name))
			{
				if (!r->loadFromFile(filePath))
					r->loadFromFile(m_FailedPath);
				m_Resources.insert(std::make_pair(name, r));
			}
			return *m_Resources[name];
		}
		bool Exists(const std::string& name)
		{
			return m_Resources.find(name) != m_Resources.end();
		}
		~ResourceLoader() {
			for (auto& i : m_Resources)
				delete i.second;
		}
	private:
		std::string m_FailedPath;
		std::map<std::string, Resource*> m_Resources;
	};
}