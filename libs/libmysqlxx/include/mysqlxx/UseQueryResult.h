#ifndef MYSQLXX_USEQUERYRESULT_H
#define MYSQLXX_USEQUERYRESULT_H

#include <mysqlxx/ResultBase.h>
#include <mysqlxx/Row.h>


namespace mysqlxx
{

class Connection;


/** Результат выполнения запроса, предназначенный для чтения строк, одна за другой.
  * В памяти при этом хранится только одна, текущая строка.
  * В отличие от StoreQueryResult, произвольный доступ к строкам невозможен,
  *  а также, при чтении следующей строки, предыдущая становится некорректной.
  * Вы обязаны прочитать все строки из результата
  *  (вызывать функцию fetch(), пока она не вернёт значение, преобразующееся к false),
  *  иначе при следующем запросе будет выкинуто исключение с текстом "Commands out of sync".
  * Объект содержит ссылку на Connection.
  * Если уничтожить Connection, то объект становится некорректным и все строки результата - тоже.
  * Если задать следующий запрос в соединении, то объект и все строки тоже становятся некорректными.
  */
class UseQueryResult : public ResultBase
{
public:
	UseQueryResult(MYSQL_RES * res_, Connection * conn_, const Query * query_);

	Row fetch();

	/// Для совместимости
	Row fetch_row() { return fetch(); }
};

}

#endif
