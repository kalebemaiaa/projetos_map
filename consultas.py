import sqlite3 as sql
from sys import argv as args

def main():
    con = sql.connect('songs.db')
    cur = con.cursor()

    if len(args) < 2:
        print("[USAGE] python main.py [files]")
        return 1

    for i in range(1,len(args)):
        extensao = args[i].split('.')[len(args[i].split('.')) - 1]

        if extensao != "sql":
            print(f"[ERROR] Extensao de arquivo consulta invalida:\n\t{args[i]}")
            return 2

    try:
        for i in range(1,len(args)):
            with open(args[i], "r") as f:

                for row in f:
                    if row.split()[0].upper() != "SELECT":
                        print(f"[WARNING] Comando inváido (apenas realizo consultas):\n\t{row.split()[0]}")
                        continue

                    print(f"\n\tConsulta [{i}]: {row}\n")
                    try:
                        for test in cur.execute(row):
                            print(list(test)[0])

                    except sql.Error:
                        print(f"[ERROR] Houve um erro na consulta {i}")

                return 0

    except IOError:
        print(f"\n[ERROR] I can't open the file:\n\t{args[i]}")
        return 3;

main()
