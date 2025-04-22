// ConexionBD.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Ricardo Diaz

#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    SQLHENV hEnv;
    SQLHDBC hDbc;
    SQLRETURN ret;

    // Asignar un gestor de entorno
    ret = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    ret = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

    // Asignar un gestor de conexión
    ret = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);

    // Conectarse a la base de datos
    ret = SQLConnect(hDbc, (SQLWCHAR*)L"sqlserver", SQL_NTS, (SQLWCHAR*)L"Username", SQL_NTS, (SQLWCHAR*)L"Password", SQL_NTS);
    // Ricardo diaz
    if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
        cout << "Conectado a la base de datos exitosamente." << endl;

        // Ejemplo de ejecución de una consulta
        SQLHSTMT hStmt;
        ret = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);


        // Imprimir encabezados de la tabla
        cout << "+---------------+------------------- +-----------+" << endl;
        cout << "| No. Empleado  | Centro supervisado | Directivo |" << endl;
        cout << "+---------------+--------------------+-----------+" << endl;

       // Ejemplo de consulta SELECT
        ret = SQLExecDirect(hStmt, (SQLWCHAR*)L"SELECT * FROM Directivos", SQL_NTS);
        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            int num_empleado;
            SQLCHAR centrosupervisado[50];
            SQLCHAR combustible[50];

            while (SQLFetch(hStmt) == SQL_SUCCESS) {
                SQLGetData(hStmt, 1, SQL_C_LONG, &num_empleado, 0, NULL);
                SQLGetData(hStmt, 2, SQL_C_CHAR, centrosupervisado, sizeof(centrosupervisado), NULL);
                SQLGetData(hStmt, 3, SQL_C_CHAR, combustible, sizeof(combustible), NULL);

                cout << "|     " << num_empleado << "         |        " << centrosupervisado << "      |   " << combustible << "       |" << endl;
                cout << "+---------------+--------------------+-----------+" << endl;

            }
        }

        //Ricardo diaz
        // Imprimir encabezados de la tabla
       // cout << "+---------+-----------------+-----------+-----------+-----------+----------+-------------------+---------+-------------------------+ " << endl;
       // cout << "| No. Emp.| Nombre completo | Apelldio p| Apellido M| Fecha Nac.|   RFC    | Centro de Trabajo | Puesto  | Descripcion del Puesto  | " << endl;
       // cout << "+---------+-----------------+-----------+-----------+-----------+----------+-------------------+---------+-------------------------+ " << endl;
        // Ejemplo de consulta SELECT
        ret = SQLExecDirect(hStmt, (SQLWCHAR*)L"SELECT * FROM Datos_Empleados", SQL_NTS);
        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            int num_empleado;
            SQLCHAR nombre[50];
            SQLCHAR apellido_p[50];
            SQLCHAR apellido_m[50];
            SQLCHAR fecha_nac[50];
            SQLCHAR rfc[50];
            SQLCHAR centro_trabajo[50];
            SQLCHAR puesto[50];
            SQLCHAR descripcion_puesto[26];

            while (SQLFetch(hStmt) == SQL_SUCCESS) {
                SQLGetData(hStmt, 1, SQL_C_LONG, &num_empleado, 0, NULL);
                SQLGetData(hStmt, 2, SQL_C_CHAR, nombre, sizeof(nombre), NULL);
                SQLGetData(hStmt, 3, SQL_C_CHAR, apellido_p , sizeof(apellido_p ), NULL);
                SQLGetData(hStmt, 4, SQL_C_CHAR, apellido_m, sizeof(apellido_m), NULL);
                SQLGetData(hStmt, 5, SQL_C_CHAR, fecha_nac, sizeof(fecha_nac), NULL);
                SQLGetData(hStmt, 6, SQL_C_CHAR, rfc, sizeof(rfc), NULL);
                SQLGetData(hStmt, 7, SQL_C_CHAR, centro_trabajo, sizeof(centro_trabajo), NULL);
                SQLGetData(hStmt, 8, SQL_C_CHAR, puesto, sizeof(puesto), NULL);
                SQLGetData(hStmt, 9, SQL_C_CHAR, descripcion_puesto, sizeof(descripcion_puesto), NULL);
               cout << "|    " << num_empleado << "    |  " << nombre << "  |   " << apellido_p << "    |   " << apellido_m << "   |" << fecha_nac << " |" << rfc<< "|       "<< centro_trabajo <<"      |" <<puesto << "|" << descripcion_puesto << "|" << endl;
               cout << "+---------+-----------------+-----------+-----------+-----------+----------+-------------------+---------+-------------------------+ " << endl;
            }
        }

    }
    else {
        cout << "Fallo la conexion a la base de datos" << endl;
    }

    // Desconectar y liberar gestores de entorno
    SQLDisconnect(hDbc);
    SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    SQLFreeHandle(SQL_HANDLE_ENV, hEnv);

    return 0;
}
