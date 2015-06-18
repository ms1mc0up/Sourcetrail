#ifndef STORAGE_CACHE_H
#define STORAGE_CACHE_H

#include <map>

#include "data/access/StorageAccessProxy.h"

class StorageCache
	: public StorageAccessProxy
{
public:
	void clear();

	virtual std::vector<Id> getTokenIdsForQuery(std::string query) const;

private:
	mutable std::map<std::string, std::vector<Id>> m_queryToTokenIds;
};

#endif // STORAGE_CACHE_H
