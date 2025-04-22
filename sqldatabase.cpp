// ConexionBD.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Ricardo Diaz.

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



        //Ricardo diaz
        // Imprimir encabezados de la tabla
        wcout << "+-----+-------------------------+-----------+-----------+-------------------+--------------------------+-----------------+ " << endl;
        wcout << "| No. | Nombre completo         | Fecha Nac.|   RFC     | Centro de Trabajo |         Puesto           |  Es directivo?  | " << endl;
        wcout << "+-----+-------------------------+-----------+-----------+-------------------+--------------------------+-----------------+ " << endl;
        // Ejemplo de consulta SELECT
        ret = SQLExecDirect(hStmt, (SQLWCHAR*)L"SELECT * FROM Datos_Empleados", SQL_NTS);
        if (ret == SQL_SUCCESS || ret == SQL_SUCCESS_WITH_INFO) {
            int num_empleado;
            SQLWCHAR nombre[50];
            SQLWCHAR apellido_p[50];
            SQLWCHAR apellido_m[50];
            SQLWCHAR fecha_nac[50];
            SQLWCHAR rfc[50];
            SQLWCHAR centro_trabajo[50];
            SQLWCHAR puesto[50];
            SQLWCHAR descripcion_puesto[26];
            SQLWCHAR directivo[26];

            while (SQLFetch(hStmt) == SQL_SUCCESS) {
                SQLGetData(hStmt, 1, SQL_C_LONG, &num_empleado, 0, NULL);
                SQLGetData(hStmt, 2, SQL_C_WCHAR, nombre, sizeof(nombre), NULL);
                SQLGetData(hStmt, 3, SQL_C_WCHAR, apellido_p, sizeof(apellido_p), NULL);
                SQLGetData(hStmt, 4, SQL_C_WCHAR, apellido_m, sizeof(apellido_m), NULL);
                SQLGetData(hStmt, 5, SQL_C_WCHAR, fecha_nac, sizeof(fecha_nac), NULL);
                SQLGetData(hStmt, 6, SQL_C_WCHAR, rfc, sizeof(rfc), NULL);
                SQLGetData(hStmt, 7, SQL_C_WCHAR, centro_trabajo, sizeof(centro_trabajo), NULL);
                SQLGetData(hStmt, 8, SQL_C_WCHAR, puesto, sizeof(puesto), NULL);
                SQLGetData(hStmt, 9, SQL_C_WCHAR, descripcion_puesto, sizeof(descripcion_puesto), NULL);
                SQLGetData(hStmt, 10, SQL_C_WCHAR, directivo, sizeof(directivo), NULL);
                //wcout << "|    " << num_empleado << "    |  " << nombre << "  |   " << apellido_p << "    |   " << apellido_m << "   |" << fecha_nac << " |" << rfc << "|       " << centro_trabajo << "      |" << puesto << "|" << descripcion_puesto << "|" << endl;
                //wcout << "+---------+-----------------+-----------+-----------+-----------+----------+-------------------+---------+-------------------------+ " << endl;
                      // Concatenar nombre y apellido paterno
                wstring apellidos = wstring(apellido_p) + L" " + wstring(apellido_m);
                wstring nombre_completo = wstring(nombre) + L" " + wstring(apellidos);
                wstring dir = wstring(directivo);
                wstring respuestadir;

                if (dir == L"1") {
                    respuestadir = L"Si";
                }
                else
                {
                    respuestadir = L"No";
                }


                // Imprimir datos de la fila con alineación
                wcout << L"| " << setw(4) << left << num_empleado
                    << L"| " << setw(24) << left << nombre_completo
                    << L"| " << setw(10) << left << fecha_nac
                    << L"| " << setw(10) << left << rfc
                    << L"| " << setw(18) << left << centro_trabajo
                    << L"| " << setw(25) << left << puesto
                    << L"| " << setw(15) << left << respuestadir << L" |" << endl;
            }
        }

        // Imprimir línea final de la tabla
        wcout << "+-----+-------------------------+-----------+-----------+-------------------+--------------------------+-----------------+ " << endl;

        // Liberar el manejador de conexión
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);


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
