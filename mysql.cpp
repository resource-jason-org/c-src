#include <mysql.h>
#include <string>
#include <stdio.h>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./test \"SQL Statement\"\n");
        return -1;
    }
    MYSQL mysql;
    mysql_init(&mysql);
    if (!mysql_real_connect(&mysql,"127.0.0.1","root","","game",3306,NULL,0))//连接到本地数据库
    {
        fprintf(stderr, "Failed to connect to database: Error: %s\n",
        mysql_error(&mysql));
    }
    mysql_query(&mysql, "set names utf8");
    printf("connect to %s:%d success...\n", "localhost", 3306);

    string sql(argv[1]);
    if (mysql_real_query(&mysql, sql.c_str(), sql.length()))
    {
        //error
    }
    else 
    { // 成功执行SQL语句
        MYSQL_RES* res = mysql_store_result(&mysql);//获得结果
        if (res) // sucess
        {
            printf("\"%s\" success\n", sql.c_str());
            int num_fields = mysql_num_fields(res);
            int num_rows = mysql_num_rows(res);
            printf("result: %d rows  %d fields\n", num_rows, num_fields);
            printf("----------------------------\n");

            //1. 获得列属性（名称）
            MYSQL_FIELD* fields;//数组，包含所有field的元数据
            fields = mysql_fetch_fields(res);
            for (int i = 0; i < num_fields; ++i)
            {
                printf("%s\t", fields[i].name);
            }
            printf("\n");

            //2. 获得每行的数据
            MYSQL_ROW row;
            while ((row = mysql_fetch_row(res)))
            {
                unsigned long *lengths;
                lengths = mysql_fetch_lengths(res);
                for (int i = 0; i < num_fields; ++i)
                {
                    printf("%s\t",  row[i] ? row[i] : "NULL");
                }
                printf("\n");
            }
            printf("----------------------------\n");
            mysql_free_result(res);
        }
        else
        {
            //接下来就需要判断为什么res为NULL了

            int ret = mysql_field_count(&mysql);
            //printf("mysql_field_count %d\n", ret);
            if (ret == 0)
            {
                // 说明执行的是UPDATE/INSERT等这类操作
                int ret = mysql_affected_rows(&mysql);
                printf("Query OK, %d rows affected\n", ret);
            }
            else
            {
                fprintf(stderr, "Error: %s\n", mysql_error(&mysql));
            }
        }
    }
    mysql_close(&mysql);
    return 0;
}
