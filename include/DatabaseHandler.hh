//
// Created by Lucas on 29-Jan-19.
//

#ifndef KOREANVOCTESTER_DATABASEHANDLER_HH
#define KOREANVOCTESTER_DATABASEHANDLER_HH

#include <string>
#include <sqlite3.h>

class DatabaseHandler
{
public:
	struct QueryContent
	{
		int	nbCol;
		std::vector<std::string> content;
		std::vector<std::string> colNames;

		QueryContent(int nb, char **cont, char **cNames)
		: nbCol(nb)
		{
		  for (int i = 0; i < nb; ++i)
			{
			  content.emplace_back(cont[i]);
			  colNames.emplace_back(cNames[i]);
			}
		};
	};

	explicit DatabaseHandler(const std::string &database);
	~DatabaseHandler();


	/**
	 * Execute a SQL query.
	 * @param query to execute
	 * @return A vector of QueryContent containing the result of the query.
	 * 			Returns an empty vector if the connection to the db failed.
	 */
	std::vector<DatabaseHandler::QueryContent> execute(const std::string &query);

private:
	sqlite3	*sql;
};

#endif //KOREANVOCTESTER_DATABASEHANDLER_HH
