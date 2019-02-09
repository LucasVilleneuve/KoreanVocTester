//
// Created by Lucas on 29-Jan-19.
//

#include <iostream>
#include <vector>
#include <memory>
#include "DatabaseHandler.hh"

DatabaseHandler::DatabaseHandler(const std::string &database)
{
  int rc = sqlite3_open(database.c_str(), &sql);
  if (rc)
	{
	  std::cerr << "Can't open database: "
				<< sqlite3_errmsg(sql) << std::endl;
	  sql = nullptr;
	  return;
	}
}

DatabaseHandler::~DatabaseHandler()
{
  if (sql)
	{
	  sqlite3_close(sql);
	}
}

std::vector<DatabaseHandler::QueryContent> DatabaseHandler::execute(const std::string &query)
{
  if (!sql) return std::vector<QueryContent>();

  char *errMsg = nullptr;
  auto queryContent = std::make_unique<std::vector<QueryContent>>();

  int rc = sqlite3_exec(sql, query.c_str(),
						[](void *v, int nb, char **content, char **col) {
    						auto qc = (std::vector<QueryContent> *)v; // TODO dymamic_cast
							qc->emplace_back(nb, content, col);
							return 0;
						}, queryContent.get(), &errMsg);

  if (rc != SQLITE_OK)
	{
	  std::cerr << "SQL error: " << errMsg << std::endl;
	  sqlite3_free(errMsg);
	}

  std::cout << "End" << std::endl;
  return *queryContent;
}
